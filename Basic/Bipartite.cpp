#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// We say a undirected graph is a bipartite graph if we
// can divide the graph into two parts that vertices inside
// each part are not adjacent
// This equals to that it doesnot contain any odd cycle

// algorithm: color the vertices using 2 colors such that
// no adjacent nodes share the same color

int color[1000001] = { 0 };
vector<int> G[1000001];// undirected graph using adjacency list
queue<int> q;

int main()
{
	int n, m;// the number of node, and the number of edge
	cin >> n >> m;
	int a, b;
	while (m--)
	{
		cin >> a >> b;// input the edge(a,b)
		G[a].push_back(b);
		G[b].push_back(a);
	}
    //using BFS to color the vertices, two differnet color: 1, -1
	q.push(a);
	color[a] = 1;
	while (!q.empty())
	{
		int t = q.front();
		q.pop();
		for (int i = 0; i < G[t].size(); i++)
		{
			if (color[G[t][i]] == 0)
			{
				color[G[t][i]] = -color[t];
				q.push(G[t][i]);
			}
			else if (color[G[t][i]] == color[t])
			{
				cout << "NO";
				return 0;
			}
		}
	}
	cout << "YES";
	return 0;
}

/*
input sample:
5 6
1 2
3 2
3 5
1 3
5 1
2 4
*/
/*
output sample:
No
*/