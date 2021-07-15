# Projeto de Controlador para Obtenção de Caminho Mínimo em Grafo Estocástico

Executa o controlador, baseado no algoritmo de Dijkstra, em malha fechada para um grafo estocástico em forma de grade com tamanho *n* x *n*. Um algoritmo *presciente* realiza uma busca em largura para encontrar, dada uma realização das variáveis aleatórias (pesos das arestas), o menor caminho possível no grafo. Os resultados do custo total de ambos, respectivamente, são escritos no arquivo `dados.csv` a cada execução.

## Autores
- [Caio Costa](https://github.com/Atsocs)
- [Gabriel Tostes](https://github.com/gtostes)
- [Samuel Vendramini](https://github.com/samuelv8)

## Execução do programa
### Linux
Para compilar o programa é necessário ter instalado na máquina o CMake na versão 3.19 ou superior. Para verificar a versão instalada, `cmake --version`. Na raiz do diretório, crie uma pasta `build` e vá para ela:

    mkdir -p build
    cd build

Para compilar com o CMake, execute os comandos:

    cmake ..
    make

Finalmente, para executar o programa:

    ./ssp_controller

> **Nota**: o arquivo `dados.csv` é gerado dentro da pasta `build` na primeira execução e, então, acrescentado a cada nova execução.

## Arquivos
- main.cpp: script principal que executa as simulações;
- Plant.h/Plant.cpp: contém as definições e métodos necessários para a dinâmica da planta;
- Controller.h/Controller.cpp: contém o algoritmo do controlador;
- Prescient.h/Prescient.cpp: contém o algoritmo presciente;
- PrintDefinitions.h: script para obter outputs dos grafos da simulação;
- GenerateGraph.py: script auxiliar para gerar imagens dos grafos a partir de outputs da simulação;
- analysis.m: script auxiliar para gerar gráficos e medir o desempenho do controlador.
