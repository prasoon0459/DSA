#include <bits/stdc++.h>
using namespace std;


int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
  int n=a.size();
  int m=b.size();
  int p=c.size();
  bool mat=false;
  int los [n+1][m+1][p+1];

  int max_i=max(max(n,m),p);

  for(int i=0;i<=max_i;i++){
    for(int j=0;j<=max_i;j++){  
      if(i<=m && j<=n) los[j][i][0]=0;
      if(i<=n && j<=p) los[i][0][j]=0;
      if(i<=p && j<=m) los[0][j][i]=0; 
    }
  }

  for(int k=1;k<=p;k++){
    for(int j=1;j<=m;j++){
      for(int i=1;i<=n;i++){
        mat=a[i-1]==b[j-1]&&a[i-1]==c[k-1];
        int maxim=0;
        maxim=max(los[i][j-1][k],maxim);
        maxim=max(los[i-1][j][k],maxim);
        maxim=max(los[i-1][j-1][k],maxim);
        maxim=max(los[i][j-1][k-1],maxim);
        maxim=max(los[i-1][j][k-1],maxim);
        maxim=max(los[i][j][k-1],maxim);

        int match=los[i-1][j-1][k-1];
        if(mat) los[i][j][k]=max(maxim, match+1);
        else los[i][j][k]=max(maxim,match );
      }
    }
    
  }
  // for(int k=0;k<=p;k++){
  //   cout<<"k = "<<k<<endl;
  //   for(int j=0;j<=m;j++){
  //     for(int i=0;i<=n;i++){
  //       cout<<los[i][j][k]<<" ";
  //     }
  //     cout<<endl;
  //   }
  //   cout<<endl;
  // }

  return los[n][m][p];
}

int main() {
  size_t an;
  cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    cin >> a[i];
  }
  size_t bn;
  cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    cin >> b[i];
  }
  size_t cn;
  cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    cin >> c[i];
  }
  cout << lcs3(a, b, c) << endl;
}
