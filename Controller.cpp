#include<bits/stdc++.h>

#include <tuple>

using namespace std;
#define _ << ' ' <<
#define pb push_back
#define all(x) begin(x), end(x)
#define mp make_pair
#define f first
#define s second
#define sz(x) int((x).size())
using ll = long long;
using db = long double;
using pl = pair<ll, ll>;
using pi = pair<int, int>;


struct edges {
    int j;
    double w;

    edges(int j, double w) : j(j), w(w) {};

    edges() {}
};


typedef vector<vector<edges> > graph_t;

int SIZE = 3;

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

std::random_device rd1;

double uniform(double n) {
    std::uniform_real_distribution<double> uniform_dist(0, n);
    return uniform_dist(rd1);
}

double normal(double stddev) {
    std::normal_distribution<double> distribution(0, stddev);
    auto x = distribution(rd1);
    return x;
}

void eval_f(const vector<complex<double>> &zs, vector<vector<double>> &f) {
    double K = 0.0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            complex<double> z = (i + 0.5) + (j + 0.5) * 1i;
            double tmp = 1;
            for (auto zk : zs) {
                tmp *= abs(z - zk);
            }
            tmp *= tmp; // abs^2 values
            K += tmp;
            f[i][j] = tmp;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            f[i][j] *= SIZE * SIZE / K;
        }
    }
}

void attedges(graph_t &adj, vector<complex<double>> &zs) {
//  for(auto &SIZE: adj){
//    for(auto &e: SIZE){
//      e.w = e.w + normal(sqrt(var));
//      if (e.w<=1) e.w=1;
//    }
//  }
    vector<vector<double>> f(SIZE, vector<double>(SIZE, 0));
    eval_f(zs, f);
    for (int i = 0; i < adj.size(); ++i) {
        for (int j = 0; j < adj[i].size(); ++j) {
            adj[i][j].w = 1 + (f[i / SIZE][i % SIZE] + f[j / SIZE][j % SIZE]) / 2.0;
        }
    }
}

complex<double> saturate(complex<double> z, double n) {
    if (imag(z) < 0.0) {
        z = real(z) + 0.0 * 1i;
    }
    if (imag(z) > n) {
        z = real(z) + n * 1i;
    }
    if (real(z) < 0.0) {
        z = 0.0 + imag(z) * 1i;
    }
    if (real(z) > n) {
        z = n + imag(z) * 1i;
    }
    return z;
}

void attroots(vector<complex<double>> &zs, double w) {
    for (auto &z : zs) {
        double x = normal(sqrt(w));
        double y = normal(sqrt(w));
        complex<double> delta = x + y * 1i;
//        double r = normal(sqrt(w));
//        double theta = uniform(2 * M_PI);
//        complex<double> delta = polar(r, theta);
        z += delta;
        z = saturate(z, SIZE);
    }
}

graph_t invert_graph(graph_t graph) {
    graph_t graph2;
    graph2.resize(graph.size());
    for (int i = 0; i < graph.size(); i++) {
        for (auto e: graph[i]) {
            graph2[e.j].pb(edges(i, e.w));
        }
    }
    return graph2;
}

int controller(int u, int dest, graph_t &adj, double &w) {
    vector<double> d;
    auto invadj = invert_graph(adj);
    dijkstra(dest, d, invadj);
    double mn = 1e18;
    int goV = -1;
    for (auto &e: adj[u]) {
        if (d[e.j] + e.w < mn) {
            mn = d[e.j] + e.w;
            goV = e.j;
        }
    }
    w = mn - d[goV];
//  cout << "MN" _ mn _ "AR" _ w << endl;
    return goV;
}

bool ingraph(int i, int j, int n) {
    if (i >= 0 and j >= 0 and i < n and j < n) return true;
    return false;
}

void print_graph(graph_t &g, ofstream &fs) {
    int V = (int) g.size();
//    int E = 0;
//    for (auto &v: g){
//        E += (int) v.size();
//    }
//    cout << "V" _ V << endl;
//    cout << "E" _ E << endl;
    for (int i = 0; i < V; ++i) {
        for (auto &e: g[i]) {
            fs << i _ e.j _ e.w << endl;
        }
    }
}

typedef pair<double, pair<int, pair<vector<complex<double> > *, graph_t *>>> pq_type;

double prescient(int u, int dest, graph_t &graph, vector<complex<double>> &zs, ofstream &fs) {
    priority_queue<pq_type> pq;

    pq.push(mp(-0.0, mp(u, mp(&zs, &graph))));
    pq_type g;
    while (true) {
        g = pq.top();
        pq.pop();
//        print_graph(*g.s.s.s, fs);
//        fs << endl;
//        cout << g.s.f << " ";
        if (g.s.f == dest) break;
        for (auto &e: (*g.s.s.s)[g.s.f]) {
            auto *ngp = new graph_t;
            *ngp = *g.s.s.s;
            auto *nzsp = new vector<complex<double>>;
            *nzsp = *g.s.s.f;
            attroots(*nzsp, e.w);
            attedges(*ngp, *nzsp);
            pq.push(mp(g.f - e.w, mp(e.j, mp(nzsp, ngp))));
        }
    }
//    cout << endl;
//    cout << endl;
    return -g.f;
}

int main() {
    ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
    cin.tie(nullptr);
#endif
    //freopen("B_15", "r", stdin);
    //freopen("15.out", "w", stdout);

    graph_t adj;
    adj.resize(SIZE * SIZE);
    vector<complex<double>> zs;
    zs.resize(SIZE);
    for (int i = 0; i < SIZE; i++) {
        zs[i] = uniform(SIZE) + uniform(SIZE) * 1i;
    }
    vector<complex<double>> zs_init = zs;
    vector<vector<double>> f;

    for (int i = 0; i < SIZE; i++) { // (i,j) 3*i+j
        for (int j = 0; j < SIZE; j++) {
            //(i+1,j), (i-1,j), (i,j-1), (i,j+1);
            vector<pi> DD{mp(i - 1, j), mp(i + 1, j), mp(i, j - 1), mp(i, j + 1)};
            for (pi nij: DD) {
                if (!ingraph(nij.f, nij.s, SIZE)) continue;
                int ni = nij.f, nj = nij.s;
                adj[SIZE * i + j].pb(edges(SIZE * ni + nj, 0));
            }
        }
    }
    attedges(adj, zs);

    ofstream graph_txt;
    graph_txt.open("graph.txt", std::ios_base::out);
    print_graph(adj, graph_txt);
    graph_txt << endl;

    graph_t adj_init = adj;

    auto invadj = invert_graph(adj);
    int at = 0;
    double T = 0;
    while (true) {
//    cout << '(' << at/SIZE _ at%SIZE << ')' << endl;
        if (at == SIZE * SIZE - 1) break;
        double w;
        at = controller(at, SIZE * SIZE - 1, adj, w);
        T += w;
        attroots(zs, w);
        attedges(adj, zs);
//      cout << endl; print_graph(adj);
    }
//    cout << "T" _ T << endl;
    auto Tp = prescient(0, SIZE * SIZE - 1, adj_init, zs_init, graph_txt);
//    cout << "T_presciente" _ Tp << endl;
    graph_txt.close();

    ofstream outdata;
    outdata.open("dados.csv", std::ios_base::app);
    outdata << T << ',' _ Tp << endl;
    outdata.close();
}