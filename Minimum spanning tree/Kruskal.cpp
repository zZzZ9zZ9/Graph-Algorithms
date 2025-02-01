#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Minimum Spanning Tree
// there are two algorithms to find the minimum spanning tree: Prim and Kruskal
// Prim is based on the priority queue, while Kruskal is based on the union-find set
// Dense graph: Prim is faster; Sparse graph: Kruskal is faster
// If you are familiar with the union-find set, I think Kruckal is easier to implement

// Kruskal algorithm
struct Edge {
    int u, v, w;
};

Edge edges[100001];
int parent[100001];

int find_root(int a){
    int t = a;
    while(parent[a]!=a){
        a = parent[a];
    }
    parent[t] = a;// path compression
    return a;
}

int main(){
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m;i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    sort(edges, edges + m, [](Edge a, Edge b) {return a.w < b.w; });// sort the edges by weight
    for (int i = 1; i <= n;i++){// initialize the union-find set
        parent[i] = i;
    }
    int cost = 0;
    for (int i = 0; i < m;i++){
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        int root_u = find_root(u);
        int root_v = find_root(v);
        if(root_u!=root_v){
            parent[root_u] = root_v;
            parent[u] = root_v;// path compression
            cost += w;
        }
    }
    cout << cost;
    return 0;
}

/*input sample:
5 7
1 2 1
1 3 1
2 4 2
2 5 4
3 4 2
3 5 3
4 5 3
*/
/*output sample:
7
*/