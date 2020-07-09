#include <bits/stdc++.h>
using namespace std;

int partition3(vector<int> A, int sum) {
  
  // cout<<"sum = "<<sum<<'\n';
  if(sum%3!=0)
  return 0;
  int n=A.size();
  int l=sum/3;
  vector<vector<int>> previous(l+1, vector<int> (l+1,0));
  vector<vector<int>>  current(l+1, vector<int> (l+1,0));

  previous[0][0]=1;
  // cout<<"n = "<<n<<'\n';
  for(int i=1;i<=n;i++){
    for(int j=0;j<=l;j++){
      for(int k=0;k<=l;k++){
        if(previous[j][k]==1){
          current[j][k]=1;
        }
        else{
          int x=A[i-1];
          if(j<x && k<x) current[j][k]=0;
          else if(j<x) current[j][k]=previous[j][k-x];
          else if(k<x) current[j][k]=previous[j-x][k];
          else current[j][k]=max(previous[j][k-x],previous[j-x][k]);
        }
      }
    }
    // cout<<"i = "<<i<<"\n "; 
    // for(int p=0;p<=l;p++){
    //   for(int q=0;q<=l;q++){
    //     cout<<current[p][q]<<' ';
    //   }
    //   cout<<"\n ";
    // }
    // cout<<"\n";
    previous=current;
  }
  return current[l][l];
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  int sum=0;
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
    sum=sum+A[i];
  }
  //cout<<"sum="<< sum<<'\n';
  std::cout << partition3(A, sum) << '\n';
}
