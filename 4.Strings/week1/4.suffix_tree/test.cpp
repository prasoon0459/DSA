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
    cout<<"for  i = "<<i<<'\n';
    int starting_index=i;
    int current_node=0;
    char curr_sym=text[starting_index];
    auto itr=t[current_node].find(curr_sym);

    cout<<" itr found -> "<<itr->first<<" {"<<itr->second.st_index<<", "<<itr->second.len<<", "<<itr->second.pos<<"}\n";

    if(itr!=t[current_node].end()){
      cout<<" exists\n";
      int cnt=0;
      while(starting_index+cnt<=l){
        cout<<"   cnt= "<<cnt<<'\n';
        if(cnt>=itr->second.len){
          cout<<"     node encountered \n";
          starting_index=starting_index+cnt;
          curr_sym=text[starting_index];
          cout<<"     starting index= "<<starting_index<<" current sym= "<<curr_sym;
          int pos=itr->second.pos;
          itr=t[pos].find(curr_sym);
          if(itr==t[pos].end()){
            cout<<"       curr sym not found -> adding new edge at "<<node_cnt<<"\n";
            t[pos].insert(make_pair(curr_sym,subStr{starting_index, l-starting_index , node_cnt}));
            edges e; t.push_back(e);
            node_cnt++;
            flag=true;
            break;
          }
          cnt=0;
        }
        if(text[starting_index+cnt]==text[itr->second.st_index + cnt])cnt++;
        else {
          cout<<"     breaking at "<<cnt<<'\n';
          break;
        }
      }
      if(!flag){
    
        cout<<"   flag not set\n";
        int oldNode=itr->second.pos; // 1
        cout<<"   old node = "<<oldNode<<'\n';
        int new_node1=node_cnt;
        cout<<"   new node1 = "<<new_node1<<'\n';
        int new_node2=node_cnt+1;
        cout<<"   new node2 = "<<new_node2<<'\n';

        int old_len=itr->second.len;
        itr->second.pos=new_node1; //2
        itr->second.len=cnt;
        cout<<"   old edge len set to "<<itr->second.len<<'\n';

        // insert child 1 -> $
        edges edges1; t.push_back(edges1);
        edges edges2; t.push_back(edges2);


        subStr e1=subStr{starting_index+cnt,l-starting_index-cnt, new_node2};
        cout<<"   adding substr ("<<starting_index+cnt<<", "<<l-starting_index-cnt<<", "<<new_node2<<") to  "<<new_node1<<'\n';
        t[new_node1].insert(make_pair(text[starting_index+cnt],e1));

        // insert child 2 -> A$
        subStr e2=subStr{itr->second.st_index+cnt,old_len-cnt, oldNode};
        cout<<"   adding substr ("<<itr->second.st_index+cnt<<", "<<old_len-cnt<<", "<<oldNode<<") to  "<<new_node1<<'\n';
        t[new_node1].insert(make_pair(text[itr->second.st_index+cnt],e2));

        node_cnt=node_cnt+2;
        // fix parent edge

      }
    }
    else{
      cout<<" doesnt exist\n";
      cout<<"   adding substr ("<<starting_index<<", "<<l-starting_index<<", "<<node_cnt<<") to  "<<current_node<<'\n';
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
