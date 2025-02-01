#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// adjacency matrix
int adj[30][30] = {0};
vector<int> BFS_order;
int n = 6;

// Breadth First Search
// BFS can also be used to calculate the shortest path
// which requres the weight of the edge to be 1（unweighted graph）
// properties:
// if u is pushed earlier than v, then d[u]<d[v]
void BFS(int s){
    // use queue to achieve first in, first out
    queue<int> q;
    q.push(s);
    int visit[30] = {0};
    visit[s] = 1;

    while(!q.empty()){
        int t = q.front();
        q.pop();
        BFS_order.push_back(t);
        // search next node
        for (int i = 1; i <= n;i++){
            if(adj[t][i]!=0&&visit[i]==0){
                q.push(i);
                visit[i] = 1;
            }
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
    BFS(1);
    for (int i = 0; i < n;i++){
        cout << BFS_order[i] << ' ';
    }
}