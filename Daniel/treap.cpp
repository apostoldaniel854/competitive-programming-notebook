const int GOL = 0;
class Treap {
private:
    struct Node {
        int val;
        int prio;
        int lnode = GOL, rnode = GOL;
        int cnt = 0;
        bool rev = false;
        Node(int val, int prio) : val(val), prio(prio) {

        }
    };
    int root = 0;
    vector <Node> treap = vector<Node> (1, Node(-1, -1));
    int updateNode(int node) {
        treap[node].cnt = treap[treap[node].lnode].cnt + treap[treap[node].rnode].cnt + 1;
        return node;
    }
    void push(int node) {
        if (node != GOL && treap[node].rev) {
            int lnode = treap[node].lnode, rnode = treap[node].rnode;
            treap[lnode].rev ^= 1;
            swap(treap[lnode].lnode, treap[lnode].rnode);
            treap[rnode].rev ^= 1;
            swap(treap[rnode].lnode, treap[rnode].rnode);
            treap[node].rev = false;
        }
    }
    int addNode(int val) {
        treap.push_back(Node(val, rand()));
        return updateNode((int)treap.size() - 1);
    }
    int join(int l, int r) {
        push(r);
        if (l == GOL)
            return r;
        push(l);
        if (r == GOL)
            return l;
        if (treap[l].prio > treap[r].prio) {
            treap[l].rnode = join(treap[l].rnode, r);
            return updateNode(l);
        }
        else {
            treap[r].lnode = join(l, treap[r].lnode);
            return updateNode(r);
        }
    }
    pair <int, int> split(int node, int key) {
        if (node == GOL)
            return {GOL, GOL};
        push(node);
        int cnt_left = treap[treap[node].lnode].cnt;
        if (key < cnt_left) { /// we go to the left
            pair <int, int> ans = split(treap[node].lnode, key);
            treap[node].lnode = ans.second;
            return {ans.first, updateNode(node)};
        }
        else {
            pair <int, int> ans = split(treap[node].rnode, key - cnt_left - 1);
            treap[node].rnode = ans.first;
            return {updateNode(node), ans.second};
        }
    }
    tuple <int, int, int> slice(int node, int lb, int rb) {
        int l, mid, r;
        tie(mid, r) = split(node, rb);
        tie(l, mid) = split(mid, lb - 1);
        return {l, mid, r};
    }
    void getVector(int node, vector <int> &v) {
        if (node != GOL) {
            push(node);
            getVector(treap[node].lnode, v);
            v.push_back(treap[node].val);
            getVector(treap[node].rnode, v);
        }
    }
public:
    void ins(int key, int val) {
        pair <int, int> t = split(root, key - 1);
        root = join(join(t.first, addNode(val)), t.second);
    }
    int getKth(int key) {
        int l, mid, r;
        tie(l, mid, r) = slice(root, key, key);
        root = join(join(l, mid), r);
        return treap[mid].val;
    }
    void revRange(int lb, int rb) {
        int l, mid, r;
        tie(l, mid, r) = slice(root, lb, rb);
        treap[mid].rev = true;
        swap(treap[mid].lnode, treap[mid].rnode);
        root = join(join(l, mid), r);
    }
    void rem(int lb, int rb) {
        int l, mid, r;
        tie(l, mid, r) = slice(root, lb, rb);
        root = join(l, r);
    }
    void print() {
        vector <int> sol;
        getVector(root, sol);
        for (int x : sol)
            cout << x << " ";
        cout << "\n";
    }
};
