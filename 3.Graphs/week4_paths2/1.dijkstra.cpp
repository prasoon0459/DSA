#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
struct binHeap{

  vector<pi> q;
  int size=0;
  vector<int> pos;

  int parent(int index){
    return ((index+1)/2) - 1;
  }
  int LeftChild(int index){
    return (2 * index) + 1;
  }
  int RightChild(int index){
    return (2 * index) + 2;
  }
  void siftUp(int index){
    while (index > 0 && q[ parent (index)].first > q[index].first){
      swap (q[ parent (index)] , q[index]);
      swap (pos[ q[parent (index)].second] , pos[q[index].second]);
      index = parent (index);
    }
  }
  void siftDown(int index){
    int minindex=index;
    int l=LeftChild(index);
    if(l<size && q[l].first<q[minindex].first)
      minindex=l;
    int r=RightChild(index);
    if(r<size && q[r].first<q[minindex].first)
      minindex=r;
    if(index!=minindex){
      swap(q[index], q[minindex]);
      swap(pos[q[index].second], pos[q[minindex].second]);
      siftDown(minindex);
    }
  }
  void insert(pi p){
    size++;
    pos.resize(size);
    q.resize(size);
    q[size-1]=p;
    pos[p.second]=size-1;
    siftUp(size-1);
  }
  pi extractMin(){
    pi result= q[0];
    q[0]=q[size-1];
    pos[q[0].second]=0;
    pos[result.second]=-1;
    size--;
    q.resize(size);
    siftDown(0);
    return result;
  }
  void changePriority(int v, int priority){
    int i=pos[v];
    int oldp=q[i].first;
    q[i].first=priority;
    if(priority<oldp) siftUp(i);
    else siftDown(i);
  }
  
};

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t, int max_val) {
  
  int n=adj.size();
  vector<int> dist(n,max_val);
  vector<int> prev(n,-1);

  dist[s]=0;
  binHeap h;
  for(int i=0;i<n;i++){
    h.insert(make_pair( dist[i],i ));//insert dist value in priority queue
  }
  while(h.size>0){
    pi u=h.extractMin();//exxtract with minimum priority
    int index=0;

    for(int v : adj[u.second]){
      int w=cost[u.second][index];
      if(dist[v]>dist[u.second]+w){
        dist[v]=dist[u.second]+w;
        prev[v]=u.second;
        h.changePriority(v, dist[v]);//change priority of v to new dist[v] value
      }
      index++;
    }
  }
  return dist[t]==max_val? -1: dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  int max_val=0;
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
    max_val+=w;
  }
  max_val++;
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t, max_val);
}
