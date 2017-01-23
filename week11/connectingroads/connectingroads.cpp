#include <iostream>
#include <vector>

std::vector<int> memo;
int m,n;
struct Node {

  std::vector<int> childrens;
};
int solve(int  root, std::vector<Node> & nodes){
  int res=0;
  if (memo[root] == -1){
    std::vector<int> childs = nodes[root].childrens;
    if (childs.size() == 0){ // leaf
      res = 0;
    }
    else {
      for (int i = 0; i < childs.size(); i++){
        res+=solve(childs[i],nodes);
      }
      int copy_res = res;

      for (int i = 0; i < childs.size(); i ++){
        int take_i_res = copy_res-solve(childs[i],nodes)+1;
          std::vector<int> grandchilds = nodes[childs[i]].childrens;
           if (grandchilds.size() != 0) {
             for (int j = 0; j < grandchilds.size(); j++){
               //std::cout << "grandchilds" << grandchilds[j]<<std::endl;
               take_i_res+=solve(grandchilds[j],nodes);
             }
           }
        res = std::max(take_i_res,res);
      }
    }

    //std::cout << root << "  has " << res << std::endl;
    memo[root] = res;
  }
  else {
    res = memo[root];
  }
  return res;
}
void do_case(){
  std::cin >> n >> m;
  memo = std::vector<int>(n,-1);
  std::vector<Node> nodes(n);
  int u ,v;
  for (int i = 0; i < m ; i ++){
    std::cin >> u >> v ;u--; v--;
    //std::cout << "u " << u << "v " << v;

    nodes[u].childrens.push_back(v);
  }
  //std::cout << "finished reading\n";
  // Assuming root is always 0
  std::cout << solve(0,nodes)<< std::endl;
}
int main(){
  int t;
  std::cin >> t;
  while(t--){
    do_case();
  }
  return 0;
}
