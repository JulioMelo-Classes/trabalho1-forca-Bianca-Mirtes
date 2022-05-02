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
#include "Forca.hpp"
#include <iterator>

using namespace std;

Forca::Forca( string palavras, string scores ){
    m_arquivo_palavras = palavras;  // NOME DO ARQUIVO QUE CONTÉM A BASE DE PALAVRAS DO JOGO
    m_arquivo_scores = scores;      // NOME DO ARQUIVO QUE CONTÉM OS SCORES
};

pair<pair<bool, string>, pair<int, string>> Forca::eh_valido(){
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
    if(!arq_palavras.is_open()){ // CASO O ARQUIVO COM A BASE DE PALAVRAS DO JOGO NÃO EXISTA, A FUNÇÃO open() NÃO CONSEGUE ABRI-LO E RETORNA FALSE 
        return pair<pair<bool, string>, pair<int, string>> {{false, "Arquivo(s) Inexistente(s)"}, {0, m_arquivo_palavras}};
    } else if(!arq_scores.is_open()){ // CASO O ARQUIVO COM OS SCORES NÃO EXISTA, A FUNÇÃO open() NÃO CONSEGUE ABRI-LO E RETORNA FALSE
        return pair<pair<bool, string>, pair<int, string>> {{false, "Arquivo(s) Inexistente(s)"}, {0, m_arquivo_scores}};
    } else{
        // LER O CONTEÚDO DO ARQUIVO DE PALAVRAS LINHA A LINHA ENQUANDO NÃO CHEGAR AO FINAL DO ARQUIVO
        while(!arq_palavras.eof()){
            getline(arq_palavras, linha);   // LER A LINHA INTEIRA
            count++;                        // CONTABILIZA A QUANTIDADE DE LINHAS
            for(int k=0; k < (int)linha.size(); k++){ // PERCORRE A LINHA
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
            getline(arq_scores, linha2);    // LER A LINHA INTEIRA
            count1++;                       // CONTABILIZA A QUANTIDADE DE LINHAS
            for(int k=0; k < (int)linha2.size(); k++){ //PERCORRE A LINHA
                if(linha2[k] == ';'){       // SE ENCONTRAR UM ';' SOMA +1 NA VARIÁVEL qnt
                    pos_pv.push_back(k);    // ARMAZENA A POSIÇÃO DE TODOS OS ';'
                    qnt++;
                }
            }
            if(qnt > 3){ // CASO O N° DE ';' SEJA MAIOR QUE 3 RETORNA O ERRO EXCESSO DE ';'
                return pair<pair<bool, string>, pair<int, string>>{{false, "Excesso de ponto e vírgula"}, {count1, ""}};
            } else if(qnt < 3){ // CASO O N° DE ';' SEJA MENOR QUE 3 RETORNA O ERRO FALTA DE ';'
                return pair<pair<bool, string>, pair<int, string>>{{false, "Falta de ponto e vírgula"}, {count1, ""}};
            }
            qnt = 0;  // ZERA A VARIÁVEL qnt PARA SER USADA NA LEITURA DA PRÓXIMA LINHA
            dificult = linha2.substr(0, pos_pv[0]);                        // ARMAZENA A DIFICULDADE
            jogador = linha2.substr(pos_pv[0]+1, pos_pv[1]-(pos_pv[0]+1)); // ARMAZENA O NOME DO(A) JOGADOR(A) 
            pont = linha2.substr(pos_pv[2]+1, -1);                         // ARMAZENA A PONTUAÇÃO
            // VERIFICA SE OS CAMPOS DE DIFICULDADE, NOME DO JOGADOR(A) OU PONTUAÇÃO DO ARQUIVO DE SCORES ESTÃO VAZIOS E RETORNA A RAZÃO DO ERRO E A LINHA
            if(dificult.size() == 0){
                return pair<pair<bool, string>, pair<int, string>>{{false, "Campo DIFICULDADE vazio"}, {count1, ""}};
            } else if(jogador.size() == 0){
                return pair<pair<bool, string>, pair<int, string>>{{false, "Campo NOME vazio"}, {count1, ""}};
            } else if(pont.size()-1 == 0 && find(pont.begin(), pont.end(), '\n') != pont.end()){
                return pair<pair<bool, string>, pair<int, string>>{{false, "Campo PONTUAÇÃO vazio"}, {count1, ""}};
            }
            pos_pv.clear(); // LIMPA O VETOR QUE ARMAZENA AS POSIÇÕES DO ';' PARA SER USADO A CADA NOVA LINHA LIDA
        }
    }
    // FECHA OS ARQUIVOS
    arq_palavras.close();
    arq_scores.close();
    // SE NÃO OCORRER NENHUM DOS ERROS, RETORNA {TRUE, "VÁLIDO"}
    return pair<pair<bool, string>, pair<int, string>> {{true, "Válido"}, {0, ""}};
};
 

void Forca::carregar_arquivos(){
    fstream arquivo_palavras;
    fstream arquivo_scores;
    string line, palavra;
    int freq, pos;
    // ABRE OS ARQUIVOS PARA LEITURA DOS DADOS
    arquivo_palavras.open(m_arquivo_palavras, ios::in);
    arquivo_scores.open(m_arquivo_scores, ios::in);
    // LÊ O CONTEÚDO DO ARQUIVO DE PALAVRAS LINHA A LINHA ENQUANDO NÃO CHEGAR AO FINAL DO ARQUIVO
    while(!arquivo_palavras.eof()){
        getline(arquivo_palavras, line); // LER A LINHA INTEIRA
        for(int k=0; k < (int)line.size(); k++){
            // SE ENCONTRAR UM NÚMERO ELE GUARDA A POSIÇÃO ANTERIOR QUE É O ESPAÇO EM BRANCO PARA FAZER O "FATIAMENTO" DA string line
            if(isdigit(line[k])){
                pos = k-1;
                break;
            }
        }
        palavra = (line.substr(0, pos));   // ARMAZENA A PALAVRA NA VARIÁVEL palavra
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
        if(line1.size() == 1){               // SE O JOGADOR NÃO ACERTAR NENHUMA PALAVRA, SUBSTITUI O ESPAÇO EM BRANCO POR <nenhuma>
            line1 = " <nenhuma>";
            palavras.push_back(line1);
        } else{
            palavras.push_back(line1);
            line1.push_back(',');  
        }
        getline(arquivo_scores, line1, '\n'); // PARTINDO DA POSIÇÃO DO TERCEIRO getline() LER ATÉ ENCONTRAR O FINAL DA LINHA (\n)
        pont.push_back(stoi(line1));          // ARMAZENA A PONTUAÇÃO DO JOGADOR(A)
    }
    // FECHA OS ARQUIVOS
    arquivo_palavras.close();
    arquivo_scores.close();
};


void Forca::dados(){
    for(int i=0; i < (int)m_palavras.size(); i++){
        soma_freq += m_palavras[i].second; // FAZ A SOMA DAS FREQUÊNCIAS
    }
    media_p = soma_freq/(int)m_palavras.size(); // FAZ A MÉDIA DAS FREQUÊNCIAS DAS PALAVRAS 
    qnt_palavras = (int)m_palavras.size();      // ARMAZENA A QUANTIDADE DE PALAVRAS DA BASE DE PALAVRAS DO JOGO
};


void Forca::set_dificuldade(int d){
    if (d == 0){
        m_dificuldade = FACIL;      // ALTERA A DIFICULDADE DO JOGO PARA FÁCIL
    } else if(d == 1){
        m_dificuldade = MEDIO;      // ALTERA A DIFICULDADE DO JOGO PARA MÉDIO
    } else if(d == 2){
        m_dificuldade = DIFICIL;    // ALTERA A DIFICULDADE DO JOGO PARA DÍFICIL
    }
};
 

string Forca::proxima_palavra(){
    vector<string> freq_maior_igual;
    vector<string> freq_menor;
    vector<string> freq_maior;
    int sorteio, sorteio2;
    int count1=0;
    unsigned semente = time(NULL); // PARA AUMENTAR A ALEATORIEDADE DA FUNÇÃO rand(), ALTERANDO A SEMENTE A CADA COMPILAÇÃO
    srand(semente);
    for(int i=0; i < (int)m_palavras.size(); i++){      // PERCORRE O VETOR m_palavras QUE CONTÉM AS PALAVRAS E SUAS FREQUÊNCIAS
        if(m_palavras[i].second < media_p){             // SE A FREQUÊNCIA FOR MENOR QUE A MÉDIA
            freq_menor.push_back(m_palavras[i].first);  // ARMAZENA NO VETOR freq_menor
        }
        if(m_palavras[i].second >= media_p){                 // SE A FREQUÊNCIA FOR MAIOR OU IGUAL A MÉDIA
            freq_maior_igual.push_back(m_palavras[i].first); // ARMAZENA NO VETOR freq_maior_igual
        }
        if(m_palavras[i].second > media_p){             // SE A FREQUÊNCIA FOR MAIOR QUE A MÉDIA
            freq_maior.push_back(m_palavras[i].first);  // ARMAZENA NO VETOR freq_maior
        }
    }
    if(m_dificuldade == 0){ // DIFICULDADE FÁCIL
        while(count1 < 10){ // LOOP DO SORTEIO DAS 10 PALAVRAS DO JOGO
            sorteio = rand()%(freq_maior.size()-1); // SORTEIA UM NÚMERO no intervalo [0, freq_maior.size()[
            if(m_palavras_do_jogo.empty()){         // CASO O VETOR ESTEJA VAZIO
                m_palavras_do_jogo.push_back(freq_maior[sorteio]); // ARMAZENA A PALAVRA SORTEADA EM m_palavras_do_jogo
            } else{
                // CASO NÃO ENCONTRE A PALAVRA SORTEADA DENTRO DE m_palavras_do_jogo
                if(find(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end(), freq_maior[sorteio]) == m_palavras_do_jogo.end()){
                    m_palavras_do_jogo.push_back(freq_maior[sorteio]); // ARMAZENA A PALAVRA SORTEADA EM m_palavras_do_jogo
                    count1++;                                          // SOMA +1 AO CONTADOR PARA CONTABILIZAR A PALAVRA VÁLIDA, OU SEJA, NÃO REPETIDA
                }
            }
        }
    } else if (m_dificuldade == 1){     // DIFICULDADE MÉDIA
        while(count1 < 20){             // LOOP DO SORTEIO DAS 20 PALAVRAS DO JOGO
            if(count1 <= (int)(20/3)){  // SE O CONTADOR FOR MENOR OU IGUAL A 1/3 DAS PALAVRAS
                sorteio = rand()%(freq_menor.size()-1); // SORTEIA UM NÚMERO no intervalo [0, freq_menor.size()[
                if(m_palavras_do_jogo.empty()){         // CASO O VETOR ESTEJA VAZIO
                    m_palavras_do_jogo.push_back(freq_menor[sorteio]);  // ARMAZENA A PALAVRA SORTEADA EM m_palavras_do_jogo
                } else{
                    // CASO NÃO ENCONTRE A PALAVRA SORTEADA DENTRO DE m_palavras_do_jogo
                    if(find(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end(), freq_menor[sorteio]) == m_palavras_do_jogo.end()){
                        m_palavras_do_jogo.push_back(freq_menor[sorteio]); // ARMAZENA A PALAVRA SORTEADA EM m_palavras_do_jogo
                        count1++;                                          // SOMA +1 AO CONTADOR PARA CONTABILIZAR A PALAVRA VÁLIDA, OU SEJA, NÃO REPETIDA
                    }
                }
            } else{
                sorteio = rand()%(freq_maior_igual.size()-1); // SORTEIA UM NÚMERO no intervalo [0, freq_maior_igual.size()[
                if(m_palavras_do_jogo.empty()){               // CASO O VETOR ESTEJA VAZIO
                    m_palavras_do_jogo.push_back(freq_maior_igual[sorteio]); // ARMAZENA A PALAVRA SORTEADA EM m_palavras_do_jogo
                } else{
                    // CASO NÃO ENCONTRE A PALAVRA SORTEADA DENTRO DE m_palavras_do_jogo
                    if(find(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end(), freq_menor[sorteio]) == m_palavras_do_jogo.end()){
                        m_palavras_do_jogo.push_back(freq_maior_igual[sorteio]); // ARMAZENA A PALAVRA SORTEADA EM m_palavras_do_jogo
                        count1++;                                                // SOMA +1 AO CONTADOR PARA CONTABILIZAR A PALAVRA VÁLIDA, OU SEJA, NÃO REPETIDA
                    }
                }
            }
        }
    } else if(m_dificuldade == 2){  // DIFICULDADE DIFÍCIL
        while(count1 < 30){         // LOOP DO SORTEIO DAS 30 PALAVRAS DO JOGO
            if(count1 <= 22){       // SE O CONTADOR FOR MENOR OU IGUAL A 3/4 DAS PALAVRAS
                sorteio = rand()%(freq_menor.size()-1); // SORTEIA UM NÚMERO no intervalo [0, freq_menor.size()[
                if(m_palavras_do_jogo.empty()){         // SE O VETOR ESTIVER VAZIO
                    m_palavras_do_jogo.push_back(freq_menor[sorteio]); // ARMAZENA A PALAVRA SORTEADA EM m_palavras_do_jogo
                } else{
                    if(find(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end(), freq_menor[sorteio]) == m_palavras_do_jogo.end()){ // BUSCA
                        m_palavras_do_jogo.push_back(freq_menor[sorteio]);  // ARMAZENA A PALAVRA SORTEADA EM m_palavras_do_jogo
                            count1++;                                       // SOMA +1 AO CONTADOR PARA CONTABILIZAR A PALAVRA VÁLIDA, OU SEJA, NÃO REPETIDA
                    }
                }
            } else{
                sorteio = rand()%(freq_maior_igual.size()-1); // SORTEIA UM NÚMERO no intervalo [0, freq_maior_igual.size()[
                if(m_palavras_do_jogo.empty()){               // CASO O VETOR ESTEJA VAZIO
                    m_palavras_do_jogo.push_back(freq_maior_igual[sorteio]); // ARMAZENA A PALAVRA SORTEADA EM m_palavras_do_jogo
                } else{
                    if(find(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end(), freq_menor[sorteio]) == m_palavras_do_jogo.end()){ // BUSCA
                        m_palavras_do_jogo.push_back(freq_maior_igual[sorteio]);  // ARMAZENA A PALAVRA SORTEADA EM m_palavras_do_jogo
                        count1++;                                                 // SOMA +1 AO CONTADOR PARA CONTABILIZAR A PALAVRA VÁLIDA, OU SEJA, NÃO REPETIDA
                    }
                }
            }
        }
    }
    random_shuffle(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end());   // EMBARALHA A ORDEM DAS PALAVRAS
    sorteio2 = rand()%((int)m_palavras_do_jogo.size()-1);                   // SORTEIA UM NÚMERO no intervalo [0, m_palavras_do_jogo.size()[
    // GARANTE QUE A PALAVRA JOGADA NA RODADA SEGUINTE NÃO SEJA IGUAL A DA RODADA ANTERIOR
    for(int k=0; k < m_palavras_do_jogo.size(); k++){
        if(m_palavras_do_jogo[k] == m_palavra_atual){
            sorteio2 = rand()%((int)m_palavras_do_jogo.size()-1);
            while(m_palavra_atual == m_palavras_do_jogo[sorteio2]){
                sorteio2 = rand()%((int)m_palavras_do_jogo.size()-1);
            }
            break;
        }
    }
    m_palavra_atual = m_palavras_do_jogo[sorteio2];     // ARMAZENA A PALAVRA SORTEADA EM m_palavra_atual PARA SER USADA NA PARTIDA
    m_palavra_jogada = m_palavra_atual;                 // ARMANEZA m_palavra_atual EM m_palavra_jogada
    for(int i=0; i < (int)m_palavra_atual.size(); i++){ // PERCORRE m_palavra_jogada E ALTERA CADA CARACTERE POR UM UNDERLINE('_')
        m_palavra_jogada[i] = '_';
    }
    return m_palavra_jogada; // RETORNA A PALAVRA SORTEADA NO FORMATO “_ _ _ ... _ “
};
 

string Forca::get_palavra_jogada(char palp){
    for(int i=0; i < (int)m_palavra_atual.size(); i++){ // PERCORRE m_palavra_atual
        if (m_palavra_atual[i] == palp){                // SE ALGUM CARACTERE COINCIDIR COM O PALPITE DO(A) JOGADOR(A)
            m_palavra_jogada[i] = palp;                 // SUBSTUI O CARACTERE EM m_palavra_jogada PELO PALPITE
        }
    }
    return m_palavra_jogada; // RETORNA m_palavra_jogada ATUALIZADA
};


string Forca::get_palavra_atual(){
    return m_palavra_atual;     // RETORNA A PALAVRA QUE ESTÁ SENDO UTILIZADA ATUALMENTE NA PARTIDA
};
 

pair<bool, bool> Forca::palpite(char palp){
    int exist=0;
    if(m_letras_palpitadas.size() == 0){       // CASO SEJA O PRIMEIRO PALPITE DO JOGADOR(A)
        m_letras_palpitadas.push_back(palp);   // ARMAZENA O PALPITE
        if (m_palavra_atual.find(palp) < m_palavra_atual.size()){ // CASO O PALPITE ESTEJA CONTIDO EM m_palavra_atual
            return pair<bool, bool>{true, true};                  // RETORNA {T, T}
        } else if (m_palavra_atual.find(palp) > m_palavra_atual.size()){ // CASO O PALPITE NÃO ESTEJA CONTIDO EM m_palavra_atual
            m_tentativas_restantes--;                                    // SUBTRAI 1 DAS TENTATIVAS RESTANTES
            return pair<bool, bool>{false, true};                        // RETORNA {F, T}
        }
    } else{
        for(int k=0; k < (int)m_letras_palpitadas.size(); k++){ // PERCORRE m_letras_palpitadas
            if(m_letras_palpitadas[k] == palp){                 // CASO O PALPITE ESTEJA CONTIDO NO VETOR ALTERA A VARIÁVEL exist
                exist = 1;
            }
        }
        if (m_palavra_atual.find(palp) < m_palavra_atual.size() && (exist != 1)){ // CASO O PALPITE ESTEJA CONTIDO EM m_palavra_atual E A LETRA FOR NOVA
            m_letras_palpitadas.push_back(palp);                                  // ARMAZENA O PALPITE EM m_letras_palpitadas
            return pair<bool, bool>{true, true};                                  // RETORNA {T, T}
        } else if (m_palavra_atual.find(palp) > m_palavra_atual.size() && (exist != 1)){ // CASO O PALPITE NÃO ESTEJA CONTIDO EM m_palavra_atual E A LETRA FOR NOVA
            m_tentativas_restantes--;                                                    // SUBTRAI 1 DAS TENTATIVAS RESTANTES
            m_letras_palpitadas.push_back(palp);                                         // ARMAZENA O PALPITE EM m_letras_palpitadas
            return pair<bool, bool>{false, true};                                        // RETORNA {F, T}
        } else if(m_palavra_atual.find(palp) < m_palavra_atual.size() && (exist == 1)){  // SE O PALPITE ESTIVER CONTIDO EM m_palavra_atual E A LETRA FOR REPETIDA
            return pair<bool, bool>{true, false};                                        // RETORNA {T, F}
        } else if(m_palavra_atual.find(palp) > m_palavra_atual.size() && (exist == 1)){  // SE O PALPITE NÃO ESTIVER CONTIDO EM m_palavra_atual E A LETRA FOR REPETIDA
            return pair<bool, bool>{false, false};                                       // RETORNA {F, F}         
        }
    }
    exist = 0; // ZERA A VARIÁVEL exist PARA SER USADA A CADA NOVO PALPITE
};
 

bool Forca::rodada_terminada(){
    // CASO O JOGADOR ESGOTE AS TENTATIVAS (GAMEOVER) OU O JOGADOR ACERTE A PALAVRA (VITÓRIA) FINALIZA A RODADA
    if(get_tentativas_restantes() == 0 || m_palavra_jogada == m_palavra_atual){
        return true;
    }
    else{
        return false;
    }
};
 

void Forca::reset_rodada(){ 
    // RESTAURA AS TENTATIVAS RESTANTES E LIMPA O VETOR QUE CONTÉM AS LETRAS PALPITADAS PARA INICIAR UMA NOVA RODADA
    m_tentativas_restantes = 6;
    m_letras_palpitadas.clear();
};

void Forca::reinicia_jogo(bool reinicia){
    /* REINICIA O JOGO:
        - RESTAURA AS TENTATIVAS RESTANTES;
        - LIMPA O VETOR QUE CONTÉM AS LETRAS PALPITADAS
        - RESTAURA O RETORNO DA FUNÇÃO rodada_terminada PARA false
    */ 
    m_tentativas_restantes = 6;
    m_letras_palpitadas.clear();
    reinicia = false;
};
 

int Forca::get_tentativas_restantes(){
    return m_tentativas_restantes;  // RETORNA AS TENTATIVAS RESTANTES
};


void Forca::boneco(){
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

vector<string> Forca::fatiamento(string pa){
    // DIVIDE A STRING CONTENDO TODAS AS PALAVRAS ACERTADAS PELO(A) JOGADOR(A) E ARMAZENA AS PALAVRAS SEPARADAMENTE EM UM VETOR 
    stringstream sstream(pa);
    vector<string> str_sep;
    string word;
    char delimit = ',';
    while(getline(sstream, word, delimit)){
        str_sep.push_back(word);
    }
    return str_sep; // RETORNA O VETOR CONTENDO AS PALAVRAS ACERTADAS PELO(A) JOGADOR(A)
};


string Forca::dica_jogador(){
    vector<char> consoantes;
    vector<char> vogais;
    int dica;
    for(int i=0; i < (int)get_palavra_atual().size(); i++){ // PERCORRE m_palavra_atual
        // CASO O CARACTERE SEJA DIFERENTE (A, E, I, O E U) ARMAZENA ELE NO VETOR DAS CONSOANTES
        // CASO O CARACTE SEJA IGUAL A (A, E, I, O OU U) ARMAZENA ELE NO VETOR DAS VOGAIS
        if((get_palavra_atual()[i] != 'A') && (get_palavra_atual()[i] != 'E') && (get_palavra_atual()[i] != 'I') && (get_palavra_atual()[i] != 'O') && (get_palavra_atual()[i] != 'U')){
            consoantes.push_back(get_palavra_atual()[i]);
        } else if(get_palavra_atual()[i] == 'A' || get_palavra_atual()[i] == 'E' || get_palavra_atual()[i] == 'I' || get_palavra_atual()[i] == 'O' || get_palavra_atual()[i] == 'U'){
            vogais.push_back(get_palavra_atual()[i]);
        }
    }
    if (m_dificuldade == 0){   // CASO O NÍVEL SEJA FÁCIL, SORTEIA UMA CONSOANTE COMO DICA PARA O(A) JOGADOR(A)
        dica = rand()%(consoantes.size()-1);
        m_letras_palpitadas.push_back(consoantes[dica]);
        for(int i=0; i < (int)m_palavra_jogada.size(); i++){
            if(get_palavra_atual()[i] == consoantes[dica]){
                m_palavra_jogada[i] = consoantes[dica];
            }
        }
    } else if(m_dificuldade == 1){  // CASO O NÍVEL SEJA MEDIO, SORTEIA UMA VOGAL COMO DICA PARA O(A) JOGADOR(A)
        dica = rand()%(vogais.size()-1);
        m_letras_palpitadas.push_back(vogais[dica]);
        for(int i=0; i < (int)m_palavra_jogada.size(); i++){
            if(get_palavra_atual()[i] == vogais[dica]){
                m_palavra_jogada[i] = vogais[dica];
            }
        }
    }
    return m_palavra_jogada;    // RETORNA m_palavra_jogada ATUALIZADA COM A DICA
};

void Forca::score_tabela(){
    string d = "Dificuldade";
    string j = "Jogador";
    string pa = "Palavras";
    string pon = "Pontos";
    string maior_palavra = "Palavras";
    string maior_nome = "Jogador";
    vector<string> str_separadas;
    for(int j=0; j < dificuldade_jogador.size(); j++){      // PERCORRE dificuldade_jogador PARA ENCONTRAR O(A) JOGADOR(A) COM O MAIOR NOME
        if(dificuldade_jogador[j].second.size() > maior_nome.size()){
            maior_nome = dificuldade_jogador[j].second;     // ARMAZENA O MAIOR NOME EM maior_nome
        }
    }
    for(int i=0; i < (int)dificuldade_jogador.size(); i++){ // PERCORRE dificuldade_jogador PARA PERCORRER TODAS AS LINHAS DO ARQUIVO DE SCORES
        for(int a=0; a < palavras.size(); a++){             // PERCORRE palavras PARA ACESSAR AS PALAVRAS ACERTADAS POR CADA JOGADOR(A)
            str_separadas = fatiamento(palavras[a]);        // CRIA UM VETOR COM AS PALAVRAS ACERTADAS SEPARADAS
            for(int s=0; s < str_separadas.size(); s++){    // PERCORRE str_separadas PARA ENCONTRAR A MAIOR PALAVRA DENTRE AS PALAVRAS ACERTADAS POR CADA JOGADOR(A)
                if(str_separadas[s].size() > maior_palavra.size()){
                    maior_palavra = str_separadas[s];       // ARMAZENA A MAIOR PALAVRA EM maior_palavra
                }
            }
        }
        if(i==0){
            cout << d << " | " << j << setw((maior_nome.size() - j.size())+2) << " | " << pa << setw((maior_palavra.size() - pa.size())+2) << " | " << pon << endl;
        }
        // CHAMA NOVAMENTE A FUNÇÃO fatiamento() PARA IMPRIMIR AS PALAVRAS ACERTADAS POR CADA JOGADOR(A) SEPARADAMENTE 
        str_separadas = fatiamento(palavras[i]);
        /*PARA FAZER PADRONIZAÇÃO DA TABELA DE SCORES UTILIZAMOS A FUNÇÃO setw() PARA IMPRIMIR OS ESPAÇOS EM BRANCO:
            NO CASO DO CAMPO DIFICULDADE, COMO A STRING "Dificuldade" É MAIOR QUE AS DOS 3 NÍVEIS POSSÍVEIS, TEMOS O PADRÃO:
                - stew((tamanho_de_"Dificuldade" - dificuldade_do_jogador(a))+2)
            NO CASO DO CAMPO JOGADOR, TEMOS O PADRÃO:
                - stew((tamanho_do_maior_nome - nome_do_jogador(a))+2)
            NO CASO DO CAMPO PALAVRAS, TEMOS O PADRÃO:
                - stew((tamanho_da_maior_palavra - palavra_acertada_pelo_jogador(a))+2)
            NO CASO DO CAMPO PONTUAÇÃO, COMO A PONTUAÇÃO DE UM JOGADOR(A) DIFICILMENTE ULTRAPASSARÁ 6 DIGITOS, TEMOS O PADRÃO:
                - stew((tamanho_de_"Pontos" - pontuação_do_jogador(a))+2)
        */
        cout << dificuldade_jogador[i].first << setw((d.size() - dificuldade_jogador[i].first.size())+2) << "|" << dificuldade_jogador[i].second << setw((maior_nome.size() - dificuldade_jogador[i].second.size())+2) << "|";
        cout << str_separadas[0] << setw((maior_palavra.size() - str_separadas[0].size())+2) << "|" << " " << pont[i] << endl;
        for(int k=1; k < str_separadas.size(); k++){
            cout << setw(dificuldade_jogador[i].first.size() + (d.size() - dificuldade_jogador[i].first.size())+2) << "|" << setw(dificuldade_jogador[i].second.size() + (maior_nome.size() - dificuldade_jogador[i].second.size())+2) << "|"; 
            cout << str_separadas[k] << setw((maior_palavra.size() - str_separadas[k].size())+2) << "|" << setw((pon.size() - to_string(pont[i]).size())+2) << endl;
        }
        cout << setw(dificuldade_jogador[i].first.size() + (d.size() - dificuldade_jogador[i].first.size())+2) << setfill('-') << "+" << setw(dificuldade_jogador[i].second.size() + (maior_nome.size() - dificuldade_jogador[i].second.size())+2) << setfill('-') << "+";
        cout << setw(str_separadas[0].size() + (maior_palavra.size() - str_separadas[0].size())+2) << setfill('-') << "+" << setw(to_string(pont[i]).size() + (pon.size() - to_string(pont[i]).size())+2) << setfill('-') << "-" << endl;
        cout << setfill(' ');
    }    
};