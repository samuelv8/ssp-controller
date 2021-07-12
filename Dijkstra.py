import sys
import heapq
from Graph import Graph


def dijkstra(G: Graph, frm, to):
    """
    Dijkstra shortest path algorithm
    :param G: Graph object
    :param frm: initial vertex
    :param to: target vertex
    :return: tuple with minimum distance and a list with the related shortest path
    """
    info = {}  # information to be returned
    visited = {}  # indicates if vertices were visited or not
    queue = []  # pqueue of unvisited vertices
    for u in G.get_vertices():
        if u == frm:
            queue.append((0, u))
            info[u] = (0, None)
        else:
            queue.append((sys.maxsize, u))
            info[u] = (sys.maxsize, None)
        visited[u] = False

    heapq.heapify(queue)
    while queue:
        d, u = heapq.heappop(queue)
        visited[u] = True
        if u == to:
            break  # stops search when 'to' vertex has definitive distance
        for v in G.get_neighbors(u):
            if not visited[v]:
                tmp = info[u][0] + G.get_edge_weight(u, v)
                if info[v][0] > tmp:
                    info[v] = (tmp, u)
                    heapq.heappush(queue, (tmp, u))
    min_dist = 0
    min_path = [to]
    dis, pred = info[to]
    if pred is None:
        raise Exception('no path!')
    while pred:
        min_dist += dis
        min_path.insert(0, pred)
        dis, pred = info[pred]
    return min_dist, min_path


if __name__ == '__main__':
    g = Graph()
    g.add_vertex('a')
    g.add_vertex('b')
    g.add_vertex('c')
    g.add_vertex('d')
    g.add_vertex('e')
    g.add_vertex('f')
    g.add_edge('a', 'b', 7)
    g.add_edge('a', 'c', 9)
    g.add_edge('a', 'f', 14)
    g.add_edge('b', 'c', 10)
    g.add_edge('b', 'd', 15)
    g.add_edge('c', 'd', 11)
    g.add_edge('c', 'f', 2)
    g.add_edge('d', 'e', 6)
    g.add_edge('e', 'f', 9)

    dmin, path = dijkstra(g, 'a', 'e')
    print(f'Min dist: {dmin}, Shortest path: {path}')

