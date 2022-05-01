#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <ctype.h>
#include <iomanip>

/*using cout;
using endl;
using vector;
using string;
using pair;
using fstream;
using ios;*/

using namespace std;

class Forca {
    public:
        enum Dificuldade{
            FACIL, MEDIO, DIFICIL
        };
    private:
        //TODO: armazenar os scores?
        vector< pair<string, int> > m_palavras; //<! VETOR CONTENDO AS PALAVRAS E SUA OCORRÊNCIA NO CORPUS 

        string m_arquivo_scores; //<! NOME DO ARQUIVO CONTENDO OS SCORES 
 
        string m_arquivo_palavras; //<! NOME DO ARQUIVO CONTENDO AS PALAVRAS 
 
        Dificuldade m_dificuldade; //<! DIFICULDADE ATUAL DO JOGO 
 
        vector< string > m_palavras_do_jogo; //<! CONTAINER “PALAVRAS DO JOGO”
        vector< char > m_letras_palpitadas; //<! CONTEM AS LETRAS PALPITADAS PELO JOGADOR
        string m_palavra_atual; //<! PALAVRA SENDO JOGADA “ATUALMENTE”
        string m_palavra_jogada; //<! PALAVRA SENDO JOGADA “ATUALMENTE” NO FORMATO “_ _ _ ... _ “ 
        
        int m_tentativas_restantes=6; // ARMAZENA AS TENTATIVAS RESTANTES
        int qnt_palavras; // A QUANTIDADE DE PALAVRAS DO ARQUIVO base_formatada.txt
        int media_p; // MÉDIA DAS FREQUÊNCIAS DAS PALAVRAS DO ARQUIVO base_formatada.txt
        int soma_freq=0; // SOMA DAS FREQUÊNCIAS DAS PALAVRAS DO ARQUIVO base_formatada.txt
        vector<pair<string, string>> dificuldade_jogador;
        vector<string> palavras;
        vector<int> pont;
   
    public:
        /** 
         * CRIA A UM OBJETO FORCA 
         * O CONSTRUTOR PODE OU NÃO VALIDAR OS ARQUIVOS DE ENTRADA, NO ENTANTO, MESMO COM  
         * OS ARQUIVOS INVÁLIDOS O OBJETO DEVE SER CONSTRUÍDO. PARA O CASO DE ARQUIVOS DE PALAVRAS 
         * OU SCORES INVÁLIDOS, USE O MÉTODO eh_valido(). 
         * @param PALAVRAS O NOME DO ARQUIVO QUE CONTÉM AS PALAVRAS 
         * @param SCORES O NOME DO ARQUIVO QUE CONTÉM OS SCORES 
         * @see eh_valido 
         */
        Forca( string palavras, string scores );
       
 
        /**
         * VALIDA OS ARQUIVOS DE ENTRADA DE ACORDO COM AS ESPECIFICAÇÕES.
         * AO VALIDAR OS ARQUIVOS, NO CASO DE ARQUIVOS INVÁLIDOS, ESTE MÉTODO DEVE RETORNAR A  
         * RAZÃO CORRESPONDENTE DE ACORDO COM AS ESPECIFICAÇÕES. 
         * @return {T,""} SE OS ARQUIVOS ESTIVEREM VÁLIDOS, {F,"RAZÃO"} CASO CONTRÁRIO. 
         */
        pair<pair<bool, string>, pair<int, string>> eh_valido();
 
        /** 
         * CARREGA OS ARQUIVOS DE SCORES E PALAVRAS PREENCHENDO **AO MENOS** A ESTRUTURA m_palavras 
         */ 
        void carregar_arquivos();

        /*DETERMINA:
            # A SOMA DE TODAS AS FREQUÊNCIAS DO VETOR DE PARES m_palavras
            # A QUANTIDADE DE PALAVRAS PRESENTES NO VETOR DE PARES m_palavras
            # A MÉDIA DAS FREQUÊNCIAS DAS PALAVRAS*/
        void dados();

        /** 
         * MODIFICA A DIFICULDADE DO JOGO. 
         * ESTE MÉTODO MODIFICA A DIFICULDADE DO JOGO GERANDO UM NOVO VETOR m_palavras_do_jogo
         * TODA VEZ QUE É CHAMADO. 
         * @param d A DIFICULDADE DESEJADA 
         * @see proxima_palavra 
         */ 
        void set_dificuldade(int d);
 
        /** 
         * RETORNA A PRÓXIMA PALAVRA DE ACORDO COM A DIFICULDADE ATUAL. 
         * ESTE MÉTODO DEVE ATUALIZAR O VALOR DOS ATRIBUTOS m_palavra_atual, COM A PALAVRA ATUAL, 
         * DO ATRIBUTO m_palavra_jogada COM UM TEXTO NO FORMATO "_ _ _ _ ... _". 
         * O MÉTODO TAMBÉM DEVE SORTEAR AS LETRAS QUE DEVEM APARECER DEPENDENDO DO NÍVEL DE DIFICULDADE, 
         * ALTERANDO O VALOR DE m_palavra_jogada DE ACORDO. 
         * @return O VALOR DO ATRIBUTO m_palavra_jogada. 
         */

