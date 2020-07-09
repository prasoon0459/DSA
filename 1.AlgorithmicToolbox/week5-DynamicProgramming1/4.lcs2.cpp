#include <bits/stdc++.h>
using namespace std;

int lcs2(vector<int> &a, vector<int> &b) {
  
  int n=a.size();
  int m=b.size();


  int los [n+1][m+1];

  for(int i=0;i<=max(n,m);i++){
    if(i<=m) los[0][i]=0;
    if(i<=n) los[i][0]=0; 
  }

  for(int j=1;j<=m;j++){
    for(int i=1;i<=n;i++){

      int insertion=los[i][j-1];
      int deletion=los[i-1][j];
      int mismatch=los[i-1][j-1];
      int match=los[i-1][j-1]+1;

      if(a[i-1]==b[j-1]) los[i][j]=max(match, max(insertion,deletion));
      else los[i][j]=max(mismatch, max(insertion,deletion));
    }
  }
  return los[n][m];


}

int main() {
  size_t n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    cin >> a[i];
  }

  size_t m;
  cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    cin >> b[i];
  }

  cout << lcs2(a, b) << endl;
}
