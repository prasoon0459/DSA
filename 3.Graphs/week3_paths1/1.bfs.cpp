#include<bits/stdc++.h>
using namespace std;

int distance(vector<vector<int> > &adj, int s, int t) {
  int n=adj.size();
  vector<int> dist(n,n+1);
  queue <int> q;

  dist[s]=0;
  q.push(s);

  while(!q.empty()){
    int u=q.front();
    q.pop();
    for(int v:adj[u]){
      if(dist[v]==n+1){
        q.push(v);
        dist[v]=dist[u]+1;
        if(v==t)return dist[v];
      }
    }
  }

  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
