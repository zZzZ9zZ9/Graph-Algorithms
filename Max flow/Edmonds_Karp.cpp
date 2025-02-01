#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// Edmonds-Karp algorithm

int cap[201][201] = { 0 };
// in fact, we don't need to use capacity matrix, the initial capacity is not important
// we can directy use residual network to iteratively find the augmenting path
// but we use capacity matrix here to make the code more readable which is same as the pseudocode
// if you don't want to code the build_res() function
// you can directly update residual network like the Dinic.cpp file
int res[201][201] = { 0 };
int flow[201][201] = { 0 };

int n, m;

void build_res() {// build residual network
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			res[i][j] = cap[i][j] + flow[j][i];
		}
	}
}

int update(int parent[], int t) {// update the flow
	int limit = 0x3f3f3f3f;
	int u = parent[t];
	int v = t;
	while (u != -1) {
		limit = min(limit, res[u][v]);
		v = u;
		u = parent[u];
	}
	u = parent[t];
	v = t;
	while (u != -1) {
		flow[u][v] += limit;
		flow[v][u] = -flow[u][v];
		v = u;
		u = parent[u];
	}
	return limit;
}

int BFS(int s, int t) {
	queue<int> Q;
	Q.push(s);
	int parent[201] = { 0 };
	parent[s] = -1;
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		for (int i = 1; i <= n; i++) {
			if (res[v][i] > 0 && parent[i] == 0) {
				Q.push(i);
				parent[i] = v;
				if (i == t) {
					return update(parent, t);
				}
			}
		}
	}
	return 0;
}

long long int Edmonds_Karp(int s, int t) {
	long long int f = 0;
	while (1) {
		build_res();
		int k = BFS(s, t);// find the shortest path as the augmenting path
		if (k <= 0)
			return f;
		f += k;
	}
}

int main() {
    cin >> n >> m;
    memset(cap, 0, sizeof(cap));
    memset(flow, 0, sizeof(flow));
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        cap[u][v] += w;
	}

    long long int f = Edmonds_Karp(1, n);// s = 1, t = n
    cout << f << endl;
	return 0;
}

/* input sample:
4 5
1 2 40
1 4 20
2 4 20
2 3 30
3 4 10
*/
/* output sample:
50
*/