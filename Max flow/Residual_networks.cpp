#include <iostream>
#include <vector>

using namespace std;

// Residual network
int c[1001][1001] = {0}; // Capacity
int f[1001][1001] = {0}; // Flow
int cf[1001][1001] = {0}; // Residual capacity

int main(){
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m;i++){
        int u, v, ct, ft;
        cin >> u >> v >> ct >> ft;
        c[u][v] = ct;
        f[u][v] = ft;
        if (f[v][u] == 0){
            f[v][u] = -ft;
        }
        else{
            f[u][v] = f[u][v] - f[v][u];
            f[v][u] = -f[u][v];
        }
    }
    for (int i = 1; i <= n;i++){
        for (int j = 1; j <= n;j++){
            cf[i][j] = c[i][j] - f[i][j];
            if(cf[i][j]>0){
                cout << i << " " << j << " " << cf[i][j] << endl;
            }
        }
    }
    return 0;
}

/* input sample:
4 5
1 2 2 2
2 4 3 1
2 3 2 1
1 3 2 1
3 4 2 2
*/
/* output sample:
1 3 1
2 1 2
2 3 1
2 4 2
3 1 1
3 2 1
4 2 1
4 3 2
*/