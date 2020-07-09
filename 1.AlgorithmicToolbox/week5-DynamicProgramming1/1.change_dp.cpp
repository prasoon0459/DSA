#include <bits/stdc++.h>
using namespace std;


int get_change(int m) {
  vector <int> min_coins(m+1);
  //base case
  min_coins[0]=0;
  min_coins[1]=1;
  min_coins[2]=2;
  min_coins[3]=1;

  for(int i=4;i<=m;i++){
    min_coins[i]= min(min( min_coins[i-1]+1, min_coins[i-3]+1) , min_coins[i-4]+1);
  }
  return min_coins[m];
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
