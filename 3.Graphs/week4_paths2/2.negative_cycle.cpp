#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost, int max_val) {
  
  int n=adj.size();
  vector<int>dist(n,max_val);
  vector<int>prev(n,-1);
  
  dist[0]=0;
  for(int i=0;i<n-1;i++){
    for(int u=0;u<n;u++){
      int index=0;
      for(int v:adj[u]){
        int w=cost[u][index];
        if(dist[v]>dist[u]+w){
          dist[v]=dist[u]+w;
          prev[v]=u;
        }
        index++;
      }
    }
  }
  for(int u=0;u<n;u++){
    int index=0;
    for(int v:adj[u]){
      int w=cost[u][index];
      if(dist[v]>dist[u]+w){
        return 1;
      }
      index++;
    }
  }
  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  int max_val=1;
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
    max_val+=w;
  }
  std::cout << negative_cycle(adj, cost, max_val);
}
