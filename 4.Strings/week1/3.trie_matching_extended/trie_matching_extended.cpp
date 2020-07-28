#include <bits/stdc++.h>
using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}


vector<Node> construct_trie(const vector <string>& patterns){
	Node root;
	vector<Node> trie;
	trie.push_back(root);
	for(string pattern:patterns){
		int current_node=0;
		for(int i=0;i<pattern.length();i++){
			int current_sym=letterToIndex(pattern[i]);
			int ind=trie[current_node].next[current_sym];
			if(ind!=NA){
				current_node=ind;
			}
			else{
				trie[current_node].next[current_sym]=trie.size();
				Node n;
				trie.push_back(n);
				current_node=trie.size()-1;
			}
			if(i==pattern.length()-1) trie[current_node].patternEnd=true;
		}
	}
	return trie;
}

int prefix_trie_matching(char* text, vector<Node> &trie, int l){

	char c= * text;
	int sym=letterToIndex(c);
	int index=1;
	Node v=trie[0];
	while(true){
		if(v.patternEnd){
			return 1;
		}
		else if(sym!=-1&&v.next[sym]!=NA){
			int next=v.next[sym];
			if(index>=l) sym=-1;
			else sym=letterToIndex(*(text+index));
			index++;
			v=trie[next];
		}
		else{
			return -1;
		}
	}
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	char * p=new char[text.length()+1];
    strcpy(p,text.c_str());
	vector <int> result;
	vector<Node> trie= construct_trie(patterns);
	int i=0;
	while(i<text.length()){
		int res=prefix_trie_matching(p+i, trie,text.length()-i);
		if(res==1){
			result.push_back(i);
		}
		i++;
	}

	return result;
}


int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
