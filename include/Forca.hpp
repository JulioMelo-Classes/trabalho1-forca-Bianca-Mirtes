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
        vector< pair<string, int> > m_palavras; //<! palavras e sua ocorrência no Corpus

        string m_arquivo_scores; //<! nome do arquivo contendo os scores
 
        string m_arquivo_palavras; //<! nome do arquivo contendo as palavras
 
        Dificuldade m_dificuldade;
        //= Dificuldade::FACIL; //<! dificuldade atual do jogo
 
        vector< string > m_palavras_do_jogo; //<! container “Palavras do Jogo”
        vector< char > m_letras_palpitadas; //<! contem as letras palpitadas pelo jogador
        string m_palavra_atual; //<! palavra sendo jogada “atualmente”
        string m_palavra_jogada; //<! palavra sendo jogada “atualmente” no formato “_ _ _ ... _ “
        
        int m_tentativas_restantes=0; //TODO: armazenar tentativas restantes
        int qnt_palavras;
        int media_p;
        int soma_freq=0;
   
    public:
        /**
         * Cria a um objeto Forca
         * O construtor pode ou não validar os arquivos de entrada, no entanto, mesmo com 
         * os arquivos inválidos o objeto deve ser construído. Para o caso de arquivos de palavras
         * ou scores inválidos, use o método eh_valido.
         * @param palavras o arquivo que contém as palavras
         * @param scores o nome do arquivo que contém os scores
         * @see eh_valido
         */
        Forca( string palavras, string scores ){
            m_arquivo_palavras = palavras;
            m_arquivo_scores = scores;
        };
       
 
        /**
         * Valida os arquivos de entrada de acordo com as especificações.
         * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a 
         * razão correspondente de acordo com as especificações.
         * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
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
         * Carrega os arquivos de scores e palavras preenchendo **ao menos** a estrutura m_palavras
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

        void dados(){
            for(int i=0; i < (int)m_palavras.size(); i++){
                soma_freq += m_palavras[i].second;
            }
            media_p = soma_freq/(int)m_palavras.size();
            qnt_palavras = (int)m_palavras.size();
        };
        /**
         * Modifica a dificuldade do jogo.
         * Este método modifica a dificuldade do jogo gerando um novo vetor palavras_do_jogo
         * toda vez que é chamado.
         * @param d a dificuldade desejada
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
         * Retorna a próxima palavra de acordo com a dificuldade atual.
         * Este método deve atualizar o valor dos atributos m_palavra_atual, com a palavra atual,
         * do atributo m_palavra_jogada com um texto no formato "_ _ _ _ ... _".
         * O método também deve sortear as letras que devem aparecer dependendo do nível de dificuldade,
         * alterando o valor de m_palavra_jogada de acordo.
         * @return o valor do atributo m_palavra_jogada.
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
         * Retorna a palavra atual que está sendo jogada.
         * Diferente do método proxima_palavra(), este método __não atualiza__ o atributo
         * m_palavra_atual, apenas retorna o atributo m_palavra_jogada que é a palavra no
         * formato  "_ _ _ _ ... _" contendo todas as letras
         * já acertadas/sorteadas ao invés de “_”.
         * @return a palavra atualmente sendo jogada.
         */
        string get_palavra_jogada();

        /**
         * Retorna o valor da palavra atual, útil no caso de um game over, para mostrar a palavra que estava
         * sendo jogada
         * @return o valor do atributo palavra_atual
         **/
        string get_palavra_atual(){
            return m_palavra_atual;
        };
 
        /**
         * Testa se uma letra pertence á palavra atual e se já foi jogada pelo jogador.
         * Este método testa se uma letra pertence à palavra atual, caso a letra pertença a palavra
         * e ainda não foi jogada o método retorna {T, T}, caso a letra não pertença à palavra o método retorna {F,T}; 
         * Caso a letra já tenha sido jogada o método retorna {T, F}, quando a letra pertence à palavra e {F, F}, quando
         * não pertence.
         * Este método deve atualizar os atributos m_tentativas, m_palavra_jogada e m_letras_palpitadas, para refletir
         * as situações citadas. No caso da letra já ter sido escolhida, o método não deve atualizar m_tentativas.
         * @param palpite uma letra, que deve ser testada se pertence à palavra.
         * @return {T,T} se o palpite pertence à palavra e é um palpite novo, {F,T} caso não pertença e é novo.
         *         {T,F} ou {F,F} no caso do palpite pertencer/não pertencer à palavra, mas não é novo.
         */


        // letra pertence a palavra e letra nova (T, T)
        // letra não pertence e letra nova (F, T)
        // letra pertence e letra repetida (T, F)
        // letra não pertence e letra repetida (F, F) 
        pair<bool, bool> palpite(char palpite){
            int exist=0;
            if(m_letras_palpitadas.size() != 0){
                for(int k=0; k < (int)m_letras_palpitadas.size(); k++){
                    if(m_letras_palpitadas[k] == palpite){
                        exist = 1;
                    }
                }
                for(int i=0; i < (int)m_palavra_atual.size(); i++){
                    if (m_palavra_atual[i] == palpite && exist != 1){
                        m_letras_palpitadas.push_back(palpite);
                        return pair<bool, bool>{true, true}; 
                    } else if (m_palavra_atual[i] != palpite && exist != 1){
                        m_letras_palpitadas.push_back(palpite);
                        return pair<bool, bool>{false, true};
                    } else if(m_palavra_atual[i] == palpite && exist == 1){
                        return pair<bool, bool>{true, false};
                    } else if(m_palavra_atual[i] != palpite && exist == 1){
                        return pair<bool, bool>{false, false};
                    }
                }
            } else{  
                m_letras_palpitadas.push_back(palpite);
                for(int i=0; i < (int)m_palavra_atual.size(); i++){
                    if (m_palavra_atual[i] == palpite){
                        return pair<bool, bool>{true, true}; 
                    } else if (m_palavra_atual[i] != palpite){
                        return pair<bool, bool>{false, true};
                    }
                }
            }
        };
 
        /**
         * Em caso de Game Over ou do jogador ter acertado a palavra este método deve retornar T.
         * @return T caso o m_tentativas_restantes do jogo esteja igual a 0 ou se o usuário 
         *         acertou toda a palavra, F caso contrário.
         */
        bool rodada_terminada(){
            if(get_tentativas_restantes() == 6){
                return true;
            }
            else{
                return false;
            }
        };
 
        /**
         * Reseta o valor de tentativas restantes para 5 e do atributo m_letras_palpitadas para vazio
         * Este método é útil no caso do jogador escolher continuar o jogo, ou no início
         * de cada rodada, resetando o valor de tentativas restantes para 5 e do atributo
         * m_letras_palpitadas como sendo um vetor vazio
         */
        void reset_rodada();
 
        /**
         * Retorna a quantidade de tentativas restantes.
         * @return a quantidade de tentativas restantes.
         */
        int get_tentativas_restantes(){
            m_tentativas_restantes++;
            return m_tentativas_restantes;
        };

};