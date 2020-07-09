#include <bits/stdc++.h>
using namespace std;

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  int a [n+1];
  a[0]=0;
  a[1]=0;
  int i=2;
  
  while (i<=n) {

    if (i % 6 == 0) {
			a[i]=min(min(a[i/2],a[i/3]),a[i-1])+1;
    } else if (i % 2 == 0) {
      a[i]=min(a[i/2],a[i-1])+1;
    } else if (i % 3 == 0) {
      a[i]=min(a[i/3],a[i-1])+1;
    } else {
			a[i]=a[i-1]+1;
		}
		i++;
  }

	int x=n;
	sequence.push_back(x);
	while(x>1){
		if(x%2 == 0 && a[x]==a[x/2]+1) x=x/2;
		else if(x%3 == 0 && a[x]==a[x/3]+1) x=x/3;
		else x=x-1;
		sequence.push_back(x);
	}
	return sequence;

}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (int i = sequence.size()-1; i >=0; i--) {
   std::cout << sequence[i] << " ";
  }

}
