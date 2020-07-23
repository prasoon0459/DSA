#include <bits/stdc++.h>
using namespace std;

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &dist, vector<int> &reachable, vector<int> &shortest, long long max_val) {
  
  int n=adj.size();
  vector<int>prev(n,-1);
  dist[s]=0;
  reachable[s]=1;
  for(int i=0;i<n-1;i++){
    queue<int> qu;
    vector<int>visited(n,0);
    visited[s]=1;
    qu.push(s);

    while(!qu.empty()){
      int u=qu.front();
      qu.pop();
      int index=0;
      for(int v:adj[u]){
        if(!visited[v]) qu.push(v);
        visited[v]=1;
        int w=cost[u][index];
        if(dist[v]>dist[u]+w){
          dist[v]=dist[u]+w;
          prev[v]=u;
          reachable[v]=1;
        }
        index++;
      }
    }

  }

  vector<int>vis(n,0);
  queue <int> q,q2;
  q.push(s);
  vis[s]=1;
  while(!q.empty()){
    int u=q.front();
    q.pop();
    int index=0;
    for(int v:adj[u]){
      if(!vis[v]) q.push(v);
      vis[v]=1;
      int w=cost[u][index];
      if(dist[v]>dist[u]+w){
        q2.push(v);
      }
      index++;
    }
  }
  queue<int>q3;
  while(!q2.empty()){
    q3.push(q2.front());
    q2.pop();
  }

  while(!q3.empty()){
    int u=q3.front();
    q3.pop();
    for(int v:adj[u]){
      if(shortest[v]==1){
        q3.push(v);
        shortest[v]=0;
      }
    }
  }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  long long max_val=1;
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
    max_val+=abs(w);
  }
  std::cin >> s;
  s--;
  vector<long long> dist(n, max_val);
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, dist, reachable, shortest, max_val);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << dist[i] << "\n";
    }
  }
}
