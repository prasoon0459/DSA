#include <bits/stdc++.h>
using namespace std;

int explore(vector<vector<int> > &adj,vector<bool> &visited, int x, stack<int> &order) {
  visited[x]=true;
  for(int w: adj[x]){
    if(!visited[w]){
      explore(adj, visited, w, order);
    }
  }
  order.push(x);
  return 0;
}
stack<int> dfs(vector<vector<int> > &adj) {
  int n=adj.size();
  vector<bool> visited(n, false);
  stack<int> order;
  for(int i=0;i<n;i++){
    if(!visited[i]){
      explore(adj, visited, i, order);
    }
  }
  return order;
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
  stack<int> order = dfs(adj);
  while(!order.empty()){
    cout<<order.top()+1<<" ";
    order.pop();
  }

}
