class Fenwick {
private:
    vector <long long> bit;
    int n;
public:
    Fenwick(int n) : n(n), bit(1 + n, 0) {}
    void add(int pos, long long val) {
        while (pos <= n) {
            bit[pos] += val;
            pos += pos & -pos;
        }
    }
    long long get(int pos) {
        long long ans = 0;
        while (pos > 0) {
            ans += bit[pos];
            pos -= pos & -pos;
        }
        return ans;
    }
    long long get(int l, int r) {
        return get(r) - get(l - 1);
    }
};
