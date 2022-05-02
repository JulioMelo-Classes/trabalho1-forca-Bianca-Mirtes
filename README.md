# Trabalho-1-Jogo-da-Forca-LP1-2022.1
* Repositório contendo as especificações do Trabalho 1 da disciplina de LP1 do semestre 2022.1
# Introdução ao Jogo da Forca
* O Jogo da Forca consiste no sorteio de uma palavra que aparece para o jogador na forma "_ _ _ _ ... _" e o objetivo do jogo é o jogador ir palpitando letras até formar a palavra e vencer ou esgotar suas tentativas e perder.
* Normalmente, há níveis de dificuldade que interferem no quão frequênte a palavra sorteada vai ser. Por exemplo, as palavras do nível fácil são muito frequêntes como: ÁRVORE, COMIDA, SAÚDE. Enquanto que no nível difícil, poderá surgir palavras como: GRANDILOQUENTE, ESTEREOTIPICO, FILOGEOGRAFICOS.
* Por fim, há o boneco que é o que dá sentido ao nome do jogo. A cada palpite errado, esse boneco vai sendo formado e se o jogador não acertar a palavra até ele ficar completo, ele é enforcado (GAMEOVER):
```
                  O <- 1°
  2º, 3º e 4º -> /|\
           5º -> / \ <- 6º 
```
# Processo de Compilação e Execução do Programa
* Pré-Requisitos:
    - CMAKE; <br />

Para fazer a compilação (criação do executável) e executar o arquivo .exe criado, digite no terminal: <br />
```
    mkdir build
    cd build/
    cmake ..
    cmake --build .
    ./program ../data/base_formatada.txt ../data/base_scores.txt
```
# Validação Dos Arquivos - Testes

1. Arquivo de Palavras e de Scores:
    - (a) ERRO DE INEXISTÊNCIA;  <br />
        - (I) Caso em que o arquivo com a base de palavras não exista.  <br />
            Para testar o erro de "Arquivo Inexistente", execute o comando:
            ```
            ./program ../data/teste_EX_p.txt ../data/base_scores.txt
            ```
            A saída esperada é
            ```
            Erro: Arquivo(s) Inexistente(s) Arquivo: ../data/teste_EX_p.txt
            ```

        - (II) Caso em que o arquivo com os scores não exista.  <br />
            Para testar o erro de "Arquivo Inexistente", execute o comando:
            ```
            ./program ../data/base_formatada.txt ../data/teste_EX_s.txt
            ```
            A saída esperada é:
            ```
            Erro: Arquivo(s) Inexistente(s) Arquivo: ../data/teste_EX_s.txt
            ```
       
2. Arquivo de Palavras:
    - (a) ERRO DE CARACTERE ESPECIAL; <br />
        Para testar o erro de "Caractere Especial", execute o comando:
        ```
            ./program ../data/teste1_p.txt ../data/base_scores.txt
        ```
        A saída esperada é:
         ```
         Erro: Caractere especial encontrado, na linha: 7, palavra/frequência: POPUL@CAO
         ```

    - (b) ERRO DE ESPAÇO EM BRANCO; <br />
        Para testar o erro "Espaço em Branco", execute o comando:
        ```
            ./program ../data/teste2_p.txt ../data/base_scores.txt
        ```
        A saída esperada é:
         ```
         Erro: Espaço em branco encontrado, na linha: 3, palavra/frequência: POL ITICA
         ```

    - (c) ERRO DE PALAVRA COM TAMANHO MENOR OU IGUAL A 4; <br />
        Para testar o erro "Palavra com Tamanho Menor ou Igual a 4", execute o comando:
        ```
            ./program ../data/teste3_p.txt ../data/base_scores.txt
        ```
        A saída esperada é:
        ```
        Erro: Palavra com tamanho menor ou igual a 4, na linha: 7, palavra/frequência: PELO
        ```


    - (d) ERRO DE FREQUÊNCIA NEGATIVA; <br />
        Para testar o erro "Frequência Negativa", execute o comando:
        ```
            ./program ../data/teste4_p.txt ../data/base_scores.txt
        ```
        A saída esperada é:
        ```
        Erro: Frequência Negativa, na linha: 6, palavra/frequência: -277336
        ```

3. Arquivo de Scores:  
    - (a) ERRO DE EXCESSO DE PONTO E VÍRGULA; <br />
        Para testar o erro "Excesso de Ponto e Vírgula", execute o comando:
        ```
            ./program ../data/base_formatada.txt ../data/teste5_s.txt
        ```
        A saída esperada é:

        ```
        Erro: Excesso de ponto e vírgula na linha: 3
        ```
        - ![erro1](https://user-images.githubusercontent.com/82531511/166151162-7e764e26-7b3b-45b8-9503-b02bc543c325.jpeg)


    - (b) ERRO DE FALTA DE PONTO E VÍRGULA; <br />
        Para testar o erro "Falta de Ponto e Vírgula", execute o comando:
        ```
            ./program ../data/base_formatada.txt ../data/teste6_s.txt
        ```
        A saída esperada é:

        ```
        Erro: Falta de ponto e vírgula na linha: 2
        ```
        - ![erro2](https://user-images.githubusercontent.com/82531511/166151195-82af3846-00ff-4f16-8969-10de2995e33b.jpeg)

    - (c) ERRO DE CAMPO VAZIO (DIFICULDADE); <br />
        Para testar o erro "Campo Vazio - DIFICULDADE", execute o comando:
        ```
            ./program ../data/base_formatada.txt ../data/teste7_s.txt
        ```
        A saída esperada é:

        ```
        Erro: Campo DIFICULDADE vazio na linha: 2
        ```
        - ![erro3](https://user-images.githubusercontent.com/82531511/166151236-d1260a54-53fd-4f90-854a-1d97e9e37ebf.jpg)
        

    - (d) ERRO DE CAMPO VAZIO (NOME); <br />
        Para testar o erro "Campo Vazio - NOME", execute o comando:
        ```
            ./program ../data/base_formatada.txt ../data/teste8_s.txt
        ```
        A saída esperada é:
        ```
        Erro: Campo NOME vazio na linha: 4
        ```
        - ![erro4](https://user-images.githubusercontent.com/82531511/166151275-413c01f1-c989-4b1d-957f-781b5ebb0a13.jpg)
        
    - (e) ERRO DE CAMPO VAZIO (PONTUAÇÃO); <br />
        Para testar o erro "Campo Vazio - PONTUAÇÃO", execute o comando:
        ```
            ./program ../data/base_formatada.txt ../data/teste9_s.txt
        ```
        A saída esperada é:
        ```
        Erro: Campo PONTUAÇÃO vazio na linha: 1
        ```
        - ![erro5](https://user-images.githubusercontent.com/82531511/166151311-2cd6b73b-3c01-4477-89ce-e01d12bcf6a3.jpg)


# Documento de Especificação

Leia o documento de especificação contido em [Especificação do Trabalho 1](https://docs.google.com/document/d/1aa51VNLQ_jpZaEuGkMz2KE8feAkE48-TENZ9eqn48nk/edit?usp=sharing). Preencha o autor.md com as informações relativas ao grupo/autor.
