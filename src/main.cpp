#include <iostream>
#include "Forca.hpp"

using namespace std;
int main(int argc, char *argv[]){
    Forca forca(argv[1], argv[2]);
    forca.carregar_arquivos();
    auto valid = forca.eh_valido();
    if(!valid.first){ //sai do programa ao encontrar um erro
        cout<<"Erro "<<valid.second<<endl;
        exit(-1);
    }
    while(true){
        /*imprime o menu principal e a escolha do usuário*/
        
        if(/*iniciar jogo*/){
            /*Seleciona dificuldade*/
            Forca::Dificuldade d;
            forca.set_dificuldade(d);
            while(true){ //
                string p = forca.proxima_palavra();
                /*exibe interface do jogo*/
                while (!forca.rodada_terminada()){ //loop da rodada
                    /*ler palpite*/
                    string palpite;
                    auto result = forca.palpite(palpite);
                    /*testa palpite e atualiza a interface dependendo do resultado*/
                }
                if(/*acertou a palavra inteira*/){
                    /*imprime interface de continuar / parar*/
                    if (/*parar*/)
                        break;
                    else
                        forca.reset_rodada();
                }
                else{ /*perdeu*/
                    /*imprime gameover e a palavra que estava sendo jogada*/
                    break;
                }
            }
            /*ler informações do jogador para o score e gravar no arquivo*/
        }
        else if(/*mostrar score*/)
            /*mostrar score*/
        else //qualquer outro número sai do jogo
            break
    }
    return 0;
}