#define pb push_back
const int INF = 1e9;

struct Edge {
    int x;
    int flow;
    int cap;
    int nxt;
};

struct Dinic {
    int source;
    int sink;
    int n;
    vector <vector <Edge>> gr;
    vector <int> dist;
    vector <int> start;
    Dinic (int _source, int _sink, int _size) {
        source = _source;
        sink = _sink;
        n = _size;
        gr.resize (_size + 1);
        dist.resize (_size + 1);
        start.resize (_size + 1);
    }
    void add_edge (int x, int y, int cap) {
        gr[x].pb ({y, 0, cap, gr[y].size ()});
        gr[y].pb ({x, 0, 0, gr[x].size () - 1});
    }
    bool bfs () {
        for (int i = 1; i <= n; i++)
            dist[i] = -1;
        dist[source] = 0;
        queue <int> q;
        q.push (source);
        while (q.size ()) {
            int node = q.front ();
            q.pop ();
            for (auto vec : gr[node]) {
                if (dist[vec.x] == - 1 && vec.cap > vec.flow) {
                    dist[vec.x] = dist[node] + 1;
                    q.push (vec.x);
                }
            }
        }
        return dist[sink] != -1;
    }
    int dfs (int node, int sink, int flow) {
        if (node == sink)
            return flow;
        while (start[node] < gr[node].size ()) {
            Edge e = gr[node][start[node]];
            if (dist[e.x] == dist[node] + 1 && e.flow < e.cap) {
                int new_flow = dfs (e.x, sink, min (flow, e.cap - e.flow));
                if (new_flow > 0) {
                    gr[node][start[node]].flow += new_flow;
                    gr[e.x][e.nxt].flow -= new_flow;
                    return new_flow;
                }
            }
            start[node]++;
        }
        return 0;
    }
    int maxflow () {
        int ans = 0;
        while (bfs ()) {
            int flow;
            for (auto &x : start) x = 0;
            while (flow = dfs (source, sink, INF))
                ans += flow;
        }
        return ans;
    }
};
