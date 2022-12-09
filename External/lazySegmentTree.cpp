class SegmentTree{
private:
  std::vector<ll> aint;
  std::vector<ll> lazy;
public:
  SegmentTree(int n) {
    aint.resize(1 + 4 * n);
    lazy.resize(1 + 4 * n);
  }
 
  void cleannode(int node, int from, int to) {
    if(lazy[node] == 0)
      return ;
    if(from < to) {
      int mid = (from + to) / 2;
      lazy[node * 2] += lazy[node];
      lazy[node * 2 + 1] += lazy[node];
    }
    aint[node] += 1LL * (to - from + 1) * lazy[node];
    lazy[node] = 0;
  }
  
  void update(int node, int from, int to, int x, int y, int val) {
 
    cleannode(node, from, to);
    if(from == x && to == y) {
      lazy[node] += val;
      cleannode(node, from, to);
    } else {
      int mid = (from + to) / 2;
      cleannode(node * 2, from, mid);
      cleannode(node * 2 + 1, mid + 1, to);
 
      if(x <= mid)
        update(node * 2, from, mid, x, std::min(y, mid), val);
      if(mid + 1 <= y)
        update(node * 2 + 1, mid + 1, to, std::max(mid + 1, x), y, val);
      aint[node] = aint[node * 2] + aint[node * 2 + 1];
    }
  }
 
  ll query(int node, int from, int to, int x, int y) {
    cleannode(node, from, to);
 
    if(from == x && to == y) {
      cleannode(node, from, to);
      return aint[node];
    } else {
      int mid = (from + to) / 2;
      if(x <= mid && y <= mid)
        return query(node * 2, from, mid, x, y);
      else if(mid + 1 <= x && mid + 1 <= y)
        return query(node * 2 + 1, mid + 1, to, x, y);
      else
        return query(node * 2, from, mid, x, mid) +
               query(node * 2 + 1, mid + 1, to, mid + 1, y);
    }
  }
};
