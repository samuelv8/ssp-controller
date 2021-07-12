import networkx as nx
import numpy as np
from matplotlib import pyplot

if __name__ == '__main__':

    n = 4

    G = nx.DiGraph()
    for i in range(n):
        for j in range(n):
            G.add_node((i, j))

    for i in range(n):
        for j in range(n):
            x = [(i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)]
            for y in x:
                if 0 <= y[0] < n and 0 <= y[1] < n:
                    G.add_edge((i, j), y, weight=(i+1)*(j+1))

    pos = {(i, j): np.array([i, j]) for (i,j) in G.nodes}
    nx.draw(G, pos, with_labels=True, edgecolors="black", node_color='white', font_size=10, node_size=1000)
    labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels, font_color='red')
    pyplot.show()
