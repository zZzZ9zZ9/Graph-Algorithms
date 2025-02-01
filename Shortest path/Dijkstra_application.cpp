#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Dijkstra algorithm
// No negative edge, no negative cycle
// calculate the number of shortest paths from s to t

vector<pair<int, int>> adj[100001];// Adjacency list, first is the adjacent vertex, second is the weight
long long int dist[100001];
long long int cnt[100001] = {0};

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

    for (int i = 1; i <= n;i++){
        dist[i] = 0x3f3f3f3f;
    }
    dist[s] = 0;// Initialize
    cnt[s] = 1;

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
                cnt[v] = cnt[u];
            }
            else if(dist[v] == dist[u] + w){
                cnt[v] += cnt[u]; // Accumulate the number of shortest paths, there is no repeated calculation
            }
        }
    }
    cout << cnt[t] << endl;
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