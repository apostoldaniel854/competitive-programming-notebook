class Dsu{
  private:
    std::vector<int> mult;
  public:
    Dsu(int n) {
      mult.resize(1 + n);
      for(int i = 1; i <= n; i++)
        mult[i] = i;
    }
 
    int jump(int gala) {
      if(mult[gala] != gala) 
        mult[gala] = jump(mult[gala]);
      return mult[gala];
    }
 
    void unite(int gala, int galb) {
      gala = jump(gala);
      galb = jump(galb);
      if(gala == galb)
        return ;
      mult[gala] = galb;
    }
    bool connect(int x, int y) {
      return jump(x) == jump(y);
    }
};
