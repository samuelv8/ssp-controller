#include "Controller.h"

#define mp make_pair
#define f first
#define s second


/// Basic Dijkstra shortest path algorithm.
void dijkstra(int p, vector<double> &d, graph_t &adj) {
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
    plant.set_inverted();
    dijkstra(dest, d, plant.inverted_graph);
    double mn = 1e18;
    int go = -1;
    for (auto &e: plant.graph[u]) {
        if (d[e.j] + e.w < mn) {
            mn = d[e.j] + e.w;
            go = e.j;
        }
    }
    w = mn - d[go];
    return go;
}