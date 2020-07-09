#include <bits/stdc++.h>
using namespace std;


long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

long long get_maximum_value(const string &exp) {
  
  int n= exp.length()/2 +1 ;
  vector<int> digits;
  vector<char> ops;

  for(int i=0;i<(2*n)-1;i++){
    if(i%2==0)digits.push_back(exp[i]-48);
    else ops.push_back(exp[i]);
  }

  long long max_table[n][n];
  long long min_table[n][n];

  for(int i=0;i<n;i++){
    max_table[i][i]=digits[i];
    min_table[i][i]=digits[i];
  }

  for(int s=1;s<n;s++){
    for(int i=0;i<n-s;i++){
      int j=i+s;
      long long min_=LONG_LONG_MAX;
      long long max_=LONG_LONG_MIN;
      for(int k=i;k<=j-1;k++){
        long long a=eval(max_table[i][k], max_table[k+1][j], ops[k]);
        long long b=eval(max_table[i][k], min_table[k+1][j], ops[k]);
        long long c=eval(min_table[i][k], max_table[k+1][j], ops[k]);
        long long d=eval(min_table[i][k], min_table[k+1][j], ops[k]);
        max_=max( max_, max( a, max( b, max( c, d ) ) ) );
        min_=min( min_, min( a, min( b, min( c, d ) ) ) );
      }
      min_table[i][j]=min_;
      max_table[i][j]=max_;
    }
  }
  return max_table[0][n-1];
}

int main() {
  string s;
  cin >> s;
  cout << get_maximum_value(s) << '\n';
}
