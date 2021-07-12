
class Graph:
    """
    Graph class to be used in this approach
    """
    def __init__(self):
        """
        Number of vertices, edges and a adjacency list with a dict
        """
        self.n_vertices = 0
        self.n_edges = 0
        self.adj_list = {}  # key: vertex, value: dict with adjacent vertices and related weights

    def add_vertex(self, v):
        self.adj_list[v] = {}
        self.n_vertices += 1

    def add_edge(self, u, v, weight):
        # only adds an (u,v) edge if there's no edge from u to v or if it will add a lower weight edge
        if v not in self.adj_list[u]:
            self.adj_list[u][v] = weight
            self.n_edges += 1
        elif self.adj_list[u][v] > weight:
            self.adj_list[u][v] = weight

        if v not in self.adj_list:
            self.n_vertices += 1

    def get_neighbors(self, u):
        if u in self.adj_list:
            return [k for k, v in self.adj_list[u].items()]

    def get_edge_weight(self, u, v):
        if u in self.adj_list:
            if v in self.adj_list[u]:
                return self.adj_list[u][v]

