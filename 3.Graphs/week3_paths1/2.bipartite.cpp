#include<bits/stdc++.h>
using namespace std;

int distance(vector<vector<int> > &adj, int s,  vector<int> &dist, vector<int> &visited) {
  int n=adj.size();
  queue <int> q;
  dist[s]=0;
  q.push(s);
  visited[s]=1; // starting vertex black
  while(!q.empty()){
    int u=q.front();
    int color=visited[u];
    q.pop();
    for(int v:adj[u]){
      if(color==visited[v]) return 0;// if same color as parent
      visited[v]=color==1?2:1; // giving opposite color to parent
      if(dist[v]==n+1){
        q.push(v);
        dist[v]=dist[u]+1;
      }
    }
  }
  return 1;
}

int bipartite(vector<vector<int> > &adj) {
  int n=adj.size();
  vector<int> dist(n,n+1);  //write your code here
  
  /** 
   * 0 -> not visited
   * 1 -> black
   * 2 -> red
   **/
  vector<int> visited(n,0);

  for(int i=0;i<n;i++){
    if(visited[i]==0){
      int res=distance(adj,i,dist,visited);
      if(res==0) return 0; 
    }
  }
  return 1;
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
  std::cout << bipartite(adj);
}
