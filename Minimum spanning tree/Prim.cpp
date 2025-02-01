#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Minimum Spanning Tree
// there are two algorithms to find the minimum spanning tree: Prim and Kruskal
// Prim is based on the priority queue, while Kruskal is based on the union-find set


// Prim algorithm
vector<pair<int, int>> adj[100001];// adjacency list, pair.first is the vertex, pair.second is the weight

int main(){
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m;i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});// undirected graph
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // priority queue, pair.first is the weight, pair.second is the vertex
    // the priority is based on the weight, so the top element is the smallest weight
    vector<bool> visited(n + 1, false);// visited[i] is true if vertex i is visited
    pq.push({0, 1});// start from vertex 1
    int cost = 0;
    while(!pq.empty()){
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();
        if(visited[u]){
            continue;
        }
        visited[u] = true;
        cost += w;
        for(auto p:adj[u]){
            int v = p.first;
            int weight = p.second;
            if(!visited[v]){
                pq.push({weight, v});
            }
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