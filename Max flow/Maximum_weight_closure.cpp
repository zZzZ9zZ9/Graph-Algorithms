#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// Maximum weight closure
// closure: for every node in the subset, all outgoing edges from that node lead to other nodes within the same subset.
// Each node in the graph has an associated weight, which can be positive or negative. 
// The goal is to find a closure where the total weight of the included nodes is maximized.

// Please understand principle of the code from the concept of minimum cut

const int INF = 0x3f3f3f3f;
const int MAX = 5010;

int cap[MAX][MAX] = { 0 };
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

int cnt = 0;// number of nodes in the closure (including the source node)
bool visit[MAX] = { 0 };

void DFS_connected(int s) {
    visit[s] = 1;
    cnt++;
    for (int i = 1; i <= n; i++) {
        if (cap[s][i] > 0 && !visit[i]) {
            DFS_connected(i);
        }
    }
}

int main() {
    cin >> n >> m;
    int s = n + 1, t = n + 2;
    long long ceiling = 0;
    for (int i = 1; i <= n; i++){
        int w;
        cin >> w;
        if(w > 0){
            ceiling += w;
            cap[s][i] = w;
        }
        else{
            cap[i][t] = -w;
        }
    }
    for (int i = 0; i < m;i++){
        int u, v;
        cin >> u >> v;
        cap[u][v] = INF;
    }

    n = n + 2;
    long long int min_cut = Dinic(s, t);
    long long int max_weight = ceiling - min_cut;

    DFS_connected(s);

    cout << cnt - 1 << ' ' << max_weight << endl;

    return 0;
}

/* input sample:
5 5
8
-9
-20
12
-10
1 2
2 5
1 4
3 4
4 5
*/
/* output sample:
2 2
*/