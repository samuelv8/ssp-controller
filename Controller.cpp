#include "Controller.h"

#define mp make_pair
#define f first
#define s second

graph_t invert_graph(graph_t graph) {
    graph_t graph2;
    graph2.resize(graph.size());
    for (int i = 0; i < graph.size(); i++) {
        for (auto e: graph[i]) {
            graph2[e.j].push_back(edges(i, e.w));
        }
    }
    return graph2;
}

void dijkstra(int p, vector<double> &d, graph_t adj) {
    d.assign(adj.size(), 1e18);
    d[p] = 0;
    priority_queue<pair<double, int> > pq;
    pq.push(mp(-d[p], p));
    while (!pq.empty()) {
        auto u = pq.top();
        pq.pop();
        if (d[u.s] < -u.f) continue;
        for (auto v: adj[u.s]) {
            if (d[v.j] > -u.f + v.w) {
                d[v.j] = -u.f + v.w;
                pq.push(mp(-d[v.j], v.j));
            }
        }
    }
}

int controller(int u, int dest, Plant &plant, double &w) {
    vector<double> d;
    auto invadj = invert_graph(plant.graph);
    dijkstra(dest, d, invadj);
    double mn = 1e18;
    int goV = -1;
    for (auto &e: plant.graph[u]) {
        if (d[e.j] + e.w < mn) {
            mn = d[e.j] + e.w;
            goV = e.j;
        }
    }
//    w = mn - d[goV];
    return goV;
}