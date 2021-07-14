#include "Prescient.h"

#define mp make_pair
#define f first
#define s second

typedef pair<double, pair<int, Plant*>> pq_type;

double prescient(int u, int dest, Plant &plant, ofstream &fs) {
    priority_queue<pq_type> pq;

    pq.push(mp(-0.0, mp(u, &plant)));
    pq_type g;
    while (true) {
        g = pq.top();
        pq.pop();
//        print_graph(*g.s.s.s, fs);
//        fs << endl;
//        cout << g.s.f << " ";
//        cout.flush();
        if (g.s.f == dest) break;
        for (auto &e: (g.s.s->graph)[g.s.f]) {
            auto npp = new Plant(*g.s.s);
            npp->update_plant(e.w);
            pq.push(mp(g.f - e.w, mp(e.j, npp)));
        }
    }
//    cout << endl;
//    cout << endl;
    return -g.f;
}