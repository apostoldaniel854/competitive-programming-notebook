

const int N = 15e4;
int a[1 + N], b[1 + N];
vector <pair <int, int>> updates[1 + 4 * N]; /// here we store the updates in the divide and conquer
vector <int> q[1 + N]; /// the queries in each leaf
/// DON'T FORGET TO INITIATE THE DSU
void addUpdate (int node, int lb, int rb, int ql, int qr, pair <int, int> edge) {
    if (ql <= lb && rb <= qr) {
        updates[node].pb (edge);
        return;
    }
    int mid = (lb + rb) / 2;
    if (ql <= mid)
        addUpdate (node * 2, lb, mid, ql, qr, edge);
    if (mid < qr)
        addUpdate (node * 2 + 1, mid + 1, rb, ql, qr, edge);
}

struct Op {
    int node;
    int x;
    int y;
    int valueX;
    int valueY;
    int szX;
    int szY;
};
stack <Op> undoStack;
int f[1 + N];
int sz[1 + N];
int value[1 + N];
int ft (int x) {
    return (f[x] == x) ? x : ft (f[x]);
}

void addEdge (int node, int x, int y) {
    x = ft (x);
    y = ft (y);
    if (x != y) {
        if (sz[x] < sz[y])
            swap (x, y);
        undoStack.push ({node, x, y, value[x], value[y], sz[x], sz[y]});
        sz[x] += sz[y];
        f[y] = x;
        value[x] = min (value[x], value[y]);
    }
}

void removeEdge () {
    Op op = undoStack.top ();
    undoStack.pop ();
    int x = op.x, y = op.y;
    sz[x] = op.szX;
    sz[y] = op.szY;
    value[x] = op.valueX;
    value[y] = op.valueY;
    f[x] = x; f[y] = y;
}

bool ans;

void go (int node, int lb, int rb) {
    for (pair <int, int> edge : updates[node])
        addEdge (node, edge.first, edge.second);
    if (lb == rb) {
        /// queries in this leaf
        /// TO CHANGE
        for (int node : q[lb])
            ans &= (value[ft (node)] == b[node]);
    }
    else {
        int mid = (lb + rb) / 2;
        go (node * 2, lb, mid);
        go (node * 2 + 1, mid + 1, rb);
    }
    while (undoStack.size () && undoStack.top ().node == node)
        removeEdge ();
}
