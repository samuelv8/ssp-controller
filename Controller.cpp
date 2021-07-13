#include<bits/stdc++.h>
//#include<iostream>
//#include<vector>

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
using pl = pair<ll,ll>;
using pi = pair<int,int>;


struct edges{
  int j;
  double w;
  edges(int j, double w): j(j), w(w){};
  edges(){}
};


typedef vector < vector < edges > > graph_t;


void dijkstra(int p, vector < double > &d, graph_t &adj){
  d.assign(adj.size(),1e18);
  d[p] = 0;
  priority_queue < pair < double, int > > pq;
  pq.push(mp(-d[p],p));
  while(!pq.empty()){
    auto u = pq.top(); pq.pop();
    if(d[u.s]<-u.f) continue;
    for(auto v: adj[u.s]){
      if( d[v.j] > -u.f + v.w){
        d[v.j] = -u.f + v.w;
        pq.push(mp(-d[v.j],v.j));
      }
    }
  }
}
//std::uniform_int_distribution<int> d(0, 10);
//
std::random_device rd1;
//
//unsigned seed = d(rd1);
//std::default_random_engine generator(seed);

double normal(double stddev){
  std::normal_distribution<double> distribution(0,stddev);
  auto x = distribution(rd1);
//  cout << "R" _ x << endl;
  return x;
}

void attedges(double var, graph_t &adj){
  for(auto &n: adj){
    for(auto &e: n){
      e.w = e.w + normal(sqrt(var));
      if (e.w<=1) e.w=1;
    }
  }
}

graph_t invert_graph(graph_t graph){
  graph_t graph2;
  graph2.resize(graph.size());
  for(int i=0; i<graph.size(); i++){
    for(auto e: graph[i]){
      graph2[e.j].pb(edges(i,e.w));
    }
  }
  return graph2;
}

int controller(int u, int dest, graph_t &adj, double &w){
  vector < double > d;
  auto invadj = invert_graph(adj);
  dijkstra(dest,d,invadj);
  double mn = 1e18;
  int goV=-1;
  for(auto &e: adj[u]){
    if(d[e.j]+e.w < mn){
      mn = d[e.j]+e.w;
      goV = e.j;
    }
  }
  w = mn - d[goV];
//  cout << "MN" _ mn _ "AR" _ w << endl;
  return goV;
}

bool ingraph(int i, int j, int n){
  if(i>=0 and j>=0 and i<n and j<n) return true;
  return false;
}

double prescient(int u, int dest, graph_t & graph){
    priority_queue<pair<double, pair<int, graph_t*> >> pq;

    pq.push(mp(-0.0, mp(u, &graph)));
    pair<double, pair<int, graph_t*> > g;
    while (true){
        g = pq.top(); pq.pop();
//        cout << g.s.f << " ";
        if (g.s.f == dest) break;
        for (auto &e: (*g.s.s)[g.s.f]){
            auto *ngp = new graph_t;
            *ngp = *g.s.s;
            attedges(e.w, *ngp);
            pq.push(mp(g.f - e.w, mp(e.j, ngp)));
        }
    }
//    cout << endl;
//    cout << endl;
    return -g.f;
}

int main(){
  ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
  cin.tie(nullptr);
#endif
  //freopen("B_15", "r", stdin);
  //freopen("15.out", "w", stdout);

  graph_t adj;
  int n = 3;
  adj.resize(n*n);
  for(int i=0; i<n; i++){ // (i,j) 3*i+j
    for(int j=0; j<n; j++){
      //(i+1,j), (i-1,j), (i,j-1), (i,j+1);
      vector < pi > DD{mp(i-1,j), mp(i+1,j), mp(i,j-1), mp(i,j+1)};
      for(pi nij: DD){
        if(!ingraph(nij.f,nij.s,n)) continue;
        int ni=nij.f, nj=nij.s;
        adj[n*i+j].pb(edges(n*ni+nj, max(double(0),20+(i+1)*(j+1)+normal(1))));
      }
    }
  }
  /*for(int i=0; i<adj.size(); i++){
    cout << "N" _ i << endl;
    for(auto e: adj[i]){
      cout << e.j _ e.w << endl;
    }
  }*/
  graph_t adj_init = adj;
  auto invadj = invert_graph(adj);
  int at=0;
  double T=0;
  while(true){
//    cout << '(' << at/n _ at%n << ')' << endl;
    if(at==n*n-1) break;
    double w;
    at = controller(at,n*n-1,adj, w);
    T += w;
    attedges(w,adj);
  }
//  cout << "T" _ T << endl;
  auto Tp = prescient(0, n*n-1, adj_init);
//  cout << "T_presciente" _ Tp << endl;

  ofstream outdata;
  outdata.open("dados.csv", std::ios_base::app);
  outdata << T << ',' _ Tp << endl;
  outdata.close();

}