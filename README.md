# Trabalho-1-Jogo-da-Forca-LP1-2022.1
* Repositório contendo as especificações do Trabalho 1 da disciplina de LP1 do semestre 2022.1
# Processo de Compilação e Execução do Programa
* Pré-Requisitos:
    - CMAKE; <br />

Para fazer a compilação e execução do programa, digite no terminal: <br />
```
    mkdir build
    cd build/
    cmake ..
    cmake --build .
    ./program ../data/base_formatada.txt ../data/base_scores.txt
```
# Validação Dos Arquivos

1. Arquivo de Palavras e de Scores:
    - (a) ERRO DE INEXISTÊNCIA;
        - (I) Caso somente o arquivo "base_formatada.txt" não exista.
            - ![erro1](https://user-images.githubusercontent.com/99360129/165418646-3983a2d4-cd5c-4c3b-bc88-13aa3750277b.png)
        - (II) Caso somente o arquivo "base_scores.txt" não exista.
            - ![erro2](https://user-images.githubusercontent.com/99360129/165418565-61f29b6b-aace-45ca-9f4f-4ffd04be28c7.png)
        - (III) Caso os arquivos "base_formatada.txt" e "base_scores.txt" não existam.
            - ![erro3](https://user-images.githubusercontent.com/99360129/165418661-a1d98534-de4a-40ef-a12b-b3f2d152f026.png)
       
2. Arquivo de Palavras:
    - (a) ERRO DE CARACTERE ESPECIAL;
        - ![erro4](https://user-images.githubusercontent.com/82531511/165169521-40e9aa40-c39d-4d5f-983d-4dcfed3ee9ad.jpeg)

    - (b) ERRO DE ESPAÇO EM BRANCO;
        - ![erro3](https://user-images.githubusercontent.com/82531511/165169500-3a6e1d85-8c78-4fea-92a2-2001242befaf.jpeg)

    - (c) ERRO DE PALAVRA COM TAMANHO MENOR OU IGUAL A 4;
        - ![erro8](https://user-images.githubusercontent.com/82531511/165169603-b6086557-c573-4507-bdff-b82436223fec.jpeg)

    - (d) ERRO DE FREQUÊNCIA NEGATIVA;
        - ![erro6](https://user-images.githubusercontent.com/82531511/165169564-f3a13eed-8bc0-4883-85d2-e176df4e1b0c.jpeg)

3. Arquivo de Scores:  
    - (a) ERRO DE EXCESSO DE PONTO E VÍRGULA;
        - ![erro1](https://user-images.githubusercontent.com/99360129/165215289-7c4a7760-2541-4858-bf1d-fe2a0c626991.png)
        - ![erro2](https://user-images.githubusercontent.com/99360129/165215384-ee4f1437-eacd-4535-a6d7-3e656bbf20ef.png)

    - (b) ERRO DE FALTA DE PONTO E VÍRGULA;
        - ![erro1](https://user-images.githubusercontent.com/99360129/165215523-3656898f-9f70-41f6-8a56-3bc1202f5f0b.png)
        - ![erro2](https://user-images.githubusercontent.com/99360129/165215463-677bd4ff-fbbd-49d3-bb7d-7e8e1d727490.png)

    - (c) ERRO DE CAMPO VAZIO (DIFICULDADE);
        - ![erro1](https://user-images.githubusercontent.com/99360129/165219697-b1227398-8713-46c4-ba2a-7cca647e72aa.png)
        - ![erro2](https://user-images.githubusercontent.com/99360129/165219734-b3adb272-6fd5-4709-9099-b42b0a55e239.png)

    - (d) ERRO DE CAMPO VAZIO (NOME);
        - ![erro1](https://user-images.githubusercontent.com/99360129/165219812-0ed9b4d6-a3cc-4893-b08a-9678c62e3ddd.png)
        - ![erro2](https://user-images.githubusercontent.com/99360129/165219857-94128ad2-b8e3-453b-86e7-57a4953a41b1.png)
        
    - (e) ERRO DE CAMPO VAZIO (PONTUAÇÃO);
        - ![erro1](https://user-images.githubusercontent.com/99360129/165219909-c75f9269-404e-442e-a756-e2a4b1f423d1.png)
        - ![erro2](https://user-images.githubusercontent.com/99360129/165219930-0502b43f-ea27-4530-9fb6-c66bdf173edc.png)


# Documento de Especificação

Leia o documento de especificação contido em [Especificação do Trabalho 1](https://docs.google.com/document/d/1aa51VNLQ_jpZaEuGkMz2KE8feAkE48-TENZ9eqn48nk/edit?usp=sharing). Preencha o autor.md com as informações relativas ao grupo/autor.
