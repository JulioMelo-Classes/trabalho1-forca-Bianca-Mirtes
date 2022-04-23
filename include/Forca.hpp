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

using namespace std;
 
class Forca {
    public:
        enum Dificuldade{
            FACIL, MEDIO, DIFICIL
        };
    private:
        //TODO: armazenar os scores?
        vector< pair<string, int> > m_palavras; //<! PALAVRAS E SUA OCORRÊNCIA NO CORPUS 

        string m_arquivo_scores; //<! NOME DO ARQUIVO CONTENDO OS SCORES 
 
        string m_arquivo_palavras; //<! NOME DO ARQUIVO CONTENDO AS PALAVRAS 
 
        Dificuldade m_dificuldade; //<! DIFICULDADE ATUAL DO JOGO 
 
        vector< string > m_palavras_do_jogo; //<! CONTAINER “PALAVRAS DO JOGO”
        vector< char > m_letras_palpitadas; //<! CONTEM AS LETRAS PALPITADAS PELO JOGADOR
        string m_palavra_atual; //<! PALAVRA SENDO JOGADA “ATUALMENTE”
        string m_palavra_jogada; //<! PALAVRA SENDO JOGADA “ATUALMENTE” NO FORMATO “_ _ _ ... _ “ 
        
        int m_tentativas_restantes=6; // ARMAZENA AS TENTATIVAS RESTANTES
        int qnt_palavras;
        int media_p;
        int soma_freq=0;
   
    public:
        /** 
         * CRIA A UM OBJETO FORCA 
         * O CONSTRUTOR PODE OU NÃO VALIDAR OS ARQUIVOS DE ENTRADA, NO ENTANTO, MESMO COM  
         * OS ARQUIVOS INVÁLIDOS O OBJETO DEVE SER CONSTRUÍDO. PARA O CASO DE ARQUIVOS DE PALAVRAS 
         * OU SCORES INVÁLIDOS, USE O MÉTODO eh_valido(). 
         * @param PALAVRAS O NOME DO ARQUIVO QUE CONTÉM AS PALAVRAS 
         * @param SCORES O NOME DO ARQUIVO QUE CONTÉM OS SCORES 
         * @see EH_VALIDO 
         */
        Forca( string palavras, string scores ){
            m_arquivo_palavras = palavras;
            m_arquivo_scores = scores;
        };
       
 
        /**
         * VALIDA OS ARQUIVOS DE ENTRADA DE ACORDO COM AS ESPECIFICAÇÕES.
         * AO VALIDAR OS ARQUIVOS, NO CASO DE ARQUIVOS INVÁLIDOS, ESTE MÉTODO DEVE RETORNAR A  
         * RAZÃO CORRESPONDENTE DE ACORDO COM AS ESPECIFICAÇÕES. 
         * @return {T,""} SE OS ARQUIVOS ESTIVEREM VÁLIDOS, {F,"RAZÃO"} CASO CONTRÁRIO. 
         */
        pair<pair<bool, string>, pair<int, string>> eh_valido(){
            fstream arq_palavras;
            fstream arq_scores;
            int count=0, pos, count1, qnt=0;
            string palavra, freq;
            string linha, str;
            pair<pair<bool, string>, pair<int, string>> erro;
            arq_palavras.open(m_arquivo_palavras, ios::in);
            arq_scores.open(m_arquivo_scores, ios::in);
            if(!arq_palavras){
                return pair<pair<bool, string>, pair<int, string>>{{false, "Arquivo base_formatada.txt inexistente"}, {0, ""}};
            } else if(!arq_scores){
                return pair<pair<bool, string>, pair<int, string>>{{false, "Arquivos base_scores.txt inexistente"}, {0, ""}};
            } else{
                while(!arq_palavras.eof()){
                    getline(arq_palavras, linha);
                    count++;
                    for(int k=0; k < (int)linha.size(); k++){
                        if(isspace(linha[k])){
                            palavra = linha.substr(0, k);
                            pos = k;
                            break;
                        }
                    }
                    freq = linha.substr(pos+1, linha.size()-1);
                    count++;
                    for(int i=0; i < (int)palavra.size(); i++){
                       if(ispunct(linha[i]) && (linha[i] != '-')){
                            return pair<pair<bool, string>, pair<int, string>>{{false, "Caractere especial encontrado"}, {count, palavra}};
                       } else if(isspace(linha[i])){
                            return pair<pair<bool, string>, pair<int, string>>{{false, "Espaço em branco encontrado"}, {count, palavra}};
                       } else if(palavra.size() <= 4){
                            return pair<pair<bool, string>, pair<int, string>>{{false, "Palavra com tamanho menor ou igual a 4"}, {count, palavra}};
                       } else if(stoi(freq) < 0){
                            return pair<pair<bool, string>, pair<int, string>>{{false, "Frequência Negativa"}, {count, freq}};
                       }
                    }  
                }
                while(!arq_scores.eof()){
                    getline(arq_scores, linha);
                    count1++;
                    for(int k=0; k < (int)linha.size(); k++){
                        if(linha[k] == ';'){
                            qnt++;
                        }   
                    }
                    if(qnt != 3){
                        return pair<pair<bool, string>, pair<int, string>>{{false, "Excesso ou falta de ;"}, {count1, ""}};
                    }
                    qnt = 0;
                }
            }
            return pair<pair<bool, string>, pair<int, string>> {{true, "Válido"}, {0, ""}};
        };
 
