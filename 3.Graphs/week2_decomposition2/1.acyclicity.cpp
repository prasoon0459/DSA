#include <bits/stdc++.h>
using namespace std;
int clk =1;
int explore(vector<vector<int> > &adj,vector<bool> &visited, int x,vector<int> &pre,vector<int> &post) {
  visited[x]=true;
  pre[x]=clk++;
  for(int w: adj[x]){
    if(visited[w]&&post[w]==0){
      return 1;     //cycle found
    }
    if(!visited[w]){
      int cycle=explore(adj, visited, w, pre, post);
      if(cycle==1) return 1;
    }
  }
  post[x]=clk++;
  return 0;
}
int acyclic(vector<vector<int> > &adj) {
  int n=adj.size();
  vector<bool> visited(n, false);
  vector<int> pre(n,0);
  vector<int> post(n,0);
  for(int i=0;i<n;i++){
    if(!visited[i]){
      int cycle=explore(adj, visited, i, pre, post);
      if(cycle==1) return 1;
    }
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
