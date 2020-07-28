#include <bits/stdc++.h>
using namespace std;

struct subStr
{
    int st_index;
    int len;
    int pos;
};
struct Node
{
    int parent = -1;
    bool isLeaf = false;
    int type = -1;
    int height = 0;
    subStr s; // 0 -> xy, 1->x, 2->y
};
typedef map<char, subStr> edges;
typedef vector<edges> tree;
typedef queue<pair<int, subStr>> Queue;
int l1 = 0, l2 = 0;

tree ComputeSuffixTreeEdges(const string &text, vector<Node> &nodes)
{
    vector<string> result;
    tree t;
    int l = text.length();
    edges starting_map;
    t.push_back(starting_map);
    nodes.push_back(Node{-1,false,-1,0,subStr{0,0,0}});
    int node_cnt = 1;
    for (int i = 0; i < l; i++)
    {
        bool flag = false;
        int starting_index = i;
        int current_node = 0;
        char curr_sym = text[starting_index];
        auto itr = t[current_node].find(curr_sym);

        if (itr != t[current_node].end())
        {
            int cnt = 0;
            while (starting_index + cnt <= l)
            {
                if (cnt >= itr->second.len)
                {
                    starting_index = starting_index + cnt;
                    curr_sym = text[starting_index];
                    int pos = itr->second.pos;
                    itr = t[pos].find(curr_sym);
                    if (itr == t[pos].end())
                    {
                        t[pos].insert(make_pair(curr_sym, subStr{starting_index, l - starting_index, node_cnt}));
                        edges e;
                        t.push_back(e);
                        nodes.push_back(Node{pos,false,-1,0,subStr{starting_index, l - starting_index, node_cnt}});
                        node_cnt++;
                        flag = true;
                        break;
                    }
                    cnt = 0;
                }
                if (text[starting_index + cnt] == text[itr->second.st_index + cnt])
                    cnt++;
                else
                    break;
            }
            if (!flag)
            {
                int oldNode = itr->second.pos;
                int new_node1 = node_cnt;
                int new_node2 = node_cnt + 1;
                int old_len = itr->second.len;
                itr->second.pos = new_node1;
                itr->second.len = cnt;

                //making place for 2 new nodes
                edges edges1;
                t.push_back(edges1);
                edges edges2;
                t.push_back(edges2);

                //new node1 to new node2
                subStr e1 = subStr{starting_index + cnt, l - starting_index - cnt, new_node2};
                t[new_node1].insert(make_pair(text[starting_index + cnt], e1));

                //new node1 to old node
                subStr e2 = subStr{itr->second.st_index + cnt, old_len - cnt, oldNode};
                t[new_node1].insert(make_pair(text[itr->second.st_index + cnt], e2));

                nodes.push_back(Node{nodes[oldNode].parent,false,-1,0,itr->second});
                nodes[oldNode].parent=new_node1;
                nodes[oldNode].s=e2;
                nodes.push_back(Node{new_node1,false,-1,0,e1});

                //total 2 new nodes
                node_cnt = node_cnt + 2;
            }
        }
        else
        {
            t[current_node].insert(make_pair(curr_sym, subStr{starting_index, l - starting_index, node_cnt}));
            nodes.push_back(Node{current_node,false,-1,0,subStr{starting_index, l - starting_index, node_cnt}});
            edges e;
            t.push_back(e);
            node_cnt++;
        }
    }
    return t;
}

void set_type(vector<Node> &nodes, tree t){
    for(int i=0;i<nodes.size();i++){
        if(nodes[i].isLeaf){
            int type=nodes[i].type;
            int parent=nodes[i].parent;
            
            while(nodes[parent].type!=0&&parent!=-1){
                if(nodes[parent].type==-1){
                    nodes[parent].type=type;
                    parent=nodes[parent].parent;
                    continue;
                }
                if(type==0) nodes[parent].type=0;
                else if (type == 1 && nodes[parent].type==2 || type == 2 && nodes[parent].type == 1){
                    nodes[parent].type=0;
                }
                else if (type==nodes[parent].type) break;
                parent=nodes[parent].parent;
            }

        }
    }
}

void generalise_edges(tree &t, vector<Node> &nodes)
{
    
    for (int i = 0; i < t.size(); ++i)
    {
        if (t[i].empty())
        {
            nodes[i].type = nodes[i].s.st_index<=l1?1:2;
            nodes[i].isLeaf = true;
        }
        int type=-1;
        for (auto &j : t[i])
        {
            nodes[j.second.pos].parent = i;
            if (j.second.st_index <= l1 && j.second.st_index + j.second.len > l1)
            {
                j.second.len = j.second.len - (l2 + 1);
            }
            nodes[j.second.pos].s = j.second;
        }
    }
}

void bfs(vector<Node> &nodes, const tree &t, string &r, string str)
{

    Node n;
    int min_len = str.length();
    vector<bool> v(nodes.size());
    queue<subStr> q;
    q.push(subStr{0, 0, 0});
    v[0] = true;
    while (!q.empty())
    {
        subStr u = q.front();
        // cout<<"popping "<<u.st_index<<" "<<u.len<<"\n\n";
        q.pop();
        for (auto &j : t[u.pos])
        {
            // cout<<"for edge "<<j.second.st_index<<", "<<j.second.len<<'\n';
            nodes[j.second.pos].height = nodes[u.pos].height + j.second.len;
            if (!v[j.second.pos])
            {
                v[j.second.pos] = true;
                if (nodes[j.second.pos].type == 0)
                {
                    // cout<<"   type = 0 -> pushing to queue\n";
                    q.push(j.second);
                }
                else if (nodes[j.second.pos].type == 1 && j.second.st_index < l1)
                {
                    /** this is the node... u have to break from here and
            * by now u must have the resultant string from root till this node
          **/
                    // cout<<"   type = 1 and st_ind < l1 \n";
                    if ((nodes[j.second.pos].height - nodes[j.second.pos].s.len + 1) < min_len)
                    {
                        // cout<<"   potential node -> "<<nodes[j.second.pos].height<<" "<<nodes[j.second.pos].s.len<<" -> "<<min_len<<'\n';
                        min_len = nodes[j.second.pos].height - nodes[j.second.pos].s.len + 1;
                        n = nodes[j.second.pos];
                    }
                    break;
                }
            }
        }
    }
    n.s.len = 1;
    while (n.parent != -1)
    {
        r = str.substr(n.s.st_index, n.s.len) + r;
        n = nodes[n.parent];
    }
}

string solve(string p, string q)
{

    string result = "";
    string str = p + '#' + q + '$';
    l1 = p.length();
    l2 = q.length();

    vector<Node> nodes;
    //build a Generalised Suffix Tree and set s and parent of all nodes
    tree t = ComputeSuffixTreeEdges(str,nodes);

    // trim extra parts of edge labels and set nodes leaf and types of leafs
    generalise_edges(t, nodes);
    //set internal nodes types
    set_type(nodes, t);

    // do a BFS to find first node with type 1 -> path from root to that node is the result
    bfs(nodes, t, result, str);

    return result;
}

int main(void)
{
    string p;
    cin >> p;
    string q;
    cin >> q;

    // clock_t t=clock();
    string ans = solve(p, q);
    // t=clock()-t;
    cout << ans << endl;
    // cout<<" in "<<(float) (t*1.0)/CLOCKS_PER_SEC<<'\n';

    return 0;
}
