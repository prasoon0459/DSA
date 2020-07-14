#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
  
  public:
    long long key;
    int left;
    int right;
    long long lb=INT32_MIN;
    long long ub=INT32_MAX;

    Node() : key(0), left(-1), right(-1){}
    Node(long long key_, int left_, int right_) : key(key_), left(left_), right(right_){}

  
    void setLb(long long lb_){
      lb=lb_;
    }

    void setUb(long long ub_){
      ub=ub_;
    }

};

bool IsBinarySearchTree(vector<Node>& tree, int index) {

  int left= tree[index].left;
  int right= tree[index].right;
  bool leftExist=left!=-1;
  bool rightExist=right!=-1;


  if(!leftExist&&!rightExist){
    return tree[index].key<=tree[index].ub && tree[index].key>=tree[index].lb;
  } 

  if(leftExist) {
    // cout<<"setting lb="<<tree[index].lb<<" and ub="<<tree[index].key<< "for "<<tree[left].key<<'\n';
    tree[left].setUb(tree[index].key-1);
    tree[left].setLb(tree[index].lb);
  }
  if(rightExist){
    // cout<<"setting lb="<<tree[index].key<<" and ub="<<tree[index].ub<< "for "<<tree[right].key<<'\n';
    tree[right].setLb(tree[index].key);
    tree[right].setUb(tree[index].ub);
  } 

  if(tree[index].key>tree[index].ub||tree[index].key<tree[index].lb) return false;

  if(leftExist && !IsBinarySearchTree(tree,left)){
    return false;
  }
  if(rightExist && !IsBinarySearchTree(tree,right)){
    return false;
  }

  return true;
  

}

int main() {
  int nodes;
  cin >> nodes;

  if(nodes==0){
    cout << "CORRECT" << endl;
    return 0;
  }

  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    long long key;
    int left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree,0)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
