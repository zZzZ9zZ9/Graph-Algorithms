# Graph
By Zizhuo Fu

Organized from **Professor Yun(Eric) Liang's Course: Modeling, Analysis, and Optimization for Computing System (Spring 2024) in PKU**

Note: The main introduction content is the graph algorithm, and detailed proof can be found in the course PPT. The attachment is the C++ implementation of the algorithm.

Recommended reading: https://cp-algorithms.com/index.html  (Graph)

## Graph Terminology
### definition
- A graph G consists of a set of **vertices V** and a set of **edges E**
    - An edge in E connects two vertices(may be identicle)
    - We use pair $(u,v)$ to represent an edge
    - An edge mey have a **weight**
- A graph can bee **directed** or **undirected**
    - Unlesee stated otherwise, a graph is undirected by default
    - iIn directed graph, edge $(u,v)$ has direction $u\rightarrow v$

### Adjacency
- Two vertex u,v are adjacent when there exists an edge $(u,v)$
- Degree
    - In undirected graph, the degree of vertex u is the number of edges associated with u
    - In directed graph, vertex 𝑢’s degree consists of **in-degree** and **out-degree**
        - In-degree of 𝑢 is the number of edges ending at 𝑢
        - Out-degree of 𝑢 is the number of edges starting from 𝑢
- In undirected graph, the sum of degree of all nodes equals to $2 × |E|$
- In directed graph, $\sum _{𝑢} indeg(𝑢) = \sum _{𝑢} outdeg(𝑢)= |𝐸|$

### Path
- A path in a graph is a sequence of vertices $𝑤_1, 𝑤_2, … , 𝑤_𝑘 $, such that $(𝑤_𝑖, 𝑤_{𝑖+1}) \in 𝐸$
    - It's called a path between $w_1$ and $w_k$
- when a path has no identicle nodes except the first and last one, it is called a **simple path**

### Cycle
- A simple path $w_1,w_2,...,w_k$ is called a cycle when $w_1=w_k$
- The number of edges in a cycle equals to the number of its vertices

### Subgraph
- A graph $G'=(V',E')$ is a subgraph of $G=(V,E)$ if
    - $V'\subseteq V$ and $E'\subseteq E$
    - If edge $(u',v')\in E'$, then $u'\in V'$ and $v'\in V'$

### Connectivity
- For a undirected graph $G$, if there is a path between any pair of vertices in $G$, then $G$ is a **connected graph** and we call $G$ is **connected**
- For a directed graph $G$
    - Weakly connected if replacing all of its directed edges with undirected edges produces a connected (undirected) graph
    - Strongly connected if for any pair of vertices 𝑢 and 𝑣, there is a path from 𝑢𝑢 to 𝑣𝑣 and a path from 𝑣 to 𝑢 in $𝐺$

### Tree
- A tree is a undirected graph that is connected and contains no cycle
- If the undirected graph is not connected and contains no cycle, then it's a **forest** (contains multiple trees)
- We can disignate a vertex as the root of a tree to get a **rooted tree**
    - In rooted tree, each vertex except the root has a **parent** which is its adjadent vertex closer to the root
    - Avertex may have multiple **children**
- The **ancestors** of a vertex consist of its parent and the ancestors of its parent
- The **descendants** of a vertex consists of its children and the descendants of its children

### Representation of Graph
#### Adjacency Matrix
```c
int adj[MAX][MAX];

vector<vector<int>> adj(MAX, vector<int>(MAX,0));
```
- Using a $N\times N$ matrix
    - $adj[u][v]=weight$ if there is an edge $(u,v)$ and $adj[u][v]=special~value$ otherwise
    - Space complexity $O(|V|^{2})$
- Pros:
    - Can perform matrix-based analysis
    - Allow $O(1)$ checking the adjacency of any pair of vertices
- Cons:
    - Huge memory cost for space graphs
    - It takes $O(|V|)$ time to find a vertex's associated edges, even when if has only a few edges
- $A[u][v]=1$ means there is a path from u to v with exatly 1 edge
    - $A^{k}[u][v]$ is the number of paths from u to v with exatly k edges
    - $A^{L}=A^{\lfloor\frac{L}{2}\rfloor}\cdot A^{\lfloor\frac{L}{2}\rfloor}\cdot (L~is~odd?A:I)$

