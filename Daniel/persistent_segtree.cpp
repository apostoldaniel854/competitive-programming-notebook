class Node {
private:
    Node *lnode, *rnode;
    int cnt;
public:
    Node(Node *_lnode, Node *_rnode, int _cnt) : lnode(_lnode), rnode(_rnode), cnt(_cnt) {
 
    }
    void createTree(int lb, int rb) {
        if (lb == rb)
            return;
        int mid = (lb + rb) / 2;
        lnode = new Node(NULL, NULL, 0);
        rnode = new Node(NULL, NULL, 0);
        lnode->createTree(lb, mid);
        rnode->createTree(mid + 1, rb);
    }
    Node* update(int lb, int rb, int pos, int val) {
        if (lb == rb)
            return new Node(NULL, NULL, cnt + val);
        int mid = (lb + rb) / 2;
        if (pos <= mid)
            return new Node(lnode->update(lb, mid, pos, val), rnode, cnt + val);
        else
            return new Node(lnode, rnode->update(mid + 1, rb, pos, val), cnt + val);
    }
    int query(int lb, int rb, int k) { /// kth element
        if (lb == rb) {
            if (k == cnt && cnt == 1)
                return lb;
            return n + 1;
        }
        int cntLeft = lnode->cnt;
        int mid = (lb + rb) / 2;
        if (k <= cntLeft)  /// we search in left son
            return lnode->query(lb, mid, k);
        return rnode->query(mid + 1, rb, k - cntLeft);
    }
};
