struct Matrix{
private:
public:
  ll dp[sigma][sigma];
  Matrix() {
    for(int i = 0; i < sigma; i++)
      for(int j = 0; j < sigma; j++)
        dp[i][j] = inf;
  }
  Matrix operator * (Matrix oth) {
    Matrix result;
    for(int i = 0; i < sigma; i++)
      for(int j = 0; j < sigma; j++)
        for(int h = 0; h < sigma; h++)
          result.dp[i][j] = std::min(result.dp[i][j], dp[i][h] + oth.dp[h][j] - 1);
    return result;
  }
};
 
Matrix lgpow(Matrix a, ll b) {
  if(b == 1)
    return a;
  else {
    Matrix result = lgpow(a, b / 2);
    if(b % 2 == 0)
      return result * result;
    else
      return result * result * a;
  }
}
 
