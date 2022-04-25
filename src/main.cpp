#include <iostream>
#include "Forca.hpp"
#include <istream>
#include <ctype.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
    Forca forca(argv[1], argv[2]); /*ARMAZENA O NOME DOS ARQUIVOS TXT COM A BASE DE PALAVRAS E OS SCORES*/
    cout << ">>> Lendo arquivo de palavras ["<< argv[1] << "] e de scores [" << argv[2] << "], por favor aguarde.." << endl;
    // FAZ A LEITURA DOS ARQUIVOS CONTENDO AS PALAVRAS E OS SCORES PARA, RESPECTIVAMENTE EXTRAIR AS PALAVRAS E FREQUÊNCIAS E EXTRAIR AS INFORMAÇÕES DAS PARTIDAS
    // FAZ A VALIDAÇÃO DOS ARQUIVOS PARA O ERRO DE INEXISTÊNCIA
    forca.carregar_arquivos();
    //FAZ A LEITURA DOS ARQUIVOS NOVAMENTE PARA VERIFICAR POSSIVEIS ERROS NOS ARQUIVOS
    // ARQUIVO DE PALAVRAS
    // 1 - ERRO DE CARACTERE ESPECIAL;
    // 2 - ESPAÇO EM BRANCO ENCONTRADO;
    // 3 - ERRO DE PALAVRAS COM O TAMANHO IGUAL OU MENOR QUE 4; 
    // 4 - ERRO DE FREQUÊNCIA NEGATIVA;
    // ARQUIVO DE SCORES
    // 1 - ERRO DE EXCESSO OU FALTA DE ";";
    // 2 - ERRO DE CAMPO VAZIO;
    auto valid = forca.eh_valido();
    forca.dados();
    if(valid.second.first == 0){
        if(!valid.first.first){ /*SAI DO PROGRAMA AO ENCONTRAR UM ERRO*/
            cout << "Erro: " << valid.first.second << endl; // IMPRIME O ERRO
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
            /*IMPRIME O ERRO, A LINHA EM QUE OCORREU O ERRO E A PALAVRA OU FREQUÊNCIA*/
            cout << "Erro: " << valid.first.second << ", na linha: " << valid.second.first << ", palavra/frequência: " << valid.second.second << endl;
            exit(-1);
        }
    }
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
        cin >> choice;
        vector<string> jogadores;
        string nome;
        if(choice == 1){
            /*SELECIONA A DIFICULDADE*/ 
            cout << "Vamos iniciar o jogo! Por favor escolha o nivel de dificuldade:" << endl;
            cout << "1 - FACIL" << endl;
            cout << "2 - MEDIO" << endl;
            cout << "3 - DIFICIL" << endl;
            int dificuldade, d;
            cout << "Sua escolha: ";
            cin >> dificuldade;
            if (dificuldade == 1){
                d = 0; 
            } else if(dificuldade == 2){
                d = 1;
            } else if(dificuldade == 3){
                d = 2;
            }
            forca.set_dificuldade(d);
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
                string p = forca.proxima_palavra();
                cout << endl;
                cout << endl;
                cout << endl;
                for(int i=0; i < (int)p.size(); i++){
                    cout << p[i] << " ";
                }
                cout << endl;
                cout << "Pontos: " << point << endl;
                cout << "Palpite: ";
                while (!forca.rodada_terminada()){ /*LOOP DA RODADA*/
                    /*LER PALPITE*/
                    char palpite;
                    cin >> palpite;
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
                                // CASO O JOGADOR TENHA ACERTADO A ÚLTIMA LETRA DA PALAVRA SOMA +2 PONTOS AO INVES DE +1 
                                if(p == forca.get_palavra_atual()){
                                    point += 2;
                                } else{
                                  point++;  
                                }
                            }
                        }
                        // FORMAÇÃO DO BONECO DE ACORDO COM AS TENTATIVAS RESTANTES
                        forca.boneco();
                        // IMPRIME A PALAVRA ATUALIZADA
                        for(int i=0; i < (int)p.size(); i++){
                            cout << p[i] << " ";
                        }
                        cout << endl;
                        if(forca.get_tentativas_restantes() == 0 || p == forca.get_palavra_atual()){
                            //PARA QUANDO A PARTIDA FINALIZAR (GAMEOVER OU VITÓRIA)
                            cout << "Pontos: " << point << endl;
                        }else{
                            //AO LONGO DA PARTIDA
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
                        point--;
                        // FORMAÇÃO DO BONECO DE ACORDO COM AS TENTATIVAS RESTANTES
                        forca.boneco();
                        // IMPRIME A PALAVRA ATUALIZADA
                        for(int i=0; i < (int)p.size(); i++){
                            cout << p[i] << " ";
                        }
                        cout << endl;
                        if(forca.get_tentativas_restantes() == 0 || p == forca.get_palavra_atual()){
                            //PARA QUANDO A PARTIDA FINALIZAR (GAMEOVER OU VITÓRIA)
                            cout << "Pontos: " << point << endl;
                        }else{
                            //AO LONGO DA PARTIDA
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
                        // IMPRIME A PALAVRA ATUALIZADA
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
                if(p.find('_') > p.size()){
                    /*IMPRIME A INTERFACE DE CONTINUAR OU PARAR*/
                    int choice2; 
                    cout << "Aclamação, sucesso e talento? OK" << endl;
                    cout << "1 - Nova Partida" << endl;
                    cout << "2 - Menu Inicial" << endl;
                    cout << "Sua escolha: ";
                    cin >> choice2;
                    if (choice2 == 2){
                        break;
                    } else{
                        /*INICIA OUTRA RODADA COM O MESMO NÍVEL DE DIFICULDADE*/
                        forca.reset_rodada();
                    }
                } else{ /*PERDEU*/
                    /*IMPRIME O GAMEOVER E A PALAVRA QUE ESTAVA SENDO JOGADA*/ 
                    cout << "\"Os pequenos fracassos cotidianos preparam você para derrotas extraordinárias!\"" << endl;
                    cout << "O jogo acabou, a palavra era "<< forca.get_palavra_atual() << "."<< endl;
                    break;
                }
            }
            /*LER INFORMAÇÕES DO JOGADOR PARA O SCORE E GRAVAR NO ARQUIVO*/ 
            /*PEDE O NOME DO JOGADOR PARA ARMAZENAR OS DADOS DA PARTIDA NO ARQUIVO DE SCORES*/
            cout << "Apelido: ";
            cin >> nome;
            jogadores.push_back(nome);
            cout << endl;
        }
        else if( choice == 2){
            /*MOSTRAR SCORE*/
        } else{
            break;
            //QUALQUER OUTRO NÚMERO SAI DO JOGO 
        }   
    }
    return 0;
}