        /** 
         * CARREGA OS ARQUIVOS DE SCORES E PALAVRAS PREENCHENDO **AO MENOS** A ESTRUTURA m_palavras 
         */ 
        void carregar_arquivos(){
            fstream arquivo_palavras;
            fstream arquivo_scores;
            string line, palavra;
            int freq, pos;
            arquivo_palavras.open(m_arquivo_palavras, ios::in);
            arquivo_scores.open(m_arquivo_scores, ios::in);
            while(!arquivo_palavras.eof()){
                getline(arquivo_palavras, line);
                for(int k=0; k < (int)line.size(); k++){
                    if(isdigit(line[k])){
                        pos = k-1;
                        break;
                    }
                }
                palavra = (line.substr(0, pos));
                freq = stoi(line.substr(pos+1, line.size()-2));
                m_palavras.push_back(make_pair(palavra, freq));
            }
            vector<pair<string, string>> dificuldade_jogador;
            vector<string> palavras;
            vector<int> pont;
            string line1;
            while(!arquivo_scores.eof()){
                getline(arquivo_scores, line1, ';');
                string line2 = line1;
                getline(arquivo_scores, line1, ';');
                string line3 = line1;
                dificuldade_jogador.push_back(make_pair(line2, line3));
                getline(arquivo_scores, line1, ';');
                palavras.push_back(line1);
                getline(arquivo_scores, line1, '\n');
                pont.push_back(stoi(line1));
            }
            arquivo_palavras.close();
            arquivo_scores.close();
        }

        /*DETERMINA:
            # A SOMA DE TODAS AS FREQUÊNCIAS DO VETOR DE PARES m_palavras
            # A QUANTIDADE DE PALAVRAS PRESENTES NO VETOR DE PARES m_palavras
            # MÉDIA DA FREQUÊNCIA DAS PALAVRAS*/
        void dados(){
            for(int i=0; i < (int)m_palavras.size(); i++){
                soma_freq += m_palavras[i].second;
            }
            media_p = soma_freq/(int)m_palavras.size();
            qnt_palavras = (int)m_palavras.size();
        };

        /** 
         * MODIFICA A DIFICULDADE DO JOGO. 
         * ESTE MÉTODO MODIFICA A DIFICULDADE DO JOGO GERANDO UM NOVO VETOR m_palavras_do_jogo
         * TODA VEZ QUE É CHAMADO. 
         * @param d A DIFICULDADE DESEJADA 
         * @see proxima_palavra 
         */ 
        void set_dificuldade(int d){
            if (d == 0){
                m_dificuldade = FACIL;
            } else if(d == 1){
                m_dificuldade = MEDIO;
            } else if(d == 2){
                m_dificuldade = DIFICIL;
            }
        };
 
