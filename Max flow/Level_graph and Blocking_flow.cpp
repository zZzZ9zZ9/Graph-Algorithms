#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// Given a residual network
// establish a level graph from s
// find the blocking flow from s to t.

int c[1001][1001] = { 0 };// Capacity of the residual network
int Flow[1001][1001] = { 0 };// Flow of the residual network
int level[1001];// level graph

vector<int> used(1001, 1);

int n, m, s, t;

void BFS(int s){
    queue<int> q;
    q.push(s);

	memset(level, -1, sizeof(level));
	level[s] = 0;

    while(!q.empty()){
        int temp = q.front();
        q.pop();
        for (int i = 1; i <= n; i++){
            if(c[temp][i] != 0 && level[i] < 0){
                q.push(i);
				level[i] = level[temp] + 1;
			}
        }
    }
}

int DFS(int a, int b, int limit) {// DFS flow f from a to b with the limit of flow f
	if (a == b)
		return limit;
	for (int& i = used[a]; i <= n; i++) {// used[a] is the next node to be searched, avoid repeated search
		if (c[a][i] > 0 && level[i] == level[a] + 1) {
			int flow = DFS(i, b, min(limit, c[a][i]));
			if(flow > 0){
				c[a][i] -= flow;
				c[i][a] += flow;
				Flow[a][i] += flow;
				return flow;
			}
		}
	}
	return 0;
}

int blockingFlow() {
	int V = 0;
	int T = 0;
	while (1) {
		T = DFS(s, t, 0x3f3f3f3f);// optimal DFS
		if (T <= 0)
			break;
		V += T;
	}
	return V;
}

int main() {
	cin >> n >> m;
	cin >> s >> t;
	for (int i = 0; i < m; i++) {
		int u, v, ct;
		cin >> u >> v >> ct;
		c[u][v] += ct;
	}

	BFS(s);

	// only when c[u][v]>0 && level[v]==level[v]+1,the edge from u to v exits

	int total_flow = blockingFlow();
	cout << total_flow << endl;
	return 0;
}
