#include "Plant.h"
#include "Prescient.h"
#include "Controller.h"

#define _ << ' ' <<

/// Main script.
int main() {
    int SIZE = 4; // grid size

    Plant plant(SIZE);
    Plant plant_init = plant;

    ofstream graph_txt;
    if (PRINT) { graph_txt.open("graph.txt", std::ios_base::out); }
    if (PRINT & INIT) {
        print_graph(plant, graph_txt);
        graph_txt << endl;
    }

    // Runs the controller policy for the plant.
    int at = 0;
    int last = SIZE * SIZE - 1;
    double T = 0;
    while (true) {
        if (PRINT & CTRL_PATH) { graph_txt << '(' << at / SIZE _ at % SIZE << ')' << endl; }
        if (at == last) break;
        double w;
        at = controller(at, last, plant, w);
        T += w;
        plant.update_plant(w);
        if (PRINT & CTRL) {
            print_graph(plant, graph_txt);
            graph_txt << endl;
        }
    }
    // Runs the prescient algorithm for the initial plant.
    auto Tp = prescient(0, last, plant_init, graph_txt);

    if (PRINT) { graph_txt.close(); }
    ofstream outdata;
    outdata.open("dados.csv", std::ios_base::app);
    outdata << T << ',' _ Tp << endl; // appends the total costs in file
    outdata.close();
}

