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
	int x= r->left==NULL?-1:r->left->length-1;
	while (index!=x+1){
        if(index<x+1){
            r=r->left;
        }
        else{
            r=r->right;
            index=index-x-2;
        }
        x= r->left==NULL?-1:r->left->length-1;
    }
    return r;
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


void insert(char x) {
  Vertex* left = NULL;
  Vertex* right = NULL;
  Vertex* new_vertex = new Vertex(x,"", NULL, NULL, NULL);
  if(root==NULL) {
		root=new_vertex;
		update(root);
		return;
  }
  root = merge(root, new_vertex);
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

int main() {
	ios_base::sync_with_stdio(0);
	string s;
	cin >> s;
	for(int i=0;i<s.length();i++){
		insert(s[i]);
	}
	
	int actions;
	cin >> actions;
	for (int action_index = 0; action_index < actions; ++action_index) {
		int i, j, k;
		cin >> i >> j >> k;
		process_str(i, j, k);
	}
	cout << root->s << endl;
}
