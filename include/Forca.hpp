#include <iostream>
#include <vector>
 
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
        Forca( std::string palavras, std::string scores );
       
 
        /**
         * Valida os arquivos de entrada de acordo com as especificações.
         * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a 
         * razão correspondente de acordo com as especificações.
         * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
         */
        std::pair<bool, std::string> eh_valido();
 
        /**
         * Carrega os arquivos de scores e palavras preenchendo **ao menos** a estrutura m_palavras
         */
        void carregar_arquivos();
 
        /**
         * Modifica a dificuldade do jogo.
         * Este método modifica a dificuldade do jogo gerando um novo vetor palavras_do_jogo
         * toda vez que é chamado.
         * @param d a dificuldade desejada
         * @see proxima_palavra
         */
        void set_dificuldade(Dificuldade d);
 
        /**
         * Retorna a próxima palavra de acordo com a dificuldade atual.
         * Este método deve atualizar o valor dos atributos m_palavra_atual, com a palavra atual,
         * do atributo m_palavra_jogada com um texto no formato "_ _ _ _ ... _".
         * O método também deve sortear as letras que devem aparecer dependendo do nível de dificuldade,
         * alterando o valor de m_palavra_jogada de acordo.
         * @return o valor do atributo m_palavra_jogada.
         */
        std::string proxima_palavra();
 
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