        string proxima_palavra();


         /** 
         * RETORNA A PALAVRA ATUAL QUE ESTÁ SENDO JOGADA. 
         * DIFERENTE DO MÉTODO proxima_palavra(), ESTE MÉTODO __NÃO ATUALIZA__ O ATRIBUTO 
         * m_palavra_atual, APENAS RETORNA O ATRIBUTO m_palavra_jogada QUE É A PALAVRA NO 
         * FORMATO  "_ _ _ _ ... _" CONTENDO TODAS AS LETRAS 
         * JÁ ACERTADAS/SORTEADAS AO INVÉS DE “_”. 
         * @return A PALAVRA ATUALMENTE SENDO JOGADA. 
         */ 
        string get_palavra_jogada(char palp);

        /** 
         * RETORNA O VALOR DA PALAVRA ATUAL, ÚTIL NO CASO DE UM GAME OVER, PARA MOSTRAR A PALAVRA QUE ESTAVA 
         * SENDO JOGADA 
         * @return O VALOR DO ATRIBUTO m_palavra_atual 
         **/ 
        string get_palavra_atual();
 
        /** 

         * TESTA SE UMA LETRA PERTENCE Á PALAVRA ATUAL E SE JÁ FOI JOGADA PELO JOGADOR. 
         * ESTE MÉTODO TESTA SE UMA LETRA PERTENCE À PALAVRA ATUAL, CASO A LETRA PERTENÇA A PALAVRA 
         * E AINDA NÃO FOI JOGADA O MÉTODO RETORNA {T, T}, CASO A LETRA NÃO PERTENÇA À PALAVRA O MÉTODO RETORNA {F,T};  
         * CASO A LETRA JÁ TENHA SIDO JOGADA O MÉTODO RETORNA {T, F}, QUANDO A LETRA PERTENCE À PALAVRA E {F, F}, QUANDO 
         * NÃO PERTENCE. 
         * ESTE MÉTODO DEVE ATUALIZAR OS ATRIBUTOS m_tentativas_restantes, m_palavra_jogada E m_letras_palpitadas, PARA REFLETIR 
         * AS SITUAÇÕES CITADAS. NO CASO DA LETRA JÁ TER SIDO ESCOLHIDA, O MÉTODO NÃO DEVE ATUALIZAR m_tentativas_restantes. 
         * @param palpite UMA LETRA, QUE DEVE SER TESTADA SE PERTENCE À PALAVRA. 
         * @return {T,T} SE O PALPITE PERTENCE À PALAVRA E É UM PALPITE NOVO, {F,T} CASO NÃO PERTENÇA E É NOVO. 
         *         {T,F} OU {F,F} NO CASO DO PALPITE PERTENCER/NÃO PERTENCER À PALAVRA, MAS NÃO É NOVO. 
         */
        // letra pertence a palavra e letra nova (T, T)
        // letra não pertence e letra nova (F, T)
        // letra pertence e letra repetida (T, F)
        // letra não pertence e letra repetida (F, F) 
        pair<bool, bool> palpite(char palp);
 
        /** 
         * EM CASO DE GAME OVER OU DO JOGADOR TER ACERTADO A PALAVRA ESTE MÉTODO DEVE RETORNAR T. 
         * @return T CASO O m_tentativas_restantes DO JOGO ESTEJA IGUAL A 0 OU SE O USUÁRIO  
         *         ACERTOU TODA A PALAVRA, F CASO CONTRÁRIO. 
         */ 
        bool rodada_terminada();
 
        /** 
         * RESETA O VALOR DE TENTATIVAS RESTANTES PARA 6 E DO ATRIBUTO m_letras_palpitadas PARA VAZIO 
         * ESTE MÉTODO É ÚTIL NO CASO DO JOGADOR ESCOLHER CONTINUAR O JOGO, OU NO INÍCIO 
         * DE CADA RODADA, RESETANDO O VALOR DE TENTATIVAS RESTANTES PARA 6 E DO ATRIBUTO 
         * m_letras_palpitadas COMO SENDO UM VETOR VAZIO 
         */ 
        void reset_rodada();

        void reinicia_jogo(bool reinicia);
 
        /** 
         * RETORNA A QUANTIDADE DE TENTATIVAS RESTANTES. 
         * @return A QUANTIDADE DE TENTATIVAS RESTANTES. 
         */ 
        int get_tentativas_restantes();

        /*CRIA O BONECO DE ACORDO COM AS TENTATIVAS RESTANTES*/
        void boneco();

        vector<string> fatiamento(string pa);


        string dica_jogador();

        void score_tabela();
};