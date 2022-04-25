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
            int count=0, pos, count1=0, qnt=0;
            string palavra, freq;
            string linha, linha2;
            string dificult, jogador, pont; 
            vector<int> pos_pv;
            pair<pair<bool, string>, pair<int, string>> erro;
            // ABRE OS ARQUIVOS PARA LEITURA DOS DADOS
            arq_palavras.open(m_arquivo_palavras, ios::in);
            arq_scores.open(m_arquivo_scores, ios::in);
            // LER O CONTEÚDO DO ARQUIVO DE PALAVRAS LINHA A LINHA ENQUANDO NÃO CHEGAR AO FINAL DO ARQUIVO
            while(!arq_palavras.eof()){
                getline(arq_palavras, linha);   // LER A LINHA INTEIRA
                count++;                        // CONTABILIZA A QUANTIDADE DE LINHAS
                for(int k=0; k < (int)linha.size(); k++){   // PERCORRE A LINHA
                // SE ENCONTRAR UM NÚMERO ELE GUARDA A POSIÇÃO ANTERIOR QUE É O ESPAÇO EM BRANCO E GUARDA A POSIÇÃO NA VARIÁVEL "pos"
                    if(isdigit(linha[k])){
                        palavra = linha.substr(0, k-1);   // ARMAZENA A PARTE DA LINHA QUE CONTÉM A PALAVRA
                        pos = k-1;
                        break;
                    }
                }
                freq = linha.substr(pos, linha.size()-1); // UTILIZA A POSIÇÃO DO ESPAÇO EM BRANCO PARA ARMAZENAR A PARTE DA LINHA QUE CONTÉM A FREQUÊNCIA
                for(int i=0; i < (int)palavra.size(); i++){ // PERCORRE A PALAVRA PARA ANALISAR OS POSSÍVEIS ERROS
                    if(ispunct(palavra[i]) && (palavra[i] != '-')){  //CASO ENCONTRE ALGUM CARACTERE ESPECIAL NA PALAVRA, EXCETO O HÍFEN, RETORNA O ERRO DO TIPO CARACTERE ESPECIAL
                        return pair<pair<bool, string>, pair<int, string>>{{false, "Caractere especial encontrado"}, {count, palavra}};
                    } else if(isspace(palavra[i])){  //CASO ENCONTRE ALGUM ESPAÇO EM BRANCO NA PALAVRA, RETORNA O ERRO DO TIPO ESPAÇO EM BRANCO
                        return pair<pair<bool, string>, pair<int, string>>{{false, "Espaço em branco encontrado"}, {count, palavra}};
                    } else if(palavra.size() <= 4){  //CASO ENCONTRE ALGUMA PALAVRA COM TAMANHO <=4, RETORNA O ERRO DO TIPO TAMANHO DA PALAVRA <=4
                        return pair<pair<bool, string>, pair<int, string>>{{false, "Palavra com tamanho menor ou igual a 4"}, {count, palavra}};
                    } else if(stoi(freq) < 0){   //CASO ENCONTRE ALGUMA FREQUÊNCIA NEGATIVA, RETORNA O ERRO DO TIPO FREQUÊNCIA NEGATIVA
                        return pair<pair<bool, string>, pair<int, string>>{{false, "Frequência Negativa"}, {count, freq}};
                    }
                }  
            }
            // LER O CONTEÚDO DO ARQUIVO DE SCORES LINHA A LINHA ENQUANDO NÃO CHEGAR AO FINAL DO ARQUIVO
            while(!arq_scores.eof()){
                getline(arq_scores, linha2); // LER A LINHA INTEIRA
                count1++;                   // CONTABILIZA A QUANTIDADE DE LINHAS
                for(int k=0; k < (int)linha2.size(); k++){ //PERCORRE A LINHA
                    if(linha2[k] == ';'){ // SE ENCONTRAR UM ';' SOMA +1 NA VARIÁVEL qnt
                        pos_pv.push_back(k);
                        qnt++;
                    }
                }
                if(qnt != 3){ // CASO O N° DE ';' SEJA > OU < QUE 3 RETORNA O ERRO DE EXCESSO OU FALTA DE ';'
                    return pair<pair<bool, string>, pair<int, string>>{{false, "Excesso ou falta de ;"}, {count1, ""}};
                }
                qnt = 0; // ZERA A VARIÁVEL qnt PARA SER USADA NA LEITURA DA PRÓXIMA LINHA
                // VERIFICA SE OS CAMPOS DE DIFICULDADE, NOME DO JOGADOR(A) OU PONTUAÇÃO DO ARQUIVO DE SCORES ESTÃO VAZIOS E RETORNA A RAZÃO DO ERRO E A LINHA
                dificult = linha2.substr(0, pos_pv[0]);
                jogador = linha2.substr(pos_pv[0], pos_pv[1]);
                pont = linha2.substr(pos_pv[2], -1);
                if((dificult.size() == 0) || (jogador.size() == 0) || (pont.size() == 0)){
                    return pair<pair<bool, string>, pair<int, string>>{{false, "Campo vazio"}, {count1, ""}};
                }
                pos_pv.clear();
            }
            // FECHA OS ARQUIVOS
            arq_palavras.close();
            arq_scores.close();
            // SE NÃO OCORRER NENHUM DOS ERROS, RETORNA {TRUE, "VÁLIDO"}
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
            // ABRE OS ARQUIVOS PARA LEITURA DOS DADOS
            arquivo_palavras.open(m_arquivo_palavras, ios::in);
            arquivo_scores.open(m_arquivo_scores, ios::in);
            // CASO A FUNÇÃO OPEN() NÃO CONSIGA ABRIR OS ARQUIVOS A FUNÇÃO IMPRIME O ERRO DO TIPO INEXISTÊNCIA DE ARQUIVO E ENCERRA O PROGRAMA
            if(!arquivo_palavras.is_open() && (!arquivo_scores.is_open())){
                cout << "Erro: Arquivo base_formatada.txt e Arquivo base_scores.txt inexistentes" << endl;
                exit(0);
            } else if(!arquivo_palavras.is_open()){
                cout << "Erro: Arquivo base_formatada.txt inexistente" << endl;
                exit(0);
            } else if(!arquivo_scores.is_open()){
                cout << "Erro: Arquivo base_scores.txt inexistente" << endl;
                exit(0);
            }
            // LER O CONTEÚDO DO ARQUIVO DE PALAVRAS LINHA A LINHA ENQUANDO NÃO CHEGAR AO FINAL DO ARQUIVO
            while(!arquivo_palavras.eof()){
                getline(arquivo_palavras, line); // LER A LINHA INTEIRA
                for(int k=0; k < (int)line.size(); k++){
                    // SE ENCONTRAR UM NÚMERO ELE GUARDA A POSIÇÃO ANTERIOR QUE É O ESPAÇO EM BRANCO PARA FAZER O "FATIAMENTO" DA STRING line
                    if(isdigit(line[k])){
                        pos = k-1;
                        break;
                    }
                }
                palavra = (line.substr(0, pos));    // ARMAZENA A PALAVRA NA VARIÁVEL palavra 
                freq = stoi(line.substr(pos+1, line.size()-2)); // ARMAZENA A FREQUÊNCIA NA VARIÁVEL freq
                m_palavras.push_back(make_pair(palavra, freq)); // ARMAZENA A PALAVRA E SUA RESPECTIVA FREQUÊNCIA EM UM VETOR DE PARES
            }
            string line1;
            // LER O CONTEÚDO DO ARQUIVO DE SCORES LINHA A LINHA ENQUANDO NÃO CHEGAR AO FINAL DO ARQUIVO
            while(!arquivo_scores.eof()){
                getline(arquivo_scores, line1, ';'); // LER ATÉ ENCONTRAR O ';'
                string line2 = line1;
                getline(arquivo_scores, line1, ';'); // PARTINDO DA POSIÇÃO DO PRIMEIRO getline() LÊ ATÉ ENCONTRAR O ';'
                string line3 = line1;
                dificuldade_jogador.push_back(make_pair(line2, line3)); // ARMAZENA A DIFICULDADE E O NOME DO JOGADOR(A) NO VETOR DE PARES dificuldade_jogador 
                getline(arquivo_scores, line1, ';'); // PARTINDO DA POSIÇÃO DO SEGUNDO getline() LÊ ATÉ ENCONTRAR O ';'
                palavras.push_back(line1); //ARMAZENA A(S) PALAVRA(S) ACERTADAS PELO JOGADOR(A)
                getline(arquivo_scores, line1, '\n'); // PARTINDO DA POSIÇÃO DO TERCEIRO getline() LER ATÉ ENCONTRAR O FINAL DA LINHA (\n)
                pont.push_back(stoi(line1)); // ARMAZENA A PONTUAÇÃO DO JOGADOR(A)
            }
            // FECHA OS ARQUIVOS
            arquivo_palavras.close();
            arquivo_scores.close();
        }

        /*DETERMINA:
            # A SOMA DE TODAS AS FREQUÊNCIAS DO VETOR DE PARES m_palavras
            # A QUANTIDADE DE PALAVRAS PRESENTES NO VETOR DE PARES m_palavras
            # A MÉDIA DAS FREQUÊNCIAS DAS PALAVRAS*/
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
            vector<string> nivel_facil; // VETOR PARA ARMAZENAR AS PALAVRAS DO NÍVEL FÁCIL
            vector<string> nivel_medio; // VETOR PARA ARMAZENAR AS PALAVRAS DO NÍVEL MÉDIO
            vector<string> nivel_dificil; // VETOR PARA ARMAZENAR AS PALAVRAS DO NÍVEL DIFÍCIL
            int sorteio;
            unsigned semente = time(NULL); // PARA AUMENTAR A ALEATORIEDADE DA FUNÇÃO rand(), ALTERANDO A SEMENTE A CADA COMPILAÇÃO
            srand(semente);
            if(m_dificuldade == 0){ 
                for(int i=0; i < (int)m_palavras.size(); i++){ // PERCORRE O VETOR m_palavras
                    if(m_palavras[i].second > media_p){ // SE A FREQUÊNCIA FOR MAIOR QUE A MÉDIA, ARMAZENA EM nivel_facil
                         nivel_facil.push_back(m_palavras[i].first);
                    }
                }
                for(int k=0; k < 10; k++){ // FAZ O SORTEIO DAS 10 PALAVRAS E ARMAZENA NO VETOR m_palavras_do_jogo
                    sorteio = rand()%nivel_facil.size();
                    m_palavras_do_jogo.push_back(nivel_facil[sorteio]);
                }
            } else if (m_dificuldade == 1){
                for(int i=0; i < (int)m_palavras.size(); i++){ // PERCORRE O VETOR m_palavras
                    if(i <= (int)(20/3)){   // ATÉ 1/3 DAS PALAVRAS VERIFICA SE A FREQUÊNCIA É MAIOR QUE A MÉDIA E ARMAZENA EM nivel_medio
                        if(m_palavras[i].second > media_p){ 
                            nivel_medio.push_back(m_palavras[i].first);
                        }  
                    } else{ // NO RESTANTE DAS PALAVRAS VERIFICA SE A FREQUÊNCIA É MENOR OU IGUAL QUE A MÉDIA E ARMAZENA EM nivel_medio
                        if(m_palavras[i].second <= media_p){
                            nivel_medio.push_back(m_palavras[i].first);
                        }  
                    }
                }
                for(int k=0; k < 20; k++){  // FAZ O SORTEIO DAS 20 PALAVRAS E ARMAZENA NO VETOR m_palavras_do_jogo
                    sorteio = rand()%nivel_medio.size();
                    m_palavras_do_jogo.push_back(nivel_medio[sorteio]);
                }
            } else if(m_dificuldade == 2){
                for(int i=0; i < (int)m_palavras.size(); i++){ // PERCORRE O VETOR m_palavras
                    if(i <= 22){ // ATÉ 3/4 DAS PALAVRAS VERIFICA SE A FREQUÊNCIA É MENOR QUE A MÉDIA E ARMAZENA EM nivel_dificil
                        if(m_palavras[i].second < media_p){
                            nivel_dificil.push_back(m_palavras[i].first);
                        }  
                    } else{ // NO RESTANTE DAS PALAVRAS VERIFICA SE A FREQUÊNCIA É MAIOR OU IGUAL QUE A MÉDIA E ARMAZENA EM nivel_dificil
                        if(m_palavras[i].second >= media_p){
                            nivel_dificil.push_back(m_palavras[i].first);
                        }  
                    }
                }
                for(int k=0; k < 30; k++){  // FAZ O SORTEIO DAS 30 PALAVRAS E ARMAZENA NO VETOR m_palavras_do_jogo
                    sorteio = rand()%nivel_dificil.size();
                    m_palavras_do_jogo.push_back(nivel_dificil[sorteio]);
                }
            }
            random_shuffle(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end()); //EMBARALHA A ORDEM DAS PALAVRAS
            m_palavra_atual = m_palavras_do_jogo[rand()%((int)m_palavras_do_jogo.size()-1)]; // SORTEIA UMA PALAVRA PARA SER USADA NA PARTIDA
            m_palavra_jogada = m_palavra_atual;
            for(int i=0; i < (int)m_palavra_atual.size(); i++){ // PERCORRE m_palavra_atual E ALTERA CADA CARACTERE POR UM UNDERLINE('_')
                m_palavra_jogada[i] = '_';
            }
            return m_palavra_jogada; // RETORNA A PALAVRA SORTEADA NO FORMATO “_ _ _ ... _ “
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
            for(int i=0; i < (int)m_palavra_atual.size(); i++){ // PERCORRE m_palavra_atual
                if (m_palavra_atual[i] == palp){ // SE ALGUM CARACTERE COINCIDIR COM O PALPITE DO JOGADOR(A) SUBSTUI-O EM m_palavra_jogada
                    m_palavra_jogada[i] = palp;
                }
            }
            return m_palavra_jogada; // RETORNA m_palavra_jogada ATUALIZADA
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
            if(m_letras_palpitadas.size() == 0){ // CASO SEJA O PRIMEIRO PALPITE DO JOGADOR(A)
               m_letras_palpitadas.push_back(palp); // ARMAZENA O PALPITE
                if (m_palavra_atual.find(palp) < m_palavra_atual.size()){ // SE O PALPITE ESTIVER CONTIDO EM m_palavra_atual RETORNA {T, T}
                    return pair<bool, bool>{true, true}; 
                } else if (m_palavra_atual.find(palp) > m_palavra_atual.size()){ // SE O PALPITE NÃO ESTIVER CONTIDO EM m_palavra_atual SUBTRAI -1 DE m_tentativas_restantes E RETORNA {F, T}
                    m_tentativas_restantes--;
                    return pair<bool, bool>{false, true};
                }
            } else{
               for(int k=0; k < (int)m_letras_palpitadas.size(); k++){ //PERCORRE m_letras_palpitadas
                    if(m_letras_palpitadas[k] == palp){ // SE O PALPITE ESTIVER CONTIDO NO VETOR ALTERA A VARIAVEL exist PARA 1
                        exist = 1;
                    }
                }
                if (m_palavra_atual.find(palp) < m_palavra_atual.size() && (exist != 1)){ // SE O PALPITE ESTIVER CONTIDO EM m_palavra_atual E A LETRA FOR NOVA, RETORNA {T, T}
                    m_letras_palpitadas.push_back(palp);
                    return pair<bool, bool>{true, true}; 
                } else if (m_palavra_atual.find(palp) > m_palavra_atual.size() && (exist != 1)){ // SE O PALPITE NÃO ESTIVER CONTIDO EM m_palavra_atual E A LETRA FOR NOVA, SUBTRAI -1 DE m_tentativas_restantes E RETORNA {F, T}
                    m_tentativas_restantes--;
                    m_letras_palpitadas.push_back(palp);
                    return pair<bool, bool>{false, true};
                } else if(m_palavra_atual.find(palp) < m_palavra_atual.size() && (exist == 1)){ // SE O PALPITE ESTIVER CONTIDO EM m_palavra_atual E A LETRA FOR REPETIDA, RETORNA {T, F}
                    return pair<bool, bool>{true, false};
                } else if(m_palavra_atual.find(palp) > m_palavra_atual.size() && (exist == 1)){// SE O PALPITE NÃO ESTIVER CONTIDO EM m_palavra_atual E A LETRA FOR REPETIDA, RETORNA {F, F}
                    return pair<bool, bool>{false, false};
                }
            }
            exist = 0; // ZERA A VARIÁVEL exist PARA SER USADA A CADA NOVO PALPITE
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
         * RESETA O VALOR DE TENTATIVAS RESTANTES PARA 6 E DO ATRIBUTO m_letras_palpitadas PARA VAZIO 
         * ESTE MÉTODO É ÚTIL NO CASO DO JOGADOR ESCOLHER CONTINUAR O JOGO, OU NO INÍCIO 
         * DE CADA RODADA, RESETANDO O VALOR DE TENTATIVAS RESTANTES PARA 6 E DO ATRIBUTO 
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
            //SE AS TENTATIVAS RESTANTES FOREM <=5 IMPRIME A CABEÇA DO BONECO
            if(get_tentativas_restantes() <= 5){
                    cout << " O " << endl;
            } else{
                /*CASO AINDA NÃO TENHA OCORRIDO NENHUM ERRO, OU SEJA, O NÚMERO DE TENTATIVAS AINDA SEJA 6,
                IMPRIME OS ESPAÇOS EM BRANCO QUE SEPARAM A FRASE DO PALPITE DA PALAVRA.*/
                cout << endl;
                cout << endl;
            }
            //SE AS TENTATIVAS RESTANTES FOREM <=4 IMPRIME UM DOS BRAÇOS DO BONECO
            if(get_tentativas_restantes() <= 4){
                    cout << "/";
            }
            //SE AS TENTATIVAS RESTANTES FOREM <=3 IMPRIME O TRONCO DO BONECO
            if(get_tentativas_restantes() <= 3){
                cout << "|";
            }
            //SE AS TENTATIVAS RESTANTES FOREM <=2 IMPRIME O OUTRO BRAÇO DO BONECO
            if(get_tentativas_restantes() <= 2){
                cout << "\\" << endl;
            }
            //SE AS TENTATIVAS RESTANTES FOREM <=1 IMPRIME UMA DAS PERNAS DO BONECO
            if(get_tentativas_restantes() <= 1){
                cout << "/";
            }
            //SE AS TENTATIVAS RESTANTES FOREM <=0 IMPRIME A OUTRA PERNA DO BONECO
            if(get_tentativas_restantes() <= 0){
                cout << " \\" << endl;
            }
            // PARA PADRONIZAR O ESPAÇO ENTRE O BONECO E A PALAVRA
            if(get_tentativas_restantes() == 4 || get_tentativas_restantes() == 3 || get_tentativas_restantes() == 1){
                cout << endl;
                cout << endl;
            } else{
                cout << endl; 
            }
        };
};