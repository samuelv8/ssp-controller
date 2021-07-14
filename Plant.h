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
}; // struct used to store edges, with destination vertex 'j' and a weight 'w'

typedef vector<vector<edges>> graph_t; // type used to store the graph as an adjacency list

/// Class that defines the plant structure for the problem
class Plant {
public:
    Plant(int n);

    Plant(Plant &P);

    /// Updates the plant edges based on a given step 'w'.
    void update_plant(double w);

    /// Sets an inverted graph to be used by the controller.
    void set_inverted();

    /// Friend functions of prescient and controller declared here to let them access private attributes of class Plant.
    friend double prescient(int u, int dest, Plant &plant, ofstream &fs);

    friend int controller(int u, int dest, Plant &plant, double &w);

    /// Prints the graph edges in defined filestream 'fs'
    friend void print_graph(Plant &plant, ofstream &fs);

private:
    graph_t graph;
    graph_t inverted_graph;
    int size;
    vector<complex<double>> zeros;

    /// Checks if the pair (i, j) can be in the grid.
    bool ingraph(int i, int j);

    /// Evaluates the function used to define the edge values based on current complex function roots (zeros).
    void eval_f(vector<vector<double>> &F);

    /// Updates the edges values.
    void attedges();

    /// Updates the roots (zeros) of the complex function.
    void attroots(double w);

};

/// Uniform distribution in the interval from zero to 'n'.
double uniform(double n);

/// Normal distribution with standard deviance 'stddev' and mean zero.
double normal(double stddev);

#endif //SSP_CONTROLLER_PLANT_H
