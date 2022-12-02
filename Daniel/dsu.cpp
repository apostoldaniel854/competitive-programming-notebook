struct DSU {
    int n;
    vector <int> f;
    DSU (int n) {
        this->n = n;
        f.resize (n + 1);
        for (int i = 1; i <= n; i++)
            f[i] = i;
    }
    int ft (int x) {
        if (f[x] == x) return x;
        return (f[x] = ft (f[x]));
    }
    bool unite (int x, int y) {
        int tx = ft (x);
        int ty = ft (y);
        if (tx == ty)
            return false;
        f[tx] = ty;
        return true;
    }
};
