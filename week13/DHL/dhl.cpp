#include <iostream>
#include <vector>
#include <climits>
typedef std::vector<std::vector<int > > vecvec;

vecvec memo;

int find_cost(int inda, int indb, std::vector<int> & parsum_a, std::vector<int> & parsum_b){
  int res;
  if (memo[inda][indb] == -1){
    if (inda == 0 || indb == 0){
      res = (parsum_a[inda]-1-inda)*(parsum_b[indb]-1-indb); // finish same time
      }
    else {
      res = INT_MAX;
      int xcost;
      for (int i = 1; i<=inda; i++){
        xcost =(parsum_a[inda]-parsum_a[inda-i]-i);
        for (int j = 1; j<=indb; j++){
          res = std::min(res,find_cost(inda-i,indb-j,parsum_a,parsum_b)+
                              xcost*
                              (parsum_b[indb]-parsum_b[indb-j]-j));
                              // Current cost and recursive
                            }

                          }
    }
    memo[inda][indb] = res;
  }
  else {
    res = memo[inda][indb];
  }

  return res;
}

void do_case(){

  int n;
  std::cin >> n;

  std::vector<int> par_as(n);
  std::vector<int> par_bs(n);
  int par_a =0;
  int par_b =0;
  for (int i = 0; i < n ; i++){
    int read; std::cin >> read;
    par_a += read;
    par_as[i] = par_a;
  }
  for (int i = 0; i < n ; i++){
    int read; std::cin >> read;
    par_b += read;
    par_bs[i] = par_b;
  }
  memo = vecvec(n,std::vector<int>(n,-1));
  std::cout << find_cost(n-1,n-1,par_as,par_bs) <<std::endl;
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
