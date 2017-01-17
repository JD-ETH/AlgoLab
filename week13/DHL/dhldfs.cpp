#include <iostream>
#include <vector>
#include <climits>


void do_case(){

  int n;
  std::cin >> n;

  std::vector<int> as(n);
  std::vector<int> bs(n);
  for (int i = 0; i < n ; i++){
    int read; std::cin >> read;
    read--;
    as[i] = read;
  }
  for (int i = 0; i < n ; i++){
    int read; std::cin >> read;
    par_b += read;
    par_bs[i] = par_b;
  }
  memo = vecvec(n,std::vector<int>(n,-1));
  std::cout << find_cost(n,n,par_as,par_bs) <<std::endl;
}
int main(){
    std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  while(t--){
    do_case();
  }
  return 0;
}
