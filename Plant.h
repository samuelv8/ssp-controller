#ifndef SSP_CONTROLLER_PLANT_H
#define SSP_CONTROLLER_PLANT_H

#include<bits/stdc++.h>

using namespace std;

struct edges {
    int j;
    double w;

    edges(int j, double w) : j(j), w(w) {};

    edges(const edges &e) = default;

    edges() = default;
};

typedef vector<vector<edges>> graph_t;

class Plant {
public:
    Plant(int n);

    Plant(Plant &P);

    void update_plant(double w);

    void set_inverted();

    friend double prescient(int u, int dest, Plant &plant, ofstream &fs);

    friend int controller(int u, int dest, Plant &plant, double &w);

    friend void print_graph(Plant &plant, ofstream &fs);

private:
    graph_t graph;
    graph_t inverted_graph;
    int size;
    vector<complex<double>> zeros;

    bool ingraph(int i, int j);

    void eval_f(vector<vector<double>> &first);

    void attedges();

    void attroots(double w);

};

double uniform(double n);

double normal(double stddev);

#endif //SSP_CONTROLLER_PLANT_H
