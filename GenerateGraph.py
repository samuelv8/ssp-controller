"""
Auxiliary script to generate graph figures from the output of the main.cpp script
"""

import os
import networkx as nx
import numpy as np
from matplotlib import pyplot
import sys

def print_graph(f, filename):
    G = nx.DiGraph()
    for line in f:
        i, j, w = map(float, line.strip('\n').split(' '))
        i, j = map(int, [i, j])
        G.add_edge(i, j, weight=w)

    n = int(np.sqrt(len(G.nodes)))
    pos = {i: np.array([i % n, i // n]) for i in G.nodes}
    nx.draw(G, pos, with_labels=True, edgecolors="black", node_color='white', font_size=10, node_size=1000)
    labels = nx.get_edge_attributes(G, 'weight')
    labels = {k: round(v, 2) for (k,v) in labels.items()}
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels, font_color='red', label_pos=0.4)
    # pyplot.show()
    path = os.path.join(os.getcwd(), f'{filename}.png')
    pyplot.savefig(path, format='png')

if __name__ == '__main__':

    filename = sys.argv[1]

    files = []
    curr_file = []
    with open(f'{filename}', 'r') as f:
        for line in f:
            if line.strip('\n'):
                curr_file.append(line)
            else:
                files.append(curr_file.copy())
                curr_file = []

    folder = 'plots'
    for i, file in enumerate(files):
        print_graph(file, f'{folder}/graph{i}')
