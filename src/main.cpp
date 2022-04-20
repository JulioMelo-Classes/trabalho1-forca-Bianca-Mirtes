#include <iostream>
#include "Forca.hpp"
#include <istream>
#include <ctype.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
    Forca forca(argv[1], argv[2]);
    cout << ">>> Lendo arquivo de palavras ["<< argv[1] << "] e de scores [" << argv[2] << "], por favor aguarde.." << endl;
    forca.carregar_arquivos();
    auto valid = forca.eh_valido();
    forca.dados();
    if(valid.second.first == 0){
        if(!valid.first.first){ //sai do programa ao encontrar um erro
            cout << "Erro " << valid.first.second << endl;
            exit(-1);
        } 
    } else if(valid.second.second == "" && (valid.second.first != 0)){
        if(!valid.first.first){ //sai do programa ao encontrar um erro
            cout << "Erro " << valid.first.second << " na linha: " << valid.second.first << endl;
            exit(-1);
        } 
    } else{
        if(!valid.first.first){ //sai do programa ao encontrar um erro
            cout << "Erro " << valid.first.second << ", na linha: " << valid.second.first << ", palavra: " << valid.second.second << endl;
            exit(-1);
        }
    }
    cout << "-----------------------------------------------------------" << endl;
    cout << ">>> Arquivos OK" << endl;
    cout << "-----------------------------------------------------------" << endl; 
    while(true){
        /*imprime o menu principal e a escolha do usuário*/
        cout << "Bem-vindo(a) ao Jogo Forca! Por favor escolha uma das opções:" << endl;
        cout << "1 - Iniciar o jogo" << endl;
        cout << "2 - Ver Scores Anteriores" << endl;
        cout << "3 - Sair do Jogo" << endl;
        int choice;
        cout << "Sua escolha: ";
        cin >> choice;
        if(choice == 1){
            /*Seleciona dificuldade*/
            cout << "Vamos iniciar o jogo! Por favor escolha o nivel de dificuldade:" << endl;
            cout << "1 - FACIL" << endl;
            cout << "2 - MEDIO" << endl;
            cout << "3 - DIFICIL" << endl;
            //Forca::Dificuldade d;
            int dificuldade, d;
            cout << "Sua escolha: ";
            cin >> dificuldade;
            if (dificuldade == 1){
                d = 0; 
                //Forca::Dificuldade::FACIL
                cout << "Iniciando o jogo no nível FÁCIL, será que você conhece essa palavra?" << endl;
            } else if(dificuldade == 2){
                d = 1;
                //Forca::Dificuldade::MEDIO;
                cout << "Iniciando o jogo no nível MÉDIO, será que você conhece essa palavra?" << endl;
            } else if(dificuldade == 3){
                d = 2;
                //Forca::Dificuldade::DIFICIL;
                cout << "Iniciando o jogo no nível DIFÍCIL, será que você conhece essa palavra?" << endl;
            }
            //cout << 3 << endl;
            forca.set_dificuldade(d);
            //cout << 5 << endl;
            int point=0;
            vector<char> boneco{'o', '/', '|', '\\', '/', '\\'};
            while(true){
                string p = forca.proxima_palavra();
                /*exibe interface do jogo*/
                cout << endl;
                cout << endl;
                cout << endl;
                for(int i=0; i < (int)p.size(); i++){
                    cout << p[i] << " ";
                }
                cout << endl;
                cout << "Pontos: " << point << endl;
                cout << "Palpite: ";
                while (!forca.rodada_terminada()){ //loop da rodada
                    /*ler palpite*/
                    char palpite;
                    cin >> palpite;
                    auto result = forca.palpite(palpite);
                    cout << forca.get_palavra_atual() << endl;
                    if(result.first == true && (result.second == true)){
                        cout << "Correto, a palavra contem a letra " << palpite << " :)" << endl;
                        //p = forca.get_palavra_jogada(palpite);
                        for(int i=0; i < (int)forca.get_palavra_atual().size(); i++){
                            if (forca.get_palavra_atual()[i] == palpite){
                                p[i] = palpite;
                            }
                        }
                        for(int i=0; i < (int)p.size(); i++){
                            cout << p[i] << " ";
                        }
                    cout << endl;
                    cout << "Pontos: " << point << endl;
                    cout << "Palpite: ";
                    } else if(result.first == false && (result.second == true)){
                        cout << "Não há a letra " << palpite << " na palavra :(" << endl;
                        for(int i=0; i < (int)p.size(); i++){
                            cout << p[i] << " ";
                        }
                        cout << endl;
                        cout << "Pontos: " << point << endl;
                        cout << "Palpite: ";
                    } else if(result.first == true && (result.second == false)){
                        cout << "Você já tentou a letra " << palpite << " !!!" << endl;
                        for(int i=0; i < (int)p.size(); i++){
                            cout << p[i] << " ";
                        }
                        cout << endl;
                        cout << "Pontos: " << point << endl;
                        cout << "Palpite: ";
                    } else if(result.first == false && (result.second == false)){
                        cout << "Você já tentou a letra " << palpite << " e ela não está na palavra :(" << endl;
                        for(int i=0; i < (int)p.size(); i++){
                            cout << p[i] << " ";
                        }
                        cout << endl;
                        cout << "Pontos: " << point << endl;
                        cout << "Palpite: ";
                    }
                }
                break;
                //if(p.find('_') == p.size()){
                    /*imprime interface de continuar / parar*/
                    //if (/*parar*/){
                        //break;
                    //} else{
                        //forca.reset_rodada();
                    //}
                //}
                //else{ /*perdeu*/
                    /*imprime gameover e a palavra que estava sendo jogada*/
                    //cout << "O jogo acabou, a palavra era "<< forca.get_palavra_atual() << endl; 
                    //break;
                //}
            }
            /*ler informações do jogador para o score e gravar no arquivo*/
        }
        else if( choice == 2){
            /*mostrar score*/
        } else{
            //break;
             //qualquer outro número sai do jogo
        }   
    }
    return 0;
}