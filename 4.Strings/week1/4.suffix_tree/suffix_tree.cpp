#include <bits/stdc++.h>
using namespace std;

struct subStr{
  int st_index;
  int len;
  int pos;
};

typedef map<char, subStr > edges;
typedef vector<edges> tree;
// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
tree ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  tree t;
  int l=text.length();
  edges starting_map;
  t.push_back(starting_map);
  int node_cnt=1;
  for(int i=0;i<l;i++){
    bool flag=false;
    int starting_index=i;
    int current_node=0;
    char curr_sym=text[starting_index];
    auto itr=t[current_node].find(curr_sym);

    if(itr!=t[current_node].end()){
      int cnt=0;
      while(starting_index+cnt<=l){
        if(cnt>=itr->second.len){
          starting_index=starting_index+cnt;
          curr_sym=text[starting_index];
          int pos=itr->second.pos;
          itr=t[pos].find(curr_sym);
          if(itr==t[pos].end()){
            t[pos].insert(make_pair(curr_sym,subStr{starting_index, l-starting_index , node_cnt}));
            edges e; t.push_back(e);
            node_cnt++;
            flag=true;
            break;
          }
          cnt=0;
        }
        if(text[starting_index+cnt]==text[itr->second.st_index + cnt])cnt++;
        else break;
      }
      if(!flag){
        int oldNode=itr->second.pos;
        int new_node1=node_cnt;
        int new_node2=node_cnt+1;
        int old_len=itr->second.len;
        itr->second.pos=new_node1; 
        itr->second.len=cnt;

        //making place for 2 new nodes
        edges edges1; t.push_back(edges1);
        edges edges2; t.push_back(edges2);

        //new node1 to new node2
        subStr e1=subStr{starting_index+cnt,l-starting_index-cnt, new_node2};
        t[new_node1].insert(make_pair(text[starting_index+cnt],e1));

        //new node1 to old node
        subStr e2=subStr{itr->second.st_index+cnt,old_len-cnt, oldNode};
        t[new_node1].insert(make_pair(text[itr->second.st_index+cnt],e2));

        //total 2 new nodes
        node_cnt=node_cnt+2;
      }
    }
    else{
      t[current_node].insert(make_pair(curr_sym,subStr{starting_index, l-starting_index , node_cnt}));
      edges e; t.push_back(e);
      node_cnt++;
    }
  }
  return t;
}

int main() {
  string text;
  cin >> text;
  tree t = ComputeSuffixTreeEdges(text);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      cout<<text.substr(j.second.st_index,j.second.len)<<'\n';
    }
  }

  return 0;
}
