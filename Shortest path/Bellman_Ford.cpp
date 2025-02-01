#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// Bellman-Ford algorithm
// No negative cycle, but negative edge is allowed
struct edge{
    int u, v, w;
};
edge edges[10001];
int dist[1001];
bool relax(int u,int v,int w){
    if(dist[v] > dist[u]+w){
        dist[v] = dist[u] + w;
        return true;
    }
    return false;
}

int main(){
    int n, m;
    cin >> n >> m;
    int s, t;
    cin >> s >> t;
    for (int i = 0; i < m;i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;// Initialize
    for (int i = 0; i < n - 1; i++){// Bellman-Ford algorithm
        for (auto e: edges){
            relax(e.u, e.v, e.w);
        }
    }
    // int k;
    // for (int i = 0; i < k; i++){// Bellman-Ford algorithm, k is the limited maximum number of edges in the shortest path
    //     for (int j = 0; j < m;j++){
    //         relax(edges[j].u, edges[j].v, edges[j].w);
    //     }
    // }
    
    for(auto e:edges){
        if(relax(e.u,e.v,e.w)){
            cout << "Negative cycle exists!" << endl;
            return 0;
        }
    }
    cout << dist[t] << endl;
    return 0;
}

/*input sample:
5 6
1 4
1 2 2
1 3 3
3 2 -2
2 4 2
2 5 1
5 4 1
*/
/*output sample:
3
*/