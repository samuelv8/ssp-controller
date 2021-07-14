#include "Plant.h"

#define _ << ' ' <<
#define mp make_pair
#define f first
#define s second
using pi = pair<int, int>;

std::random_device rd1;

Plant::Plant(int n) {
    size = n;
    graph.resize(n * n);
    zeros.resize(n);
    for (int i = 0; i < size; i++) {
        zeros[i] = uniform(size) + uniform(size) * 1i;
    }
    for (int i = 0; i < size; i++) { // (i,j) = n * i + j
        for (int j = 0; j < size; j++) {
            //(i+1,j), (i-1,j), (i,j-1), (i,j+1);
            vector<pi> DD{mp(i - 1, j), mp(i + 1, j), mp(i, j - 1), mp(i, j + 1)};
            for (pi nij: DD) {
                if (!ingraph(nij.f, nij.s)) continue;
                int ni = nij.f, nj = nij.s;
                graph[size * i + j].push_back(edges(size * ni + nj, 0));
            }
        }
    }
    attedges();
}

Plant::Plant(Plant &P) {
    size = P.size;
    zeros = P.zeros;
    graph.resize(size * size);
    for (int i = 0; i < P.graph.size(); ++i) {
        for (auto e: P.graph[i]) {
            graph[i].push_back(e);
        }
    }
    inverted_graph.resize(size * size);
    for (int i = 0; i < P.inverted_graph.size(); ++i) {
        for (auto e: P.inverted_graph[i]) {
            inverted_graph[i].push_back(e);
        }
    }
}

void Plant::eval_f(vector<vector<double>> &F) {
    double K = 0.0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            complex<double> z = (i + 0.5) + (j + 0.5) * 1i;
            double tmp = 1;
            for (auto zk : zeros) {
                tmp *= abs(z - zk);
            }
            tmp *= tmp; // abs^2 values
            K += tmp;
            F[i][j] = tmp;
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            F[i][j] *= size * size / K;
        }
    }
}

void Plant::attedges() {
    vector<vector<double>> F(size, vector<double>(size, 0.0));
    eval_f(F);
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            graph[i][j].w = 1 + (F[i / size][i % size] + F[j / size][j % size]) / 2.0;
        }
    }
}

bool Plant::ingraph(int i, int j) {
    return (i >= 0 and j >= 0 and i < size and j < size);
}

void saturate(complex<double> &z, double n) {
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
}

void Plant::attroots(double w) {
    for (auto &z : zeros) {
        double x = normal(sqrt(w));
        double y = normal(sqrt(w));
        complex<double> delta = x + y * 1i;
//        double r = normal(sqrt(w));
//        double theta = uniform(2 * M_PI);
//        complex<double> delta = polar(r, theta);
        z += delta;
        saturate(z, size);
    }
}

void Plant::update_plant(double w) {
    attroots(w);
    attedges();
}

void Plant::set_inverted() {
    inverted_graph.resize(graph.size());
    for (int i = 0; i < graph.size(); i++) {
        for (auto e: graph[i]) {
            inverted_graph[e.j].push_back(edges(i, e.w));
        }
    }
}

double uniform(double n) {
    std::uniform_real_distribution<double> uniform_dist(0, n);
    return uniform_dist(rd1);
}

double normal(double stddev) {
    std::normal_distribution<double> distribution(0, stddev);
    return distribution(rd1);
}

void print_graph(graph_t &g, ofstream &fs) {
    int V = (int) g.size();
    for (int i = 0; i < V; ++i) {
        for (auto &e: g[i]) {
            fs << i _ e.j _ e.w << endl;
        }
    }
}