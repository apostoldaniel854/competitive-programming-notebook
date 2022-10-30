
struct node_info {
    int mx;
    node_info(int value = 0) {
        this->mx = value;
    }
    node_info operator + (node_info other) const {
        node_info RES;
        RES.mx = max(mx, other.mx);
        return RES;
    }
};

class SegTree {
private:
    vector <node_info> seg;
public:
    SegTree(int n) {
        seg.resize(1 + 4 * n);
    }
    void update_pos(int node, int lb, int rb, int pos, node_info val) {
        if (lb == rb) {
            seg[node] = val;
            return;
        }
        int mid = (lb + rb) / 2, lnode = node * 2, rnode = node * 2 + 1;
        if (pos <= mid)
            update_pos(lnode, lb, mid, pos, val);
        else
            update_pos(rnode, mid + 1, rb, pos, val);
        seg[node] = seg[lnode] + seg[rnode];
    }
    node_info query_range(int node, int lb, int rb, int ql, int qr) {
        if (lb == ql && rb == qr)
            return seg[node];
        int mid = (lb + rb) / 2, lnode = node * 2, rnode = node * 2 + 1;
        if (ql <= mid && qr <= mid)
            return query_range(lnode, lb, mid, ql, qr);
        else if (mid + 1 <= ql && mid + 1 <= qr)
            return query_range(rnode, mid + 1, rb, ql, qr);
        else
            return query_range(lnode, lb, mid, ql, mid) + query_range(rnode, mid + 1, rb, mid + 1, qr);
    }
};
