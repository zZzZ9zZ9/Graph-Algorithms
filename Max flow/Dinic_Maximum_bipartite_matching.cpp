#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// Maximum bipartite matching
// Detailed explanation: Graph_Algorithm.md

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
    int n1, n2;// n1 is the number of vertices in the left set, n2 is the number of vertices in the right set
    cin >> n1 >> n2;
    n = n1 + n2 + 2;// include source and sink
    int s = n1 + n2 + 1, t = n1 + n2 + 2;
    memset(cap, 0, sizeof(cap));
    for (int i = 1; i <= n1; i++){
        cap[s][i] = 1;// source to left set
        int num;// the number of vertices that the vertex i in the left set can reach
        cin >> num;
        for(int j = 0; j < num; j++){
            int v;
            cin >> v;
            cap[i][v + n1] = 1;
        }
    }
    for(int i = n1 + 1; i <= n1 + n2; i++){
        cap[i][t] = 1;// right set to sink
    }

    long long int f = Dinic(s, t);
    cout << f << endl;
	return 0;
}

/* input sample:
5 5
2 2 5
3 2 3 4
2 1 5
3 1 2 5
1 2
*/
/* output sample:
4
*/