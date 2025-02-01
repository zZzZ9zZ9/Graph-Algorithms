#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// adjacency matrix
int adj[30][30] = {0};
vector<int> arr;
int n = 6;

// Depth First Search
// use stack/recursive to achieve first in, last out
int visit[30] = {0};
// void DFS(int s){
//     visit[s] = 1;
//     Preprocesss(u);

//     for(v adjacent with u){
//         if(visit[v]==0)
//             DFS(v);
//         Inprocess(u, v);
//     }
//     Postprocess(u);
// }
// Pre-order DFS
void Pre_order_DFS(int s){
    visit[s] = 1;
    arr.push_back(s);
    // it is the sequence how to push the node in arr, which can also represent the operation using pre order DFS
    for (int i = 1; i <= n;i++){
        if(adj[s][i]!=0 && visit[i]==0){
            Pre_order_DFS(i);
        }
    }
}
// Post-order DFS
void Post_order_DFS(int s){
    visit[s] = 1;
    for (int i = 1; i <= n;i++){
        if(adj[s][i]!=0 && visit[i]==0){
            Post_order_DFS(i);
        }
    }
    arr.push_back(s);
    // it is the sequence how to push the node in arr, which can also represent the operation using post order DFS
}
// In order DFS: there is also an algorithm for In-order DFS, but it is up to the definition

// – Tree edges (树边) are edge (u,v) that 𝑣’s first visit is
// through this edge, 𝑢 is 𝑣’s parent in the tree
// – Back edges (反向边) are those edges (u,v) in which
// 𝑣 is an ancestor of 𝑢 in a depth-first tree
// – Forward edges (前向边) are those edges (u,v) such
// that 𝑣 is a descendant of 𝑢 in a depth-first tree
// – Cross edges (交叉边) are all other edges

// Properties
// Thm1: 
// Vertex 𝑢𝑢’s ancestors in depth-first tree are the vertices in the search stack when visiting u
// Thm2:
// In undirected graphs, every edge is either a tree edge or a back edge

int main(){
    adj[1][2] = 1;
    adj[2][3] = 1;
    adj[1][4] = 1;
    adj[2][5] = 1;
    adj[5][6] = 1;
    adj[4][5] = 1;

    memset(visit, 0, sizeof(visit));
    Pre_order_DFS(1);
    for (int i = 0; i < n;i++){
        cout << arr[i] << ' ';
    }
    cout << endl;

    arr.clear();
    memset(visit, 0, sizeof(visit));
    Post_order_DFS(1);
    for (int i = 0; i < n;i++){
        cout << arr[i] << ' ';
    }
}