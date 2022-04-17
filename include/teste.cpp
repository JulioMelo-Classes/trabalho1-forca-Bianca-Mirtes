#include <iostream>
#include <fstream>
#include <string>
#include <cstring> 
#include <sstream>
#include <vector>

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
    std::vector<int> pos1;
    while(!m_arquivo_scores.eof()){
        getline(m_arquivo_scores, line1);
        for (int i=0; i < line1.size(); i++)
        {
            if(ispunct(line1[i])){
                pos1.push_back(i-1);
            }
        }
        break;
        //dificuldade_jogador[count].first = line.substr(0, pos1[0]);
    }
    std::cout << pos1[0] << pos1[1] << pos1[2] << std::endl;
    std::vector<std::pair<std::vector<std::string>, int>> palavra_pont;
    std::string linha;
    //for(int i=0; i < m_palavras.size(); i++){
        //std::cout << "Palavra: " << m_palavras[i].first << " Frequencia: " << m_palavras[i].second << std::endl;
    //}
    m_arquivo_palavras.close();
    m_arquivo_scores.close();
}
           
