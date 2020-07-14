#include <bits/stdc++.h>
using namespace std;
// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
  char key;
  string s;
  Vertex* left;
  Vertex* right;
  Vertex* parent;

  Vertex(char key, string s, Vertex* left, Vertex* right, Vertex* parent) 
  : key(key), s(s), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
  if (v == NULL) return;
  v->s =(v->left != NULL ? v->left->s :"")+v->key + (v->right != NULL ? v->right->s : "");
  if (v->left != NULL) {
    v->left->parent = v;
  }
  if (v->right != NULL) {
    v->right->parent = v;
  }
}

void small_rotation(Vertex* v) {
  Vertex* parent = v->parent;
  if (parent == NULL) {
    return;
  }
  Vertex* grandparent = v->parent->parent;
  if (parent->left == v) {
    Vertex* m = v->right;
    v->right = parent;
    parent->left = m;
  } else {
    Vertex* m = v->left;
    v->left = parent;
    parent->right = m;
  }
  update(parent);
  update(v);
  v->parent = grandparent;
  if (grandparent != NULL) {
    if (grandparent->left == parent) {
      grandparent->left = v;
    } else {
      grandparent->right = v;
    }
  }
}

void big_rotation(Vertex* v) {
  if (v->parent->left == v && v->parent->parent->left == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else {
    // Zig-zag
    small_rotation(v);
    small_rotation(v);
  }  
}

void splay(Vertex*& root, Vertex* v) {
  if (v == NULL) return;
  while (v->parent != NULL) {
    if (v->parent->parent == NULL) {
      small_rotation(v);
      break;
    }
    big_rotation(v);
  }
  root = v;
}

Vertex * getElement(Vertex* r,int index){
	int x= r->left==NULL?-1:r->left->s.length()-1;
	if (index==x+1) return r;
	else if (index<x+1) return getElement(r->left,index);
	else return getElement(r->right, index-x-2);
}

void split(Vertex* root, int index, Vertex*& left, Vertex*& right) {
  right = getElement(root, index);
  splay(root, right);
  if (right == NULL) {
    left = root;
    return;
  }
  left = right->left;
  right->left = NULL;
  if (left != NULL) {
    left->parent = NULL;
  }
  update(left);
  update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
  if (left == NULL) return right;
  if (right == NULL) return left;
  Vertex* min_right = right;
  while (min_right->left != NULL) {
    min_right = min_right->left;
  }
  splay(right, min_right);
  right->left = left;
  update(right);
  return right;
}



Vertex* root = NULL;

Vertex* bt(string s, int first, int last){
	if (first > last)
		return NULL;
	int mid = (first + last) / 2;
	Vertex* root = new Vertex(s[mid],"",NULL,NULL,NULL);
	
	root->left = bt(s, first, mid - 1);
	if(root->left!=NULL) root->left->parent=root;
	root->right = bt(s, mid + 1, last);
	if(root->right!=NULL) root->right->parent=root;
	update (root);
	return root;
}
void process_str(int i, int j, int k){
	Vertex* l1=NULL;
	Vertex* r1 = NULL;
	split(root,i,l1,r1);
	Vertex* str= NULL;
	Vertex* r2 = NULL;
	if(j+1-i<r1->s.length()) split(r1, j+1-i, str, r2);
	else str=r1;
	root=merge(l1,r2);
	string remaining_string=root==NULL?"":root->s;
	if(k==remaining_string.length()){
		root=merge(root, str);
	}
	else{
		Vertex* left =NULL;
		Vertex* right = NULL;
		split(root,k, left, right);
		root=merge(merge(left,str),right);
	} 
	return;
}

string process_slow( int i, int j, int k, string s ) {
	// Replace this code with a faster implementation
	string t = s.substr(0, i) + s.substr(j + 1);
	return t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
}
int main() {
	ios_base::sync_with_stdio(0);
	//string s;
	// cin >> s;
	// root=bt(s,0,s.length()-1);
	// int actions;
	// cin >> actions;
	// for (int action_index = 0; action_index < actions; ++action_index) {
	// 	int i, j, k;
	// 	cin >> i >> j >> k;
	// 	process_str(i, j, k);
	// }
	// cout << root->s << endl;
	string s="";
	
	for(int i=0;i<10000;i++){
		char c= (rand()%26)+97;
		s+=c;
	}
	cout<<"-------------------"<<s<<"----------------------\n";
	root=bt(s,0,s.length()-1);

	clock_t t=clock();
	int cnt=0;
	while(cnt<100000){
		string test=root->s;
		int n=test.length();
		int i=rand()% n;
		int j=rand()%(n-i) + i;
		int k=rand()%(n-j+i);
		cout<<"i="<<i<<" j="<<j<<" k="<<k<<'\n';
		process_str(i, j, k);
		string res=root->s;
		//string st=process_slow(i,j,k,test);
		// cout<<'\n'<<root->s<<"   "<<st;
		// if(res==st){
		//  	cout<<" ---> OK\n";
		// }
		// else{
		//  	cout<<" ---> WRONG ANSWER\n";
		//  	cout<<"		expected = "<<st<<'\n';
		//  	cout<<"		your o/p = "<<res<<'\n';
		//  	break;
		// }
		cnt++;
	}
	t=clock()-t;
	cout<<"took "<<(float)t/CLOCKS_PER_SEC<<" secs\n";

}
