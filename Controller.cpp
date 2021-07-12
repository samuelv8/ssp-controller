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

void dijkstra(int p, vector < double > &d, vector < vector < edges > > &adj){
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

std::default_random_engine generator;

double normal(double stddev){
  std::normal_distribution<double> distribution(0,stddev);
  return distribution(generator);
}

void attedges(double stddev, vector < vector < edges > > &adj){
  for(auto &n: adj){
    for(auto &e: n){
      e.w = e.w + normal(stddev);
      if (e.w<=0) e.w=0;
    }
  }
}

vector<vector<edges>> invert_graph(vector<vector<edges>> graph){
  vector<vector<edges>> graph2;
  graph2.resize(graph.size());
  for(int i=0; i<graph.size(); i++){
    for(auto e: graph[i]){
      graph2[e.j].pb(edges(i,e.w));
    }
  }
  return graph2;
}

int controller(int u, int dest, vector < vector < edges > > &adj){
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
  cout << "MN" _ mn _ "AR" _ (mn-d[goV]) << endl;
  return goV;
}

bool ingraph(int i, int j, int n){
  if(i>=0 and j>=0 and i<n and j<n) return true;
  return false;
}

int main(){
  ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
  cin.tie(nullptr);
#endif
  //freopen("B_15", "r", stdin);
  //freopen("15.out", "w", stdout);

  vector < vector < edges > > adj;
  int n = 6;
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
  auto invadj = invert_graph(adj);
  int at=0;
  while(1){
    cout << '(' << at/n _ at%n << ')' << endl;
    if(at==n*n-1) break;
    at = controller(at,n*n-1,adj);
    attedges(5,adj);
  }

}