#### Adjacency List
```c
vector<int> adj[MAX];// unweighted

struct edge{
    int v, w;
};
vector<edge> adj[MAX];// weighted

vector<pair<int,int>> adj[MAX];// first v, second w
```
- Every node has a linked list to store its associated edges
    - Space complexity: $O(|V|+|E|)$
- Pros:
    - No overhead for sparse graphs
    - Can enumerate v's edges in $O(outedge_v)$
- Cons:
    - Does not support random access, e.g. check if eddge $(u,v)$ exists

## Graph Traversal
- Given a graph and a starting vertex
- visiting all vertices reachable from the starting vertex **exactly once**
### Depth-first traversal
- Based on **Stack**: a first-in last-out data structure
- **Recursive** implementation
```c
DFS_Skeleton(u){
    visit[u]=1;
    Preprocess(u);// pre_order
    for(v adgacent with u){
        if(visit[v] == 0)
            DFS_Skeletion(v);
        Inprocess(u,v);// in_order
    }
    Postprocess(u);// post_order
}
```
- The depth-first search can classify edges into four types
    - **Tree edges** are edge $(u,v)$ that v’s first visit is through this edge, u is v's parent in the tree
    - **Back edges** are those edges $(u,v)$ in which v is an ancestor of u in a depth-first tree
    - **Forward edges** are those edges $(u,v)$ such
    that v is a descendant of u in a depth-first tree
    - **Cross edges** are all other edges
- The depth-first forest consists of tree edges
#### Properties
- Thm 1: Vertex u's ancestors in depth-first tree are the vertices in the search stack when visiting u
- Thm 2: In undirected graphs, every edge is either a tree edge or a back edge

### Bread-first traversal
- Based on **Queue**: a first-in first-out data structure
```c
BFS_Skeleton(u){
    queue q;
    q.push(u);
    while(q is not empty){
        v = q.pop();
        visit[v] = 1;
        for(w adjacent with v){
            if(visit[w] == 0)
                q.push(w);
            Process(v,w);
        }
    }
}
```
- Given an unweighted graph (or the weight of every edge is 1), using BFS can find the shortest path from u to v
    - if u is pushed earlier than v, then $dis[u]\leq dis[v]$

## Topological Sort
- **Directed Acyclic Graph (DAG)**
- Order its vertices such that if there is an edge $(v_i,v_j)$ then $v_i$ comes before $v_j$ in the ordering
    - A graph may have multiple valid topologic ordering
    - When a graph has cycles, it does not have a topological ordering
- Algorithm
    - Calculate the in-degree of all vertices
    - Find a vertex with $indeg_u=0$, append this vertex at the end of the current topologic ordering
    - Delete the vertex from the graph
    - Repeat the above steps
### BFS-based implementation
- A queue keeps the vertices with $indeg_u=0$
- Take a vertex from the head of the queue, append this vertex to the end of the current ordering
- Decrement the in-degree of its adjcent vertices. If a vertex's in-degree becomes 0, then push this vertex to the tail of the queue
```c
Topo_sort(){
    Compute InDeg of each node;
    queue q;
    for(u in V)
        if(InDeg[u] == 0)
            q.push(u);
    while(!q.empty()){
        v = q.top();
        append v at the end of the Topo Sequence;
        for(w adjencent with v){
            InDeg[w]--;
            if(InDeg[w] == 0){
                q.push(w);
            }
        }
    }
}
```
- We can find that the queue is not necessary, we can use other data structure like stack, vector... to store vertices with a degree of 0.
- We can use the **priority_queue** to store, which is used to order according to some **special weight**
    - e.g. Minimum topological order
### DFS-based implementation
- Reachable: In a graph, if there is a path from u to v, then we say v is reachable from u
- Calculate the reverse topological ordering, i.e. v's reachable vertices should appear earlier than v in the ordering
- Recursively find a vertex with no outgoing edge, i.e. $outdegree=0$ and delete this vertex from the graph
```c
DFS(u){
    visit[u]=1;
    for(v adjacent with u)
        if(visit[v] == 0)
            DFS(v);
    append u at the end of the Topo Sequence;
}
Topo_Sort_reverse(){
    for(u in V)
        if(visit[u] == 0)
            DFS(u);
}
```

## Strongly Connected Component
### Definition
- Given a directed G
- G is a **weakly connected** if all vertices are connected when directed edges are replaced with undirected edges
- G is a **strongly connected** if any pair of vertices are reachable from each other
- **Strongly connected component** is a subgraph of G that is **strongly connected** and **maximal**
    - Maximal means adding any vertex to the subgraph will break the strong connectivity
