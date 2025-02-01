# include <iostream>
# include <vector>
using namespace std;

// Given a directed graph and a positive integer k
// calculate the number of paths of length k from vertex i to vertex j(0<=i,j<n)
// Using adjacency matrix to calculate

vector<vector<int>> multiply(vector<vector<int>> a, vector<vector<int>> b){
    vector<vector<int>> c(100, vector<int>(100, 0));
    for (int i = 0; i < 100;i++){
        for (int j = 0; j < 100;j++){
            for (int k = 0; k < 100;k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}
vector<vector<int>> power(vector<vector<int>> matrix, int k){
    if(k==1){
        return matrix;
    }
    if(k%2==1){
        return multiply(matrix, power(matrix, k - 1));
    }
    else {
        vector<vector<int>> temp = power(matrix, k / 2);
        return multiply(temp, temp);
    }
}
int main(){
    int n, m, k;
    vector<vector<int>> adj(100, vector<int>(100, 0));
    cin >> n >> m >> k;
    for (int i = 0; i < m;i++){
        int a, b;
        cin >> a >> b;
        adj[a][b] = 1;
    }
    vector<vector<int>> length_k = power(adj, k);
    // the number of paths of length k from vertex i to vertex j
    for (int i = 1; i <= n;i++){
        for (int j = 1; j <= n;j++){
            cout << length_k[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

/*input sample:
3 4 3
2 2
1 2
3 2
2 1
*/
/*output sample:
1 2 0
2 3 0
1 2 0
*/