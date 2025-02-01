#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int MAX = 1000001;

// Given a directed graph, and a starting node
// find the maximum number of nodes that can be reached from the starting node in a single move

// Strongly connected components
vector<int> adj[MAX];// adjacency list
vector<int> adj_inv[MAX];// adjacency list of the inverse graph
vector<vector<int>> scc;// strongly connected components
vector<int> post_order;// DFS_post_order of the initial graph
vector<int> temp_scc;// temporary vector to store the current SCC
vector<int> scc_index(MAX);// index of the SCC of each node
bool visited[MAX];// visited nodes

void DFS1(int s){// DFS on the initial graph
    visited[s] = true;
    for (int i = 0; i < adj[s].size(); i++){
        if(!visited[adj[s][i]]){
            DFS1(adj[s][i]);
        }
    }
    post_order.push_back(s);
}
void DFS2(int s){// DFS on the inverse graph
    visited[s] = true;
    temp_scc.push_back(s);// store the current SCC, any order is fine
    for (int i = 0; i < adj_inv[s].size(); i++){
        if(!visited[adj_inv[s][i]]){
            DFS2(adj_inv[s][i]);
        }
    }
}

vector<int> maxnumber(MAX, 0); 
// store the maximum number of nodes which can be reached from each SCC
// in order to avoid recalculating the same value
int max_nodes(int st){// recursive function
    if(maxnumber[st] != 0){
        return maxnumber[st];// if the value is already calculated, return it
    }
    int maximum = 0;
    for (int i = 0;i < scc[st].size(); i++){
        int u = scc[st][i];
        for (int j = 0; j < adj[u].size(); j++){
            int v = adj[u][j];
            if(scc_index[v] != st){
                maximum = max(maximum, max_nodes(scc_index[v]));
            }
        }
    }
    maxnumber[st] = scc[st].size() + maximum;
    return maxnumber[st];
}

int main(){
    int n, m;
    cin >> n >> m;
    int start;
    cin >> start;
    for (int i = 0; i < m;i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj_inv[v].push_back(u);
    }
    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= n; i++){
        if(!visited[i]){
            DFS1(i);// calculate the post_order in the initial graph
        }
    }
    memset(visited, false, sizeof(visited));
    for (int i = post_order.size() - 1; i >= 0; i--){
        if(!visited[post_order[i]]){
            vector<int>().swap(temp_scc);// clear the temporary vector
            DFS2(post_order[i]);
            scc.push_back(temp_scc);// store the current SCC
            for (int j = 0; j < temp_scc.size(); j++){
                scc_index[temp_scc[j]] = scc.size() - 1;// store the index of the SCC of each node
            }
        }
    }
    cout << max_nodes(scc_index[start]);
    return 0;
}

/*input sample:
6 7
1
1 2
2 3
1 4
3 1
4 5
5 6
6 4
*/
/*output sample:
6
*/