        /** 
         * RETORNA A PRÓXIMA PALAVRA DE ACORDO COM A DIFICULDADE ATUAL. 
         * ESTE MÉTODO DEVE ATUALIZAR O VALOR DOS ATRIBUTOS m_palavra_atual, COM A PALAVRA ATUAL, 
         * DO ATRIBUTO m_palavra_jogada COM UM TEXTO NO FORMATO "_ _ _ _ ... _". 
         * O MÉTODO TAMBÉM DEVE SORTEAR AS LETRAS QUE DEVEM APARECER DEPENDENDO DO NÍVEL DE DIFICULDADE, 
         * ALTERANDO O VALOR DE m_palavra_jogada DE ACORDO. 
         * @return O VALOR DO ATRIBUTO m_palavra_jogada. 
         */
        string proxima_palavra(){
            vector<string> nivel_facil;
            vector<string> nivel_medio;
            vector<string> nivel_dificil;
            int sorteio;
            unsigned semente = time(NULL);
            srand(semente);
            if(m_dificuldade == 0){ 
                for(int i=0; i < (int)m_palavras.size(); i++){
                    if(m_palavras[i].second > media_p){
                         nivel_facil.push_back(m_palavras[i].first);
                    }
                }
                for(int k=0; k < 10; k++){
                     sorteio = rand()%nivel_facil.size();
                     m_palavras_do_jogo.push_back(nivel_facil[sorteio]);

                }
            } else if (m_dificuldade == 1){
                for(int i=0; i < (int)m_palavras.size(); i++){
                    if(i <= int(20/3)){
                        if(m_palavras[i].second > media_p){
                            nivel_medio.push_back(m_palavras[i].first);
                        }  
                    } else{
                        if(m_palavras[i].second <= media_p){
                            nivel_medio.push_back(m_palavras[i].first);
                        }  
                    }
                }
                for(int k=0; k < 20; k++){
                    sorteio = rand()%nivel_medio.size();
                    m_palavras_do_jogo.push_back(nivel_medio[sorteio]);
                }
            } else{
                for(int i=0; i < (int)m_palavras.size(); i++){
                    if(i <= 22){
                        if(m_palavras[i].second > media_p){
                            nivel_dificil.push_back(m_palavras[i].first);
                        }  
                    } else{
                        if(m_palavras[i].second <= media_p){
                            nivel_dificil.push_back(m_palavras[i].first);
                        }  
                    }
                }
                for(int k=0; k < 30; k++){
                    sorteio = rand()%nivel_dificil.size();
                    m_palavras_do_jogo.push_back(nivel_dificil[sorteio]);
                }
            }
            random_shuffle(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end());
            m_palavra_atual = m_palavras_do_jogo[rand()%((int)m_palavras_do_jogo.size()-1)];
            m_palavra_jogada = m_palavra_atual;
            for(int i=0; i < (int)m_palavra_atual.size(); i++){
                m_palavra_jogada[i] = '_';
            }
            return m_palavra_jogada;
        };
 
         /** 
         * RETORNA A PALAVRA ATUAL QUE ESTÁ SENDO JOGADA. 
         * DIFERENTE DO MÉTODO proxima_palavra(), ESTE MÉTODO __NÃO ATUALIZA__ O ATRIBUTO 
         * m_palavra_atual, APENAS RETORNA O ATRIBUTO m_palavra_jogada QUE É A PALAVRA NO 
         * FORMATO  "_ _ _ _ ... _" CONTENDO TODAS AS LETRAS 
         * JÁ ACERTADAS/SORTEADAS AO INVÉS DE “_”. 
         * @return A PALAVRA ATUALMENTE SENDO JOGADA. 
         */ 
        string get_palavra_jogada(char palp){
            for(int i=0; i < (int)m_palavra_atual.size(); i++){
                if (m_palavra_atual[i] == palp){
                    m_palavra_jogada[i] = palp;
                }
            }
            return m_palavra_jogada;
        };

