
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
        self.adj_list = {}  # key: vertex, value: list of lists with adjacent vertices and related weights

    def add_vertex(self, v):
        self.adj_list[v] = []
        self.n_vertices += 1

    def add_edge(self, u, v, weight):
        if [v, weight] not in self.adj_list[u]:
            self.adj_list[u].append([v, weight])
            self.n_edges += 1

        if v not in self.adj_list:
            self.n_vertices += 1