- If we merge each strongly connected component, the resulted graph is acyclic
### Kosaraju's Algorithm
- Group vertices into SCCs
- $O(|V|+|E|)$
- **Reverse graph**
    - The reverse graph has the same SCCs as the original graph
- **Kernel graph**
    - Merge each SCC into a single vertex, the resulted graph is an acyclic graph
    - Denoted as $G^{SCC}=(V^{SCC},E^{SCC})$
- Two passes of DFS
    - **Post-order DFS**
        - Call DFS on the original graph
    ```c
    DFS1(u){
        visit[u] = 1;
        for(v adjacent with u)
            if(visit[v] == 0)
                DFS1(v);
        push u to post-order;
    }
    for(u in |V|){
        // Any reference sequence for DFS is OK
        if(visit[u] == 0){
            DFS1(u);
        }
    }
    ```
    - **Find Reachable Nodes**
        - Call DFS on the reversed graph by reversed post-order
    ```c
    DFS2(u){
        visit[u] = 1;
        for(v adjacent with u in reversed graph)
            if(visit[v] == 0)
                DFS2(v)
        temp_SCC.push(u); // any order is OK, just store it
    }
    for(u in reverse post-order){
        // Traverse from back to front according to post-order
        // Use this sequence as the reference sequence for DFS
        temp_SCC.clear();
        if(visit[u] == 0){
            DFS2(u);
            // vertices visited by this call
            // form a SCC use the temp_SCC
        }
    }
    ```

## Shortest Path
- Find the shortest path from s to t in a graph
- Requirement: no negative cycle
- Different types of shortest path
    - Unweighted graph
        - Breadth-first Traversal
    - **Single source shortest path (SSSP)**: find the shortest path from s to all other vertices
        - Bellman-Ford algorithm, Dijkstra algorithm
    - **Find the shortest path between all pair of vertices**
        - Floyd-Warshall algorithm
### Relaxation
- Using Triangle Inequality
- If there is an edge $u\rightarrow v$, then
    - $d_{s\rightarrow v}\leq d_{s\rightarrow u}+w$
    - For the longest path, it's opposite 
- Relaxation: for an edge $(u\rightarrow v,c)$, update v with
    - $d_{s\rightarrow v}=min(d_{s\rightarrow v}, d_{s\rightarrow u}+c)$
```c
bool Relax(u,v,c){
    if(dis[v] > dis[u] + c){
        dis[v] = dis[u] + c;
        return true;
    }
    else
        return false
}
```

### Bellman-Ford Algorithm
- **Iteratively** relax: in each iteration, relax for all edges
- $d_{s\rightarrow v}$ will converge in $|V|-1$ iterations, otherwise there exist a negative cycle
- Requirement: **no negative cycle**
- $O(|V|\cdot |E|)$
```c
void Bellman_Ford(source){
    dist[source]=0;
    for(int i = 0;i < |V| - 1;i++){
        for(Edge(u,v,c) in E)
            Relax(u,v,c);
    }
    for(Edge(u,v,c) in E)
        if(Relax(u,v,c))
            error("Negative cycle exists");
}
```

### Dijkstra's Algorithm
- A greedy algorithm
- Maintain a **heap** of nodes sorted by their current $d_{s\rightarrow v}$
- Select the node with the shortest distance from heap and relax its adjacent nodes
- push the updated nodes into the heap
- Requirement: **no negative weight edge**
- $O(|E|+|V|\cdot log|E|)$
```c
void Dijkstra(source){
    dist[source] = 0;
    parent[]={};// parent for each node in the shortest path tree
    priority_queue H;// sort nodes by their distance
    H.push({0, source});// first dist, second index
    while(!H.empty()){
        cur = H.top();
        H.pop();
        if(cur.first > dist[cur.second])
            continue;
            // consider nodes that have been updated and added multiple times
            // or another implement: when H.push, if u exists in H, just update distance
            // but it's compicated
        for(Edge(cur.second->u,c) in E){
            if(Relax(curnode,u,c)){
                parent[u]=curnode;
                H.push({dist[u], u});
            }
        }
    }
}
```

