#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

 
class Forca {
    public:
        enum Dificuldade{
            FACIL, MEDIO, DIFICIL
        };
    private:
        //TODO: armazenar os scores?
        std::vector< std::pair<std::string, int> > m_palavras; //<! palavras e sua ocorrência no Corpus

        std::string m_arquivo_scores; //<! nome do arquivo contendo os scores
 
        std::string m_arquivo_palavras; //<! nome do arquivo contendo as palavras
 
        Dificuldade m_dificuldade = Dificuldade::FACIL; //<! dificuldade atual do jogo
 
        std::vector< std::string > m_palavras_do_jogo; //<! container “Palavras do Jogo”
        std::vector< char > m_letras_palpitadas; //<! contem as letras palpitadas pelo jogador
        std::string m_palavra_atual; //<! palavra sendo jogada “atualmente”
        std::string m_palavra_jogada; //<! palavra sendo jogada “atualmente” no formato “_ _ _ ... _ “
        
        int m_tentativas_restantes; //TODO: armazenar tentativas restantes
   
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
        Forca( std::string palavras, std::string scores ){
            palavras = "base_formatada.txt";
            scores = "base_scores.txt";
        };
       
 
        /**
         * Valida os arquivos de entrada de acordo com as especificações.
         * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a 
         * razão correspondente de acordo com as especificações.
         * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
         */
        std::pair<std::pair<bool, std::string>, std::pair<int, std::string>> eh_valido(){
            std::fstream m_arquivo_palavras;
            std::fstream m_arquivo_scores;
            int count=0, pos;
            std::string palavra, freq;
            std::string linha, str;
            std::pair<std::pair<bool, std::string>, std::pair<int, std::string>> erro;
            m_arquivo_palavras.open("base_formatada.txt", std::ios::in);
            m_arquivo_scores.open("base_scores.txt", std::ios::in);
            if(!m_arquivo_palavras){
                return std::pair<std::pair<bool, std::string>, std::pair<int, std::string>>{{false, "Arquivo base_formatada.txt inexistente"}, {0, ""}};
            } else if(!m_arquivo_scores){
                return std::pair<std::pair<bool, std::string>, std::pair<int, std::string>>{{false, "Arquivos base_scores.txt inexistente"}, {0, ""}};
            } else{
                while(!m_arquivo_palavras.eof()){
                    getline(m_arquivo_palavras, linha);
                    count++;
                    for(int k=0; k < linha.size(); k++){
                        if(isspace(linha[k])){
                            palavra = linha.substr(0, k);
                            pos = k;
                            break;
                        }
                    }
                    freq = linha.substr(pos+1, linha.size()-1);
                    for(int i=0; i < palavra.size(); i++){
                       if(ispunct(linha[i])){
                            return std::pair<std::pair<bool, std::string>, std::pair<int, std::string>>{{false, "Caractere especial encontrado"}, {count, palavra}};
                       } else if(isspace(linha[i])){
                            return std::pair<std::pair<bool, std::string>, std::pair<int, std::string>>{{false, "Espaço em branco encontrado"}, {count, palavra}};
                       } else if(palavra.size() <= 4){
                            return std::pair<std::pair<bool, std::string>, std::pair<int, std::string>>{{false, "Palavra com tamanho menor ou igual a 4"}, {count, palavra}};
                       } else if(std::stoi(freq) < 0){
                            return std::pair<std::pair<bool, std::string>, std::pair<int, std::string>>{{false, "Frequência Negativa"}, {count, freq}};
                       }
                    }  
                }
            }
            return std::pair<std::pair<bool, std::string>, std::pair<int, std::string>> {{true, "Válido"}, {0, ""}};
        };
 
        /**
         * Carrega os arquivos de scores e palavras preenchendo **ao menos** a estrutura m_palavras
         */
        void carregar_arquivos(){
            std::fstream m_arquivo_palavras;
            std::fstream m_arquivo_scores;
            std::string line, palavra;
            int freq;
            int pos;
            m_arquivo_palavras.open("teste.txt", std::ios::in);
            m_arquivo_scores.open("base_scores.txt", std::ios::in);
            while(!m_arquivo_palavras.eof()){
                getline(m_arquivo_palavras, line);
                for(int k=0; k < line.size(); k++){
                    if(isdigit(line[k])){
                        pos = k-1;
                        break;
                    }
                }
                palavra = (line.substr(0, pos));
                freq = std::stoi(line.substr(pos+1, line.size()-2));
                m_palavras.push_back(std::make_pair(palavra, freq));
                }
            std::vector<std::pair<std::string, std::string>> dif_nome;
            std::vector<std::pair<std::vector<std::string>, int>> palavra_pont;
            std::string palavras;
            int pont;
            m_arquivo_palavras.close();
            m_arquivo_scores.close();
        }  

        /**
         * Modifica a dificuldade do jogo.
         * Este método modifica a dificuldade do jogo gerando um novo vetor palavras_do_jogo
         * toda vez que é chamado.
         * @param d a dificuldade desejada
         * @see proxima_palavra
         */
        void set_dificuldade(Dificuldade d){
            if (d == 0){
                m_dificuldade = Dificuldade::FACIL;
            } else if(d == 1){
                m_dificuldade = Dificuldade::MEDIO;
            } else{
                m_dificuldade = Dificuldade::DIFICIL;
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
        std::string proxima_palavra(){
            if(m_dificuldade == 0){
                
            }
        };
 
        /**
         * Retorna a palavra atual que está sendo jogada.
         * Diferente do método proxima_palavra(), este método __não atualiza__ o atributo
         * m_palavra_atual, apenas retorna o atributo m_palavra_jogada que é a palavra no
         * formato  "_ _ _ _ ... _" contendo todas as letras
         * já acertadas/sorteadas ao invés de “_”.
         * @return a palavra atualmente sendo jogada.
         */
        std::string get_palavra_jogada();

        /**
         * Retorna o valor da palavra atual, útil no caso de um game over, para mostrar a palavra que estava
         * sendo jogada
         * @return o valor do atributo palavra_atual
         **/
        std::string get_palavra_atual();
 
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
        std::pair<bool, bool> palpite(std::string palpite);
 
        /**
         * Em caso de Game Over ou do jogador ter acertado a palavra este método deve retornar T.
         * @return T caso o m_tentativas_restantes do jogo esteja igual a 0 ou se o usuário 
         *         acertou toda a palavra, F caso contrário.
         */
        bool rodada_terminada();
 
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
        int get_tentativas_restantes();

};
