#include <iostream>
#include <vector>
#include <climits>
typedef std::vector<std::vector<int > > vecvec;

vecvec memo;

int find_cost(int inda, int indb,std::vector<int> & parsum_a, std::vector<int> & parsum_b){
  for (int i = 0; i < inda; i++){ // init first row and first colomn
    memo[i][0] = (parsum_a[i]-1-i)*(parsum_b[0]-1);
    memo[0][i] = (parsum_b[i]-1-i)*(parsum_a[0]-1);
  }
  for (int i = 1; i < inda; i++){
    for (int j = 1; j < indb; j++){
      // Update and compare
      //int res = (parsum_a[i]-1-i)* (parsum_b[j]-1-j); // Everything at once!
      int cur_a_weight = parsum_a[i]-parsum_a[i-1]-1;
      int cur_b_weight = parsum_b[j]-parsum_b[j-1]-1;
      int res = cur_a_weight*cur_b_weight+memo[i-1][j-1];
      res= std::min(res,memo[i][j-1]+cur_a_weight*cur_b_weight);
      res = std::min(res,memo[i-1][j]+cur_a_weight*cur_b_weight);
    //   for (int remove_i =1; remove_i <= i; remove_i++){
    //     int x_cost = (parsum_a[i]-parsum_a[i-remove_i]-remove_i);
    //
    //     res = std::min(res,
    //                     memo[i-remove_i][j-1]+
    //                     x_cost*cur_b_weight);
    //
    //   }
    //
    //
    //   for (int remove_j =1; remove_j <= j; remove_j++){
    //     int y_cost = (parsum_b[j]-parsum_b[j-remove_j]-remove_j);
    //     res = std::min(res,
    //                     memo[i-1][j-remove_j]+
    //                     y_cost*cur_a_weight);
    //
    // }

      memo[i][j] = res;
    }
  }

  return memo[inda-1][indb-1];
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
