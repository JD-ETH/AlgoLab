#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::cin;
using std::cout;

typedef vector<vector<int> > vecvec;

// This is a DP problem, recursively calculating for given number of litres
static vecvec memo;
static vecvec memo_2; // map
static vector<vecvec> memo_bev; // [true/flase][ith bev][liter]
const int MAX_PRICE = 10000000;
// given an exact amout of the bevarage, mix up with least price
int cheapest_cost(int num_bev, int liter, vector<int> const & cost, vector<int> const & amount){
  int res;
  if (num_bev < 0 || liter <0 ){ // No choice but all
    res = MAX_PRICE;
    return res;
  }

  if (memo[num_bev][liter] == -1 ){
    if (liter == 0 ) {// exact amount of liter
      res = 0;
      }

    else{
      int cost_skip = cheapest_cost(num_bev-1,liter,cost,amount);
      int cost_take = cost[num_bev]+cheapest_cost(num_bev,liter-amount[num_bev],cost,amount);
      if (cost_take <= cost_skip){
        res = cost_take;
        memo_2[num_bev][liter] = liter-amount[num_bev]; // the path
        if (cost_take == cost_skip){
          memo_2[num_bev][liter]+= MAX_PRICE; // Not good example, indicating 2 possiblities!
        }
        //cout << num_bev << " liter " << liter << "  " << liter-amount[num_bev];
      }
      else{
        res = cost_skip;
        memo_2[num_bev][liter] = -1; // Not taking, goint up
      }


    }
    memo[num_bev][liter] = res;
  }
  else res = memo[num_bev][liter];

  return res;
}

//struct pos_and_bev_count{
//  int bev_index,litre,count;
//  bool prev; // Flag for already took from this bevarage
// };
// THIS IS THE PART I SUSPECT ERRORNEOUS
// ------------------------------------------------------------------
// Taking the best litre number and beverage number as input, get the bevarge in use
int count_bev(int taken, int bev_ind, int litre){
  // acutally a dfs to determine best path
  // Change to a DP approach!
  int res;
  if (memo_bev[taken][bev_ind][litre] == -1){
    if (litre == 0 ) {
      res = 0; // no litres left
      return res;}
    if (bev_ind < 0 ) {res = -100; return res;}
    int next_litre = memo_2[bev_ind][litre];
    if (next_litre == -1 ){ // Just going up!
      res = count_bev(0,bev_ind-1,litre);
    }
    else if(next_litre < MAX_PRICE){ // Just going left!
      res = count_bev(1,bev_ind,next_litre);
      if (!taken) res++; // Add one if newly taken
    }
    else { // Two possiblities
      next_litre = next_litre % MAX_PRICE;
      int take_res = count_bev(1,bev_ind,next_litre);
      if (!taken) take_res++; // Add one if newly taken
      res = std::max(count_bev(0,bev_ind-1,litre), take_res);
    }
    memo_bev[taken][bev_ind][litre] = res;

  }
  else {
    res = memo_bev[taken][bev_ind][litre];
  }

  return res;
}
  // pos_and_bev_count init_pos_count = {n-1,optimal_litre,0,false};
  // vector<pos_and_bev_count > stack(1,init_pos_count);
  // int counter = 0;
  //
  // do {
  //   pos_and_bev_count current_pos_count = stack.back();
  //   stack.pop_back();
  //   int next_index = memo_2[current_pos_count.bev_index][current_pos_count.litre];
  //   if (next_index == 0){
  //     // Reached the end, get the final bevarage count and compare
  //     int new_count = current_pos_count.count;
  //     if(!current_pos_count.prev) new_count++;
  //     counter = std::max(counter,new_count);
  //   }
  //   if (next_index ==-1 || next_index >= MAX_PRICE ) {
  //     // IN THIS CASE the ith Beverage is not taken and continue on to the i-1 th Beverage
  //     pos_and_bev_count not_take = {current_pos_count.bev_index-1,current_pos_count.litre,
  //                                   current_pos_count.count,false};
  //     stack.push_back(not_take); // add it to stack
  //   }
  //   if (next_index > 0 && next_index != MAX_PRICE){
  //     // In this case the ith Beverage is taken and add 1 count if it was not previously taken
  //     next_index = (next_index % MAX_PRICE);
  //     int new_count = current_pos_count.count;
  //     if(!current_pos_count.prev) new_count++;
  //     pos_and_bev_count take_this = {current_pos_count.bev_index,
  //                                   next_index,
  //                                   new_count,true};
  //     stack.push_back(take_this); // Add the new choice to stack
  //   }
  //
  // } while(!stack.empty());
  // return counter;
// }

void do_case(){
  int n,k,MAX_AMOUNT=0;
  //cout << "Start reading...\n";
  cin >> n >> k;
  vector<int> cost(n);
  vector<int> amount(n);
  for (int i = 0; i < n; i ++){
    cin >> cost[i];
    cin >> amount[i];
    MAX_AMOUNT = std::max(amount[i],MAX_AMOUNT);
  }
  memo= vecvec(n,vector<int>(k+1+MAX_AMOUNT,-1));
  memo_2= vecvec(n,vector<int>(k+1+MAX_AMOUNT,-2));
  memo_bev= vector<vecvec> (2,vecvec(n,vector<int>(k+1+MAX_AMOUNT,-1)));
  for (int i = 0; i < MAX_AMOUNT; ++i){
    cheapest_cost(n-1,k+MAX_AMOUNT-i,cost,amount); // Testing every case
  }
  vector<int> last_row;
  for ( int i = 0; i < MAX_AMOUNT;  ++i){
    last_row.push_back(memo[n-1][i+k]);
  }
  std::vector<int>::iterator min_index = std::min_element(last_row.begin(),last_row.end());
  int optimal_litre = min_index-last_row.begin()+k;
  cout << *min_index << " "; // This gives the lowest cost
  //cout << optimal_litre;
  cout << count_bev(0, n-1,optimal_litre) << std::endl;
}

int main (){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t ;
  while(t--){
    do_case();
  }
}
