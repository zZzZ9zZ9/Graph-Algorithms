#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// union-find set
// Given an undirected graph with n nodes, m edges, calculate the number of connected components
int parent[100001];
int capacity[100001];
void Initialize(int n){
    for (int i = 1; i <= n;i++){
        parent[i] = i;// initialize the parent of each node as itself
        capacity[i] = 1;// initialize the capacity of each set as 1
    }
}
int find_root(int a){
    int t = a;
    while(parent[a]!=a){// find the root
        a = parent[a];
    }
    parent[t] = a;// path compression
    return a;
}

// Given an undirected weighted graph, here is q query, each query is (x,c)
// calculate how many nodes can be reached from x with the limit weight c of the edge
struct edge{
    int u, v;
    int w;
};
edge edges[500001];

struct query{
    int x, c;
    int index;
    int result;
};
query queries[500001];

int main(){
    int n, m, q;
    cin >> n >> m >> q;
    Initialize(n);
    for (int i = 0; i < m;i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    for (int i = 0; i < q; i++){
        cin >> queries[i].x >> queries[i].c;
        queries[i].index = i;
    }
    sort(edges, edges + m, [](edge a, edge b) { return a.w < b.w; });
    sort(queries, queries + q, [](query a, query b) { return a.c < b.c; });
    int j = 0;
    for (int i = 0; i < q; i++){// for each query
        while(j < m && edges[j].w<=queries[i].c){// add edges whose weight is less than or equal to c
            int root_u = find_root(edges[j].u);
            int root_v = find_root(edges[j].v);
            parent[root_v] = root_u;
            parent[edges[j].v] = root_u;
            if(root_u != root_v)
                capacity[root_u] += capacity[root_v];
            j++;
        }
        queries[i].result = capacity[find_root(queries[i].x)];
    }
    sort(queries, queries + q, [](query a, query b){ return a.index < b.index; });
    for (int i = 0; i < q; i++){
        cout << queries[i].result << endl;
    }
    return 0;
}

/*input sample:
5 8 3
1 2 6
1 3 3
3 4 3
1 5 10
4 2 7
4 1 9
2 1 9
2 5 6
4 10
1 2
4 4
*/
/*output sample:
5
1
3
*/