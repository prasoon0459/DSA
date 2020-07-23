#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x;
  int y;
};

struct Edge{
  int u;
  int v;
  int distSqr;
};

struct disjSet{
  vector<int> parent;
  vector<int> rank;
  int no_of_sets=0;

  void MakeSet(int i){
    parent[i]=i;
    rank[i]=0;
    no_of_sets++;
  }
  int Find(int i){
    if (i!=parent[i])
      parent[i]=Find(parent[i]);
    return parent[i];
  }
  void Union(int i,int j){
    int i_id=Find(i);
    int j_id=Find(j);
    if(i_id==j_id) return;
    no_of_sets--;
    if(rank[i_id]>rank[j_id])
      parent[j_id]=i_id;
    else
      parent[i_id]=j_id;
      if(rank[i_id]==rank[j_id])
        rank[j_id]=rank[j_id]+1;
  }
};

bool compare(Edge e1, Edge e2){
  return e1.distSqr<e2.distSqr;
}

int compDist(Point p1,Point p2){
  return (pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

double clustering(vector <Point> vertices, int k) {
  double result = 0.;
  int n= vertices.size();
  disjSet ds;
  ds.parent.resize(n);
  ds.rank.resize(n);
  for(int i=0;i<n;i++){
    ds.MakeSet(i);
  }
  vector<Edge> edges;
  for(int i=0;i<n-1;i++){
    for(int j=i+1;j<n;j++){
      Edge e;
      e.u=i;e.v=j;
      e.distSqr=compDist(vertices[i],vertices[j]);
      edges.push_back(e);
    }
  }
  sort(edges.begin(),edges.end(), compare);
  
  for(Edge e: edges){
    
    if(ds.Find(e.u)!=ds.Find(e.v)){
      if(ds.no_of_sets==k) return sqrt(e.distSqr);
      ds.Union(e.u,e.v);
    }
  }

  return -1;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<Point> vertices(n);
  for (size_t i = 0; i < n; i++) {
    Point p;
    std::cin >> p.x >> p.y;
    vertices[i]=p;
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(vertices, k) << std::endl;
}