### Floyd-Warshall Algorithm
- Find the shortest path between any pair of vertices
- $O(|V|^{3})$
- Let $d_{ij}^{k}$ be the distance of the shortest path between $i$ and $j$ that does not contain vertices with label greater than $k$
- Initial value
    - $d_{ii}^{0}=0$
    - $d_{uv}^{0}=w(u,v)$
    - $d_{ij}^{0}=inf$
- Compute $d_{ij}^{k}$
    - $d_{ij}^{k}=min(d_{ij}^{k-1},d_{ik}^{k-1}+d_{kj}^{k-1})$
```c
Floyd(){
    for(i = 1,...,N){
        d[0][i][i]=0;
        for(j = 1,...,N)
            if(i != j)
                d[0][i][j] = inf;
    }
    for((u,v) in E)
        d[0][u][v] = w[(u,v)];
    
    for(k = 1,...,N)
        for(i = 1,...,N)
            for(j = 1,...,N)
                d[k][i][j] = min(d[k-1][i][j], d[k-1][i][k]+d[k-1][k][j]);
}
```


## Minimum Spanning Tree
- Given a weighted undirected graph
- $T=(V,E')$ is the **spanning tree** of $G$ when:
    - $E'\subseteq E$ has exatly $|V|-1$ edges
    - $T$ is connected
- **Minimum spannning tree (MST)**: the spanning tree that minimizes the total weights

### Prim Algorithm
- A greedy algorithm
    - Let $S$ be the set of connected vertices in the MST
    - Initially $S$ has only one arbitrary vertex, and $E'=\emptyset$
    - Repeat the following steps until $S=V$
        - Choose the edge $e=(u,v)$ with the minimum weight, such that $u\in S, v\in V-S$
        - Update $E'=E'\cup \{e\},S=S\cup \{v\}$
    - $T=(S,E')$ is a MST
- Using a **heap** $H$ to contain edges between $S$ and $V - S$
- $O(|E|\cdot log|E|)$
```c
Prim(){
    S={v1}\\ v1 can be replaced by a random vertex
    priority_queue H;// a heap of edge, sorted by their weights
    while(S!=V){
        (u,v)=H.top();
        H.pop();
        if u,v in S
            continue;
        S += {v};
        for (u,v) in E
            H.push((v,x));
    }
}
```  

### Kruskal's Algorithm
- A greedy algorithm
    - Sort edges by their weights in increasing order
    - Enumerate all edges
    - Initially $E'=\emptyset$
    - For edge $e=(u,v)$, discard e if u and v are already connected by $E'$
        - If not, update $E'=E'\cup \{e\}$, merge u and v in union-find set
- Maintain connectivity using **union-find set**
- $O(|E|\cdot log|E|)$
```c
Kruskal(){
    sort edges in E by their weights
    for edge e = (u,v) in E
        if u and v is in the connected component
            continue
        else{
            merge the connected component of u and v
            add edge e into MST
        }
}
```
#### Union-find Set
- Initialize: `parent[i]=i`
- Find(u): find the root of u
- Merge(u,v)
- **Optimization**
    - Maintain the size of each vertex's sub-tree
    - During traversal, try to minimize the depth of the tree as much as possible
```c
find_root(x){
    int t = x;
    while(parent[x]!=x){
        x = parent[x];
    }
    parent[t] = x;
    return x;
}
```

## Max Flow
- Formulation network: A connected, directed graph
    - Edge (u,v) has a non-negetive capacity c(u,v)>0
    - Two special vertices, the source s and the sink t
- Flow: A flow $f$ is a set of real numbers $f(u,v)$ that satisfy
    - Capacity constraint: $f(u,v)\leq c(u,v)$
    - Skew symmetry: $f(u,v)=-f(v,u)$
    - Flow conservation: For vertices other than s,t,flows entering it are equal to flows exiting it
- Find the flow with the maximum value in a flow network

#### Residual networks
- $G_f=(V,E_f)$
- $c_f(u,v)=c(u,v)-f(u,v)$
#### Augmenting path
- A path from s to t in the residual network such that edges have positive capacity
- Improve the flow
- A flow is maximum $\Leftrightarrow$ there is no augmenting path

### Ford-Fulkerson Method
- Iteratively find an arbitrary aumenting path on the residual network and update the flow until no more path exists
- $O(|E|\cdot |f^*|)$
    - $f^*$ is the maximum flow
```c
Ford_Fulkerson(G,s,t){
    f is a zero flow
    while(true){
        Gf = Build residual network from G and f
        path = find augmenting path in Gf
        if path == ∅
            return f;
        f = Update(f,path);
    }
}
```

### Edmonds-Karp Algorithm
- Find the shortest augmenting path(in terms of #edges) using BFS
- $O(|V|\cdot |E|^2)$
```c
Edmonds_Karp(G,s,t){
    f is a zero flow
    while(true){
        Gf = Build residual network from G and f
        path = shortest path in Gf from s to t
        if path == ∅
            return f;
        f = Updated(f,path);
    }
}
```

### Dinic's Algorithm
- $O(|V|^2\cdot |E|)$
#### Level graph
- Let `dist[v]` be the length of the shortest path (in terms of #edges) from s to v in $G_f$
- $G_L=(V,E_L,c_f)$
    - $E_L=\{(u,v)\in E_f:dist[v]=dist[u]+1\}$
#### Blocking flow
- A flow in level graph $G_L$ such that every s-t path has at least a saturated edge, i.e. s is blocked from t
- To compute a blocking flow, we iteratively find a path with slack from 𝑠 to 𝑡 and produce a flow until there is no such path
- **Depth-first traversal**
```c
DFS(x,t,limit){
    if x == t
        return true;
    for (x,u) in E
        if(cf(x,u)>0 and dist[u]==dist[x]+1)
            flag = DFS(u,t,min(limit,cf(x,u)));
            if(flag)
                prev[u]=x;
                return true;
    return false;
}
```
- This code is inefficient if we want to iteratively find augmenting paths, using `used[x]` to keep the index of the unexplored edges of x in the adjacency list
```c
int push(x,t,limit){
    if(x == t)
        return limit;
    for(int& i = used[x];i <= n;i++){
        if(cap[s][i]>0 && level[i]==level[x]+1){
            int f_limit = push(i,t,min(cap[s][i],limit));
            if(f_limit>0){
                cap[s][i]-=f_limit;
                cap[i][s]+=f_limit;
                return f_limit;
            }
        }
    }
    return 0;
}
```

```c
int blockingFlow(){
    int V = 0,t = 0;
    memset(used,1,sizeof(used));
    while((t = push(s,t,INF))>0)
        V += t;
    return V;
}
```
```c
Dinic(){
    Initialize f as zero flow
    while true
        GL = construct level graph from Gf
        if t is not reachable from s
            break
        Find a blocking flow in GL
        update f
}
```

### Min cut
- For a flow network, a cut(S,T) is a partition that divides the vertices into two sets S,T such that s$\in$S and t$\in$T
    - The cost of the cut is $\sum_{u\in S,v\in T} c(u,v)$
- The following three conditions are equivalent
    - $f$ is the maximum flow
    - $G_f$ has no augmenting path
    - Exist a $cut(S,T)$ such that $|f|=c(S,T)$
- How to find a minimum cut
    - Compute max-flow on the flow network
    - Find reachable vertices from s in the residual network
    - Reachable vertices and unreachable vertices constitute a minimum cut

### Applications
- **Modeling is significant**

#### Multiple sources and sinks
- Create a super source $S$ and a super sink $T$
- $S$ connects to $s_1,s_2,...,s_n$ with a infinite capacity
- $t_1,t_2,...,t_n$ connects to $T$ with a infinite capacity

#### Vertex capacities
- Vertex v has capacity c(v) such that $\sum_{(u,v)\in E}f(u,v)\leq c(v)$
- Create two vertex $v_{in}$ and $v_{out}$ for v and an edge $e=(v_{in},v_{out})$ with $c(e)=c(v)$

#### Maximum Bipartite Matching
- Given
    - Two groups of n and m verticles
    - Edges between two groups
- Find the maximum number of matches given that each vertex can be matched once
- Create source s and sink t, connect s with group1, t with group 2
- Each vertex can be matched once $\Rightarrow$ Edges of source and sink have 1 capacity
- Edges between two groups have 1 capacity (arbitrary capacity $\geq 1$ is OK)


## Tree Covering
- Directed Acyclic Graph
#### Treeifying the input netlist
- Every place you see a gate with fanout > 1, you need to split
- To get subject tree
#### Tree matching
- For each node in the subject tree, find pattern trees in library that match
    - technology library $\rightarrow$ pattern tree
    - tree library
- Just do **pattern matching**
#### Minimum-cost covering
- Recursive call
- Just compute it once
    - First time, save it
    - Next time, look it up

