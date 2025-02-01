#include <iostream>
#include <vector>

using namespace std;

// Bellman-Ford algorithm
// No negative cycle, but negative edge is allowed
// calculate the number of shortest paths from s to t

struct edge{
    int u, v, w;
};
edge edges[1001];
long long int dist[1001];
long long int cnt[1001] = {0};// cnt[u] means the number of shortest paths from s to u
long long int part[1001][1001] = {0};
// part[u][v] means the value cnt[u] accumulates to cnt[v] through edge(u,v,w)
// aoid repeated calculation

int n, m;

bool relax(int u,int v,int w){
    if(dist[v] > dist[u] + w){
        dist[v] = dist[u] + w;
        cnt[v] = cnt[u];
        for(int i = 1; i <= n; i++){
            part[i][v] = 0;
        }
        part[u][v] = cnt[u];
        return true;
    }
    else if(dist[v] == dist[u] + w){
        cnt[v] = cnt[v] + cnt[u] - part[u][v];
        part[u][v] = cnt[u];
    }
    // else if(dist[v] < dist[u] + w){
    //     // do nothing
    // }
    return false;
}

int main(){
    cin >> n >> m;
    int s, t;
    cin >> s >> t;
    for (int i = 0; i < m;i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    for (int i = 1; i <= n;i++){
        dist[i] = 0x3f3f3f3f;
    }
    dist[s] = 0;// Initialize
    cnt[s] = 1;
    for (int i = 0; i < n - 1; i++){// Bellman-Ford algorithm
        for (auto e: edges){
            relax(e.u, e.v, e.w);
        }
    }
    cout << cnt[t] << endl;
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
2
*/