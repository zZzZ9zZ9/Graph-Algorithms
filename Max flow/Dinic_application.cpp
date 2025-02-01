#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// Given a directed graph
// how many nodes need to be deleted to make t is unreachable from s
// if there are multiple solutions, select the one with minimum index

const int INF = 0x3f3f3f3f;
const int MAX = 410;

int cap[MAX][MAX] = { 0 };// we use the cap martix to represent the residual network
int level[MAX] = { 0 };
int initial_cap[MAX][MAX] = {0};

int n;

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
    int s, t;
    cin >> n >> s >> t;
    memset(cap, 0, sizeof(cap));
    for(int i = 1; i <= n; i++){
        cap[i][i + n] = 1;
        initial_cap[i][i + n] = 1;
        for(int j = 1; j <= n; j++){
            int temp;
            cin >> temp;
            if(i == j)
                continue;
            if(temp == 1){
                cap[i + n][j] = INF;
                initial_cap[i + n][j] = INF;
            }
        }
    }
    if(initial_cap[s + n][t] == INF){
        cout << "NO ANSWER!";
        return 0;
    }
    initial_cap[s][s + n] = INF;
    initial_cap[t][t + n] = INF;
    cap[s][s + n] = INF;
    cap[t][t + n] = INF;

    n = n * 2;
    long long int min_cut = Dinic(s + n / 2, t);
    cout << min_cut << endl;

    vector<int> ans;
    for (int i = 1; i <= n / 2;i++){
        if(i == s || i == t)
            continue;
        initial_cap[i][i + n / 2] = 0;
        // copy the initial cap to cap
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cap[i][j] = initial_cap[i][j];

        long long int temp = Dinic(s + n / 2, t);
        if(temp == min_cut - 1){
            ans.push_back(i);
            min_cut = temp;
            if(min_cut == 0)
                break;
        }
        else{
            initial_cap[i][i + n / 2] = 1;
        }
    }

    for(auto i: ans)
        cout << i << ' ';
    cout << endl;
    return 0;
}


/* input sample:
3 1 3
1 1 0
1 1 1
0 1 1
*/
/* output sample:
1
2 
*/