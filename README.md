# Projeto de Controlador para Obtenção de Caminho Mínimo em Grafo Estocástico

Executa o controlador em malha fechada para um grafo estocástico em forma de grade com tamanho $n \times n$, com base no algoritmo de Dijkstra. Um algoritmo *presciente* realiza uma busca em largura para encontrar, dada uma realização das variáveis aleatórias (pesos das arestas), o melhor caminho possível no grafo. Os resultados do custo total de ambos são escritos no arquivo `dados.csv`.

## Execução do programa
### Linux
Para compilar o programa é necessário ter instalado na máquina o CMake na versão 3.19 ou superior. Para verificar a versão instalada, execute:

	cmake --version

Na raiz do diretório, crie uma pasta `build` e vá para ela:

    mkdir -p build
    cd build

Para compilar com o CMake, execute os comandos:

    cmake ..
    make

Finalmente, para executar o programa:

    ./ssp_controller

> **Nota**: o arquivo `dados.csv` é gerado dentro da pasta `build` na primeira execução e, então, acrescentado a cada nova execução.
