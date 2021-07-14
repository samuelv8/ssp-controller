#include "Plant.h"
#include "Prescient.h"
#include "Controller.h"

#define _ << ' ' <<

int main() {
    int SIZE = 4;
    Plant plant(SIZE);
    Plant plant_init = plant;
    ofstream graph_txt;
//    graph_txt.open("graph.txt", std::ios_base::out);
//    print_graph(adj, graph_txt);
//    graph_txt << endl;


    int at = 0;
    int last = SIZE * SIZE - 1;
    double T = 0;
    while (true) {
//    cout << '(' << at/SIZE _ at%SIZE << ')' << endl;
        if (at == last) break;
        double w;
        at = controller(at, last, plant, w);
        T += w;
        plant.update_plant(w);
//      cout << endl; print_graph(adj);
    }
//    cout << "T" _ T << endl;
    auto Tp = prescient(0, last, plant_init, graph_txt);
//    cout << "T_presciente" _ Tp << endl;
//    graph_txt.close();

    ofstream outdata;
    outdata.open("dados.csv", std::ios_base::app);
    outdata << T << ',' _ Tp << endl;
    outdata.close();
}

