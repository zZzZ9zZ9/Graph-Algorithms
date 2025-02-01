#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// Dijkstra algorithm
// No negative edge, no negative cycle

vector<pair<int, int>> adj[1001];// Adjacency list, first is the adjacent vertex, second is the weight
int dist[1001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
// Min heap, first is the distance, second is the vertex
// sort by the distance

int main(){
    int n, m;
    cin >> n >> m;
    int s, t;
    cin >> s >> t;
    for (int i = 0; i < m;i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;// Initialize

    pq.push({0, s});// Start from vertex s
    while(!pq.empty()){// Dijkstra algorithm
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if(d > dist[u]){
            continue;// Skip the outdated data
        }
        for(auto e: adj[u]){
            int v = e.first;
            int w = e.second;
            if(dist[v] > dist[u] + w){// Relax
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    cout << dist[t] << endl;
    return 0;
}

/* input sample:
5 6
1 4
1 2 2
1 3 1
3 2 1
2 4 2
2 5 1
5 4 1
*/
/* output sample:
4
*/