#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

int main(){
    fstream m_arquivo_palavras;
    fstream m_arquivo_scores;
    string line, palavra;
    int freq;
    vector< pair<string, int> > m_palavras;
    int pos;
    m_arquivo_palavras.open("base_formatada.txt", ios::in);
    m_arquivo_scores.open("base_scores.txt", ios::in);
    while(!m_arquivo_palavras.eof()){
        getline(m_arquivo_palavras, line);
        for(int k=0; k < line.size(); k++){
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
    m_arquivo_palavras.close();
    m_arquivo_scores.close();

    int qnt_p=0, soma_f=0, media;  
    for(int i=0; i < (int)m_palavras.size(); i++){
        if((int)m_palavras[i].first.size() > 4){
            qnt_p++;
            soma_f += m_palavras[i].second;
        }
    }
    media = soma_f/qnt_p;
    //cout << dificuldade_jogador[1].first << dificuldade_jogador[1].second << palavras[1] << pont[1] << endl;
    //cout << pos1.size() << endl;
    //for(int i=0; i < m_palavras.size(); i++){
        //cout << "Palavra: " << m_palavras[i].first << " Frequencia: " << m_palavras[i].second << endl;
    //}
    srand(time(NULL));
    int count=0;
    vector<string> m_palavras_do_jogo;
    vector<string> nivel_facil;
    vector<string> nivel_medio;
    vector<string> nivel_dificil;
                for(int i=0; i < (int)m_palavras.size(); i++){
                    if(i <= 22){
                        if(m_palavras[i].second > media){
                            nivel_dificil.push_back(m_palavras[i].first);
                        }  
                    } else{
                        if(m_palavras[i].second <= media){
                            nivel_dificil.push_back(m_palavras[i].first);
                        }  
                    }
                }
                for(int k=0; k < 30; k++){
                    int sorteio = rand()%qnt_p;
                    m_palavras_do_jogo.push_back(nivel_dificil[sorteio]);
                }

    random_shuffle(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end());
    string m_palavra_atual;
    string m_palavra_jogada;
    m_palavra_atual = m_palavras_do_jogo[rand()%((int)(m_palavras_do_jogo.size())-1)];
    m_palavra_jogada = m_palavra_atual;
    for(int i=0; i < m_palavra_atual.size(); i++){
        m_palavra_jogada[i] = '_';  
    }
    cout << m_palavra_atual << endl;
    for(int i=0; i < m_palavra_jogada.size(); i++){
        cout << m_palavra_jogada[i] << " ";
    } 
}
           
