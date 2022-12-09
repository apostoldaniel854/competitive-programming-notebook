/// be careful about MAX_N
struct Edge {
    int to;
    int cost;
};
 
struct Node {
    int node;
    ll val;
    bool operator < (const Node& other) const {
        return val > other.val;
    }
};

ll dist[1 + MAX_N];
vector <Edge> gr[1 + MAX_N];

void dijkstra(int source) {
    for (int i = 1; i <= MAX_N; i++)
        dist[i] = INF;
    priority_queue <Node> pq;
    dist[source] = 0;
    pq.push({source, 0});
    while (pq.size()) {
        int node = pq.top().node;
        ll val = pq.top().val;
        pq.pop();
        if (dist[node] == val) {
            for (Edge e : gr[node]) {
                if (dist[node] + e.cost < dist[e.to]) {
                    dist[e.to] = dist[node] + e.cost;
                    pq.push({e.to, dist[e.to]});
                }
            }
        }
    }
}
