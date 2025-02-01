# include <iostream>
# include <vector>
 using namespace std;

 // Floyd Warshall Algorithm
 // find the shortest path between all pairs of vertices in a weighted graph
 // dist[k][i][j] = min(dist[k-1][i][j], dist[k-1][i][k] + dist[k-1][k][j])
 // however, it costs too much space, so we can use two arrays to iterate
 // dist_now[i][j] = min(dist_pre[i][j], dist_pre[i][k] + dist_pre[k][j])

 const int INF = 0x3f3f3f3f;

vector<vector<int>> dist_now(301, vector<int>(301, 0));
vector<vector<int>> dist_pre(301, vector<int>(301, 0));

int main(){
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n;i++){
        for (int j = 1; j <= n;j++){// Initialize the distance
            dist_pre[i][j] = INF;
        }
        dist_pre[i][i] = 0;
    }
    for (int i = 0; i < m;i++){// Initialize the graph
        int u, v, w;
        cin >> u >> v >> w;
        dist_pre[u][v] = w;
    }
    for (int k = 1; k <= n;k++){// Floyd Warshall Algorithm
        for (int i = 1; i <= n;i++){
            for (int j = 1; j <= n;j++){
                dist_now[i][j] = min(dist_pre[i][j], dist_pre[i][k] + dist_pre[k][j]);
            }
        }
        dist_pre = dist_now;
    }

    for (int i = 1; i <= n;i++){
        for (int j = 1; j <= n;j++){
            if(dist_now[i][j]==INF)
                cout << "INF ";
            else
                cout << dist_now[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}