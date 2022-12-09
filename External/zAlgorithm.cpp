std::vector<int> zAlgo(std::string s) {
  int center = 0;
  std::vector<int> pre(s.size());
  
  for(int i = 1; i < s.size(); i++) {
    if(i < center + pre[center]) 
      pre[i] = std::min(center + pre[center] - 1 - i, pre[i - center]);
    while(i + pre[i] < s.size() && s[i + pre[i]] == s[pre[i]])
      pre[i]++;
    if(center + pre[center] < i + pre[i])
      center = i;
  }
  
  /*
  std::cout << "Zalgo\n";
  std::cout << s << '\n';
  for(int i = 0; i < pre.size(); i++)
    std::cout << pre[i] << " ";
  std::cout << '\n';
  */
 
  return pre;
}
