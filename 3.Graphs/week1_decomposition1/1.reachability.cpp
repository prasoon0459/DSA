#include <bits/stdc++.h>
using namespace std;


int reach(vector<vector<int> > &adj,vector<bool> &visited, int x, int y) {
  visited[x]=true;
  if(x==y) return 1;
  for(int w: adj[x]){
    if(!visited[w]){
      int reached=reach(adj, visited, w, y);
      if(reached) return 1; 
    }
  }
  return visited[y]==true?1:0;
}

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  vector<bool> visited(n, false);
  int x, y;
  cin >> x >> y;
  cout << reach(adj,visited, x - 1, y - 1);
}
