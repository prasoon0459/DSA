#include <bits/stdc++.h>
using namespace std;

int edit_distance(const string &str1, const string &str2) {
  
  int n=str1.length();
  int m=str2.length();


  int distances [n+1][m+1];

  for(int i=0;i<=max(n,m);i++){
    if(i<=m) distances[0][i]=i;
    if(i<=n) distances[i][0]=i; 
  }

  for(int j=1;j<=m;j++){
    for(int i=1;i<=n;i++){

      int insertion=distances[i][j-1] + 1;
      int deletion=distances[i-1][j] + 1;
      int mismatch=distances[i-1][j-1] + 1;
      int match=distances[i-1][j-1];

      if(str1[i-1]==str2[j-1]) distances[i][j]=min(match, min(insertion,deletion));
      else distances[i][j]=min(mismatch, min(insertion,deletion));
    }
  }
  return distances[n][m];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
