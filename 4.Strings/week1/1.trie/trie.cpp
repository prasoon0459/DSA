#include <bits/stdc++.h>
using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  edges starting_map;
  t.push_back(starting_map);
  int node_cnt=1;
  for(string pattern:patterns){
    int current_node=0;
    for(int i=0;i<pattern.length();i++){
      char curr_sym=pattern[i];
      auto itr=t[current_node].find(curr_sym);
      if(itr!=t[current_node].end()){
        current_node=itr->second;
      }
      else{
        t[current_node].insert(make_pair(curr_sym,node_cnt));
        edges e; t.push_back(e);
        current_node=node_cnt;
        node_cnt++;
      }
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}