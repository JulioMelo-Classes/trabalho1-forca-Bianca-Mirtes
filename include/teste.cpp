#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

int main(){
    std::fstream m_arquivo_palavras;
    std::fstream m_arquivo_scores;
    std::string line, palavra;
    int freq;
    std::vector< std::pair<std::string, int> > m_palavras;
    int pos;
    m_arquivo_palavras.open("base_formatada.txt", std::ios::in);
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
    std::vector<std::pair<std::string, std::string>> dificuldade_jogador;
    std::vector<std::string> palavras;
    std::vector<int> pont;
    std::string line1;
    int count=0;
    while(!m_arquivo_scores.eof()){
        getline(m_arquivo_scores, line1, ';');
        //std::cout << line1 << std::endl;
        std::string line2 = line1;
        getline(m_arquivo_scores, line1, ';');
        std::string line3 = line1;
        dificuldade_jogador.push_back(make_pair(line2, line3));
        getline(m_arquivo_scores, line1, ';');
        palavras.push_back(line1);
        getline(m_arquivo_scores, line1, '\n');
        pont.push_back(std::stoi(line1));
    }
    //std::cout << dificuldade_jogador[1].first << dificuldade_jogador[1].second << palavras[1] << pont[1] << std::endl;
    //std::cout << pos1.size() << std::endl;
    //for(int i=0; i < m_palavras.size(); i++){
        //std::cout << "Palavra: " << m_palavras[i].first << " Frequencia: " << m_palavras[i].second << std::endl;
    //}
    std::vector< std::string > m_palavras_do_jogo;
    //srand(time(NULL));
                    for(int i=0; i < 10; i++){
                    int sorteio = rand()%3480410;
                    if(m_palavras[sorteio].second > 130){
                        m_palavras_do_jogo.push_back(m_palavras[sorteio].first);
                    } else{
                        sorteio = rand()%3480410;
                        m_palavras_do_jogo.push_back(m_palavras[sorteio].first);
                    }
                }
    //for(int k=0; k < 10; k++){
        //std::cout << m_palavras_do_jogo[k] << std::endl;
    //}
    std::random_shuffle(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end());
    for(int k=0; k < 10; k++){
        std::cout << m_palavras_do_jogo[k] << std::endl;
    }
    std::string m_palavra_atual;
    std::string m_palavra_jogada;
    std::random_shuffle(m_palavras_do_jogo.begin(), m_palavras_do_jogo.end());
    m_palavra_atual = m_palavras_do_jogo[rand()%(m_palavras_do_jogo.size()-1)];
    m_palavra_jogada = m_palavra_atual;
    for(int i=0; i < m_palavra_atual.size(); i++){
        m_palavra_jogada[i] = '_';  
    }
    for(int i=0; i < m_palavra_jogada.size(); i++){
        std::cout << m_palavra_jogada[i] << " ";
    } 
    m_arquivo_palavras.close();
    m_arquivo_scores.close();
}
           
