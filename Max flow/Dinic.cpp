#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// Dinic algorithm
// Generally, Dinic algorithm is faster than Edmonds-Karp algorithm
// because the number of edges is often much larger than the number of vertices

const int INF = 0x3f3f3f3f;
const int MAX = 403;

int cap[MAX][MAX] = { 0 };// we use the cap martix to represent the residual network
int level[MAX] = { 0 };

int n, m;

void BFS(int s) {
	memset(level, -1, sizeof(level));
	queue<int> Q;
	Q.push(s);
	level[s] = 0;

	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();

		for (int i = 1; i <= n; i++) {
			if (cap[v][i] > 0 && level[i] < 0) {
				Q.push(i);
				level[i] = level[v] + 1;
			}
		}
	}
}

vector<int> used(MAX, 1);

long long DFS(int s, int t, int limit) {
	if (s == t)
		return limit;
	for (int& i = used[s]; i <= n; i++) {

		if (cap[s][i] > 0 && (level[i] == level[s] + 1)) {
			int f_limit = DFS(i, t, min(cap[s][i], limit));
			if (f_limit > 0) {
				cap[s][i] -= f_limit;
				cap[i][s] += f_limit;
				return f_limit;
			}
		}
	}
	return 0;
}

long long int Dinic(int s, int t) {
	long long f = 0;
	while (1) {
		BFS(s);
		if (level[t] < 0)
			return f;
        // blocking flow
		used.assign(MAX, 1);
		long long f1;
		while (1) {
			f1 = DFS(s, t, INF);
			if (f1 > 0)
				f += f1;
			else
				break;
		}
	}
}


int main() {
    cin >> n >> m;
    memset(cap, 0, sizeof(cap));
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        cap[u][v] += w;
	}

    long long int f = Dinic(1, n);// s = 1, t = n
    cout << f << endl;
	return 0;
}