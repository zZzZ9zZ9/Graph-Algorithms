#include <iostream>
#include <vector>
using namespace std;

// union-find set
// Given an undirected graph with n nodes, m edges, calculate the number of connected components
int parent[100001];
void Initialize(int n){
    for (int i = 0; i <= n;i++){
        parent[i] = i;// initialize the parent of each node as itself
    }
}
int find_root(int a){
    int t = a;
    while(parent[a]!=a){// find the root
        a = parent[a];
    }
    parent[t] = a;// path compression
    return a;
}

int main(){
    int n, m;
    cin >> n >> m;
    Initialize(n);
    for (int i = 0; i < m;i++){
        int a, b;
        cin >> a >> b;
        int root_a = find_root(a);
        int root_b = find_root(b);
        parent[root_b] = root_a;
        parent[b] = root_a;// path compression
    }
    int number = 0;
    for (int i = 1; i <= n;i++){// calculate the number of connected components
        if(parent[i]==i){
            number++;
        }
    }
    cout << number;
    return 0;
}

/*input sample:
5 4
1 2
2 4
4 1
3 5
*/
/*output sample:
2
*/