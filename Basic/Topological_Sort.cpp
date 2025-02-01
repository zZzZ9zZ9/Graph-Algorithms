# include <iostream>
# include <vector>
# include <queue>

using namespace std;

int adj[30][30] = {0};
vector<int> topo_order;
int n = 6;

// Topological ordering: 
// Given a directed acyclic graph (DAG)
// a linear ordering of vertices such that for every directed edge uv from vertex u to vertex v, 
// u comes before v in the ordering
// Topological ordering is not unique, a graph can have multiple topological orderings
// Idea:
// 1. Find a vertex with no incoming edges
// 2. Output the vertex
// 3. Remove the vertex and all its outgoing edges
// 4. Repeat until all vertices are removed
void topo_sort(){
    int in_degree[30] = {0};
    for (int i = 1; i <= n;i++){
        for (int j = 1; j <= n;j++){
            if(adj[i][j]!=0){
                in_degree[j]++;// calculate the in-degree of each vertex
            }
        }
    }
    queue<int> q;// use queue to store the vertex with in-degree 0
    for(int i = 1; i <= n;i++){
        if(in_degree[i]==0){
            q.push(i);// push the vertex with in-degree 0 into the queue
        }
    }
    while(!q.empty()){
        int t = q.front();
        q.pop();
        topo_order.push_back(t);
        for (int i = 1; i <= n;i++){
            if(adj[t][i]!=0){
                in_degree[i]--;// remove the vertex and all its outgoing edges
                if(in_degree[i]==0){
                    q.push(i);
                }
            }
        }
    }
}

// DFS-based implementation:
// calculate the reverse topological ordering
// recursively visit the vertex with no outgoing edges
int visit[30] = {0};
void DFS(int s){
    visit[s] = 1;
    for (int i = 1; i <= n;i++){
        if(adj[s][i]!=0 && !visit[i]){
            DFS(i);
        }
    }
    topo_order.push_back(s);// post-order traversal
}
void topo_sort_dfs(){// calculate the reverse topological ordering
    for (int i = 1; i <= n;i++){
        if(!visit[i]){
            DFS(i);
        }
    }
}

int main(){
    adj[1][2] = 1;
    adj[2][3] = 1;
    adj[1][4] = 1;
    adj[2][5] = 1;
    adj[5][6] = 1;
    adj[4][5] = 1;
    topo_sort();
    int size = topo_order.size();
    for (int i = 0;i < size;i++){
        cout << topo_order[i] << ' ';// output the topological order
    }
    cout << endl;
    topo_order.clear();
    topo_sort_dfs();
    size = topo_order.size();
    for (int i = 0;i < size;i++){
        cout << topo_order[i] << ' ';// output the reverse topological order
    }
    return 0;
}