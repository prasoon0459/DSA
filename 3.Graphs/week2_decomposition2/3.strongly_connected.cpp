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

void exploreSCC(vector<vector<int> > &adj,vector<bool> &visited, int x) {
  visited[x]=true;
  for(int w: adj[x]){
    if(!visited[w]){
      exploreSCC(adj, visited, w);
    }
  }
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
int number_of_strongly_connected_components(vector<vector<int> > &adj,vector<vector<int> > &adj_rev ){
  int n=adj.size();
  vector<bool> visited(n, false);
  stack<int>order=dfs(adj_rev);

  int cc=0;
  while(!order.empty()){
    int v= order.top();
    if(!visited[v]){

      exploreSCC(adj,visited,v);
      cc++;
    }
    order.pop();
  }
  return cc;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > adj_rev(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj_rev[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj, adj_rev);
}
