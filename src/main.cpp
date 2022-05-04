#include <iostream>
#include "Forca.hpp"
#include <istream>
#include <cctype>
#include <vector>
#include <fstream>
#include <random>

using namespace std;

int main(int argc, char *argv[]){
    Forca forca(argv[1], argv[2]); /*ARMAZENA O NOME DOS ARQUIVOS TXT COM A BASE DE PALAVRAS E OS SCORES*/
    cout << ">>> Lendo arquivo de palavras ["<< argv[1] << "] e de scores [" << argv[2] << "], por favor aguarde.." << endl;
    // FAZ A LEITURA DOS ARQUIVOS PARA VERIFICAR POSSIVEIS ERROS NOS ARQUIVOS
    // ARQUIVO DE PALAVRAS
    // 1 - ERRO DE INEXISTÊNCIA;
    // 2 - ERRO DE CARACTERE ESPECIAL;
    // 3 - ESPAÇO EM BRANCO ENCONTRADO;
    // 4 - ERRO DE PALAVRAS COM O TAMANHO IGUAL OU MENOR QUE 4; 
    // 5 - ERRO DE FREQUÊNCIA NEGATIVA;
    // ARQUIVO DE SCORES
    // 1 - ERRO DE INEXISTÊNCIA;
    // 2 - ERRO DE EXCESSO DE ";";
    // 3 - ERRO DE FALTA DE ";";
    // 4 - ERRO DE CAMPO VAZIO (DIFICULDADE);
    // 5 - ERRO DE CAMPO VAZIO (NOME);
    // 6 - ERRO DE CAMPO VAZIO (PONTUAÇÃO);
    auto valid = forca.eh_valido();
    if(valid.second.first == 0){
        if(!valid.first.first){ /*SAI DO PROGRAMA AO ENCONTRAR UM ERRO*/
            cout << "Erro: " << valid.first.second << " Arquivo: "<< valid.second.second <<endl; // IMPRIME O ERRO E O ARQUIVO QUE GEROU O ERRO
            exit(-1);
        } 
    } else if(valid.second.second == "" && (valid.second.first != 0)){
        if(!valid.first.first){ /*SAI DO PROGRAMA AO ENCONTRAR UM ERRO*/
            /*IMPRIME O ERRO E A LINHA EM QUE OCORREU O ERRO*/
            cout << "Erro: " << valid.first.second << " na linha: " << valid.second.first << endl;
            exit(-1);
        } 
    } else{
        if(!valid.first.first){ /*SAI DO PROGRAMA AO ENCONTRAR UM ERRO*/
            /*IMPRIME O ERRO, A LINHA EM QUE OCORREU O ERRO E A PALAVRA OU FREQUÊNCIA QUE GEROU O ERRO*/
            cout << "Erro: " << valid.first.second << ", na linha: " << valid.second.first << ", palavra/frequência: " << valid.second.second << endl;
            exit(-1);
        }
    }
    // FAZ A LEITURA DOS ARQUIVOS CONTENDO AS PALAVRAS E OS SCORES PARA, RESPECTIVAMENTE EXTRAIR AS PALAVRAS E FREQUÊNCIAS E EXTRAIR AS INFORMAÇÕES DAS PARTIDAS
    forca.carregar_arquivos();
    // ABRE O ARQUIVO QUE CONTÉM OS SCORES PARA ATUALIZÁ-LO COM AS INFORMAÇÕES DA PARTIDA DO(A) JOGADOR(A)
    fstream atualiza_score;
    atualiza_score.open(argv[2], ios::app);
    forca.dados();  // CALCULA A FRÊQUENCIA MÉDIA DAS PALAVRAS
    cout << "-----------------------------------------------------------" << endl;
    cout << ">>> Arquivos OK" << endl;
    cout << "-----------------------------------------------------------" << endl; 
    while(true){
        /*IMPRIME O MENU PRINCIPAL E A ESCOLHA DO USUÁRIO*/ 
        cout << "Bem-vindo(a) ao Jogo Forca! Por favor escolha uma das opções:" << endl;
        cout << "1 - Iniciar o jogo" << endl;
        cout << "2 - Ver Scores Anteriores" << endl;
        cout << "3 - Sair do Jogo" << endl;
        int choice;
        cout << "Sua escolha: ";
        cin >> choice; // LÊ A ESCOLHA DO(A) JOGADOR(A)
        string nome;
        vector<string> palavras_jogador;
        string dificuldade_score;
        if(choice == 1){
            /*SELECIONA A DIFICULDADE*/ 
            cout << "Vamos iniciar o jogo! Por favor escolha o nivel de dificuldade:" << endl;
            cout << "1 - FACIL" << endl;
            cout << "2 - MEDIO" << endl;
            cout << "3 - DIFICIL" << endl;
            int dificuldade, d;
            cout << "Sua escolha: ";
            cin >> dificuldade; // LÊ A DIFICULDADE ESCOLHIDA PELO(A) JOGADOR(A)
            if (dificuldade == 1){
                d = 0; 
            } else if(dificuldade == 2){
                d = 1;
            } else if(dificuldade == 3){
                d = 2;
            }
            forca.set_dificuldade(d); // ALTERA A DIFICULDADE DENTRO DA CLASSE FORCA
            int point=0;
            while(true){
                /*EXIBE A INTERFACE INICIAL DO JOGO (ANTES DE LER O PRIMEIRO PALPITE)*/
                if (dificuldade == 1){
                    cout << "Iniciando o jogo no nível FÁCIL, será que você conhece essa palavra?" << endl;
                } else if(dificuldade == 2){
                    cout << "Iniciando o jogo no nível MÉDIO, será que você conhece essa palavra?" << endl;
                } else if(dificuldade == 3){
                    cout << "Iniciando o jogo no nível DIFÍCIL, será que você conhece essa palavra?" << endl;
                }
                string p = forca.proxima_palavra(); // PALAVRA JOGADA ATUALMENTE NA FORMA "_ _ _ _ ... _"
                cout << endl;
                cout << endl;
                cout << endl;
                p = forca.dica_jogador(); // ATUALIZA p COM A DICA DO JOGADOR CASO O NÍVEL SEJA FÁCIL OU MÉDIO
                for(int i=0; i < (int)p.size(); i++){
                    cout << p[i] << " ";
                }
                cout << endl;
                cout << "Pontos: " << point << endl;
                cout << "Palpite: ";
                while (!forca.rodada_terminada()){ /*LOOP DA RODADA*/
                    /*LER PALPITE*/
                    char palpite;
                    cin >> palpite; // LÊ O PALPITE DO(A) JOGADOR(A)
                    palpite = toupper(palpite); // ALTERA O PALPITE PARA MAIÚSCULO 
                    auto result = forca.palpite(palpite);
                    if(result.first == true && (result.second == true)){
                        // ATUALIZA A VARIAVEL "p"
                        p = forca.get_palavra_jogada(palpite);
                        if(forca.get_tentativas_restantes() == 0){
                            /*SE AS TENTATIVAS CHEGAREM A ZERO, AO INVES DE IMPRIMIR A MENSAGEM PROGRAMADA DO PALPITE, IMPRIME A MENSAGEM DE GAMEOVER*/
                            cout << "FIM DE JOGO, VOCÊ PERDEU! :(" << endl;
                        }else if(p == forca.get_palavra_atual()){
                            /*PARA GANHAR O JOGO, TEM QUE ACERTAR A ÚLTIMA LETRA, ENTÃO SOMENTE NO CASO {TRUE, TRUE} HÁ ESSA CONDIÇÃO
                            QUE COMPARA SE A VARIAVEL "p", QUE É A PALAVRA JOGADA NA RODADA EM FORMA DE TRAÇOS (_), É IGUAL À PALAVRA JOGADA, OU SEJA,
                            SE TODOS OS TRAÇOS FORAM SUBSTITUIDOS E IMPRIME A MENSAGEM DE VITÓRIA*/ 
                            cout << "PARABÉNS, VOCÊ GANHOU!!!! :)" << endl;
                        } else{
                            //IMPRIME O PALPITE
                            cout << "Correto, a palavra contem a letra " << palpite << " :)" << endl;
                        }
                        // COMPUTA OS PONTOS DE ACORDO COM A OCORRÊNCIA DA LETRA NA PALAVRA
                        for(int i=0; i < (int)forca.get_palavra_atual().size(); i++){
                            if (forca.get_palavra_atual()[i] == palpite){
                                // CASO O JOGADOR TENHA ACERTADO A ÚLTIMA LETRA QUE FALTAVA DA PALAVRA SOMA +2 PONTOS 
                                if(p == forca.get_palavra_atual()){
                                    point += 2;
                                }
                                point++; // SOMA +1 PONTO PARA CADA OCORRÊNCIA NA PALAVRA DA LETRA ACERTADA PELO JOGADOR
                            }
                        }
                        // FORMA O BONECO DE ACORDO COM AS TENTATIVAS RESTANTES
                        forca.boneco();
                        // IMPRIME A PALAVRA NA FORMA "_ _ _ _ ... _" ATUALIZADA
                        for(int i=0; i < (int)p.size(); i++){
                            cout << p[i] << " ";
                        }
                        cout << endl;
                        if(forca.get_tentativas_restantes() == 0 || p == forca.get_palavra_atual()){
                            //  PARA QUANDO A PARTIDA FINALIZAR (GAMEOVER OU VITÓRIA) IMPRIME SOMENTE A PONTUAÇÃO
                            cout << "Pontos: " << point << endl;
                        }else{
                            //  AO LONGO DA PARTIDA IMPRIME A PONTUAÇÃO E O PALPITE
                            cout << "Pontos: " << point << endl;
                            cout << "Palpite: ";
                        }
                    } else if(result.first == false && (result.second == true)){
                        if(forca.get_tentativas_restantes() == 0){
                            /*SE AS TENTATIVAS CHEGAREM A ZERO, AO INVES DE IMPRIMIR A MENSAGEM PROGRAMADA DO PALPITE, IMPRIME A MENSAGEM DE GAMEOVER*/
                            cout << "FIM DE JOGO, VOCÊ PERDEU! :(" << endl;
                        }else{
                            //IMPRIME O PALPITE
                            cout << "Não há a letra " << palpite << " na palavra :(" << endl;  
                        }
                        point--; // SUBTRAI A PONTUAÇÃO DO(A) JOGADOR(A)
                        // FORMAÇÃO DO BONECO DE ACORDO COM AS TENTATIVAS RESTANTES
                        forca.boneco();
                        // IMPRIME A VARIÁVEL "p" ATUALIZADA NA FORMA "_ _ _ _ ... _" 
                        for(int i=0; i < (int)p.size(); i++){
                            cout << p[i] << " ";
                        }
                        cout << endl;
                        if(forca.get_tentativas_restantes() == 0 || p == forca.get_palavra_atual()){
                            //PARA QUANDO A PARTIDA FINALIZAR (GAMEOVER OU VITÓRIA) IMPRIME SOMENTE A PONTUAÇÃO
                            cout << "Pontos: " << point << endl;
                        }else{
                            //AO LONGO DA PARTIDA IMPRIME A PONTUAÇÃO E O PALPITE
                            cout << "Pontos: " << point << endl;
                            cout << "Palpite: ";
                        }
                    } else if((result.first == true && (result.second == false)) || (result.first == false && (result.second == false))){
                        if(forca.get_tentativas_restantes() == 0){
                            /*SE AS TENTATIVAS CHEGAREM A ZERO, AO INVES DE IMPRIMIR A MENSAGEM PROGRAMADA DO PALPITE, IMPRIME A MENSAGEM DE GAMEOVER*/
                            cout << "FIM DE JOGO, VOCÊ PERDEU! :(" << endl;
                        }else{
                            //IMPRIME O PALPITE
                            cout << "Você já tentou a letra " << palpite << " !!!" << endl;
                        }
                        // FORMAÇÃO DO BONECO DE ACORDO COM AS TENTATIVAS RESTANTES
                        forca.boneco();
                        // IMPRIME A VARIÁVEL "p" NA FORMA "_ _ _ _ ... _"
                        for(int i=0; i < (int)p.size(); i++){
                            cout << p[i] << " ";
                        }
                        cout << endl;
                        if(forca.get_tentativas_restantes() == 0 || p == forca.get_palavra_atual()){
                            // QUANDO A PARTIDA FINALIZAR (GAMEOVER OU VITÓRIA) IMPRIME SOMENTE A PONTUAÇÃO
                            cout << "Pontos: " << point << endl;
                        }else{
                            // AO LONGO DA PARTIDA IMPRIME A PONTUAÇÃO E O PALPITE
                            cout << "Pontos: " << point << endl;
                            cout << "Palpite: ";
                        }
                    }
                }
                if(find(p.begin(), p.end(), '_') == p.end()){
                    /*IMPRIME A INTERFACE DE CONTINUAR OU PARAR*/
                    int choice2;
                    palavras_jogador.push_back(forca.get_palavra_atual()); // ARMAZENAR A PALAVRA QUE O(A) JOGADOR(A) ACERTOU
                    // ARMANEZA A DIFICULDADE DA PARTIDA
                    if(dificuldade == 1){
                        dificuldade_score = "FACIL";
                    } else if(dificuldade == 2){
                        dificuldade_score = "MEDIO";
                    } else if(dificuldade == 3){
                        dificuldade_score = "DIFICIL";
                    }
                    cout << "Aclamação, sucesso e talento? OK" << endl;
                    cout << "1 - Nova Partida" << endl;
                    cout << "2 - Menu Inicial" << endl;
                    cout << "Sua escolha: ";
                    cin >> choice2; // LÊ A ESCOLHA DO JOGADOR
                    if (choice2 == 2){ // VAI PARA A INTERFACE INICIAL DO JOGO
                        break;
                    } else{ // INICIA OUTRA RODADA COM O MESMO NÍVEL DE DIFICULDADE
                        forca.reset_rodada();
                    }
                } else{ /*PERDEU*/
                    /*IMPRIME O GAMEOVER E A PALAVRA QUE ESTAVA SENDO JOGADA*/
                    // ARMANEZA A DIFICULDADE DA PARTIDA
                    if(dificuldade == 1){
                        dificuldade_score = "FACIL";
                    } else if(dificuldade == 2){
                        dificuldade_score = "MEDIO";
                    } else if(dificuldade == 3){
                        dificuldade_score = "DIFICIL";
                    }
                    cout << "\"Os pequenos fracassos cotidianos preparam você para derrotas extraordinárias!\"" << endl;
                    cout << "O jogo acabou, a palavra era "<< forca.get_palavra_atual() << "."<< endl;
                    break;
                }
            }
            /*GRAVAÇÃO DAS INFORMAÇÕES DO(A) JOGADOR(A) NO ARQUIVO DE SCORES*/ 
            cout << "Apelido: ";
            cin >> nome; // LÊ O NOME DO(A) JOGADOR(A)
            cout << endl;
            atualiza_score << "\n" << dificuldade_score << "; " << nome << "; "; // ARMAZENA A DIFICULDADE E O NOME SEPARADOS POR PONTO E VÍRGULA
            for(int i=0; i < (int)palavras_jogador.size(); i++){ // ARMAZENAR AS PALAVRAS ACERTADAS PELO(A) JOGADOR(A) SEPARADAS POR VÍRGULA
                if(palavras_jogador.size() <= 1){
                    atualiza_score << palavras_jogador[i];
                } else{
                    if(i == (int)palavras_jogador.size()-1){
                        atualiza_score << palavras_jogador[i];
                    } else{
                      atualiza_score << palavras_jogador[i] << ", ";  
                    }
                } 
            }
            palavras_jogador.clear(); // LIMPA O VETOR COM AS PALAVRAS ACERTADAS PELO(A) JOGADOR(A)
            atualiza_score << ";" << point;
            forca.reinicia_jogo(forca.rodada_terminada()); // REINICIA O JOGO
        }
        else if( choice == 2){  /*MOSTRAR SCORE*/
            forca.score_tabela();
            cout << endl;
        } else{ /*SAI DO JOGO*/
            break; 
        }   
    }
    atualiza_score.close(); // FECHA O ARQUIVO DE SCORES JÁ QUE O JOGO FINALIZOU E ELE NÃO PRECISARÁ MAIS SER ATUALIZADO
    return 0;
}