#include <bits/stdc++.h>
using namespace std;

int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  int n=w.size();
  vector<int> previous(W+1);
  vector<int> current(W+1);

  for(int i=0;i<n;i++){
    for(int weight=1;weight<=W;weight++){

      int max_=previous[weight];
      if(weight-w[i]>=0){
        max_=max(previous[weight-w[i]]+w[i], max_);
      }
      current[weight]=max_;
    }

    previous=current;
  }
  return current[W];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