        /** 
         * RETORNA O VALOR DA PALAVRA ATUAL, ÚTIL NO CASO DE UM GAME OVER, PARA MOSTRAR A PALAVRA QUE ESTAVA 
         * SENDO JOGADA 
         * @return O VALOR DO ATRIBUTO m_palavra_atual 
         **/ 
        string get_palavra_atual(){
            return m_palavra_atual;
        };
 
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
        pair<bool, bool> palpite(char palp){
            int exist=0;
            if(m_letras_palpitadas.size() == 0){
               m_letras_palpitadas.push_back(palp);
                if (m_palavra_atual.find(palp) < m_palavra_atual.size()){
                    return pair<bool, bool>{true, true}; 
                } else if (m_palavra_atual.find(palp) > m_palavra_atual.size()){
                    m_tentativas_restantes--;
                    return pair<bool, bool>{false, true};
                }
            } else{
               for(int k=0; k < (int)m_letras_palpitadas.size(); k++){
                    if(m_letras_palpitadas[k] == palp){
                        exist = 1;
                    }
                }
                if (m_palavra_atual.find(palp) < m_palavra_atual.size() && (exist != 1)){
                    m_letras_palpitadas.push_back(palp);
                    return pair<bool, bool>{true, true}; 
                } else if (m_palavra_atual.find(palp) > m_palavra_atual.size() && (exist != 1)){
                    m_tentativas_restantes--;
                    m_letras_palpitadas.push_back(palp);
                    return pair<bool, bool>{false, true};
                } else if(m_palavra_atual.find(palp) < m_palavra_atual.size() && (exist == 1)){
                    return pair<bool, bool>{true, false};
                } else if(m_palavra_atual.find(palp) > m_palavra_atual.size() && (exist == 1)){
                    return pair<bool, bool>{false, false};
                }
            }
            exist = 0;
        };
 
        /** 
         * EM CASO DE GAME OVER OU DO JOGADOR TER ACERTADO A PALAVRA ESTE MÉTODO DEVE RETORNAR T. 
         * @return T CASO O m_tentativas_restantes DO JOGO ESTEJA IGUAL A 0 OU SE O USUÁRIO  
         *         ACERTOU TODA A PALAVRA, F CASO CONTRÁRIO. 
         */ 
        bool rodada_terminada(){
            if(get_tentativas_restantes() == 0 || m_palavra_jogada == m_palavra_atual){
                return true;
            }
            else{
                return false;
            }
        };
 
        /** 
         * RESETA O VALOR DE TENTATIVAS RESTANTES PARA 5 E DO ATRIBUTO m_letras_palpitadas PARA VAZIO 
         * ESTE MÉTODO É ÚTIL NO CASO DO JOGADOR ESCOLHER CONTINUAR O JOGO, OU NO INÍCIO 
         * DE CADA RODADA, RESETANDO O VALOR DE TENTATIVAS RESTANTES PARA 5 E DO ATRIBUTO 
         * m_letras_palpitadas COMO SENDO UM VETOR VAZIO 
         */ 
        void reset_rodada(){
            m_tentativas_restantes = 6;
            m_letras_palpitadas.clear();
        };
 
        /** 
         * RETORNA A QUANTIDADE DE TENTATIVAS RESTANTES. 
         * @return A QUANTIDADE DE TENTATIVAS RESTANTES. 
         */ 
        int get_tentativas_restantes(){
            return m_tentativas_restantes;
        };

        /*CRIA O BONECO DE ACORDO COM AS TENTATIVAS RESTANTES*/
        void boneco(){
            if(get_tentativas_restantes() <= 5){
                    cout << " O " << endl;
            } else{
                cout << endl;
                cout << endl;
            }
            if(get_tentativas_restantes() <= 4){
                    cout << "/";
            }
            if(get_tentativas_restantes() <= 3){
                cout << "|";
            }
            if(get_tentativas_restantes() <= 2){
                cout << "\\" << endl;
                        }
            if(get_tentativas_restantes() <= 1){
                cout << "/";
            }
            if(get_tentativas_restantes() <= 0){
                cout << " \\" << endl;
            }
            if(get_tentativas_restantes() == 4 || get_tentativas_restantes() == 3 || get_tentativas_restantes() == 1){
                cout << endl;
                cout << endl;
            } else{
                cout << endl; 
            }
        };

};