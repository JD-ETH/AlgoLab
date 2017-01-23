#include <iostream>
#include <vector>

typedef std::vector<std::vector< int > > VecVec;

VecVec memo;

int find_congruent(std::vector<int> & hs, int ind, int cur_goal,int &k){
  int res;
  if (memo[ind][cur_goal] ==-1){
    if (hs[ind]==cur_goal) res=1;
    else if (ind ==0) res = 0;
    else {
      int new_goal = cur_goal-hs[ind];
      if (new_goal<0) new_goal+=k;
      res = (find_congruent(hs,ind-1, cur_goal,k) || find_congruent(hs,ind-1,new_goal,k));
    }
    memo[ind][cur_goal]=res;
  }
  else{
    res = memo[ind][cur_goal];
  }
  return res;
}
void do_case(){
  int n,goal,k;
  std::cin >> n >> goal >>k;
  goal = goal%k;
  //std::cout << goal;
  std::vector<int> hs(n);
  memo = VecVec(n, std::vector<int>(k,-1));
  for (int i = 0; i < n; i++){
    long h;
    std::cin >> h;
    hs[i] = h%k;
    //std::cout << hs[i] << " " ;
  }
  if (find_congruent(hs,n-1,goal,k)==1)   std::cout << "yes"  << std::endl;
  else std::cout << "no" << std::endl;

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
