#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<std::vector<int> > vecvec;
typedef std::vector<std::pair<int,int> > vecpair;

vecvec memo;
int k,s,m;
struct CommandCenter {
  int id;
  int num_sons;
  std::vector<int> controls;
  std::vector<vecpair> external_control;
  vecpair internal_control;
};
inline int get_max_allowed(vecpair& external_control_next_cc, int state_parent) {
  int max_allowed = (1<<s)-1;
  for (int i = 0; i<external_control_next_cc.size(); i++){
    if (state_parent & (1 << external_control_next_cc[i].first)){
      max_allowed &= ~(1<<(external_control_next_cc[i].second)); // remove ith
    }
  }
  return max_allowed;
}
inline int is_allowed_or_count(vecpair& internal_control, int state){
  for (int i = 0 ; i < internal_control.size(); i++){
    if ((state & (1<<internal_control[i].first)) && (state & (1<<internal_control[i].second))){
      return -1;
    }
  }
  int counter = 0;
  for (int i = 0; i < s; i++){
    if (state & (1<<i)){
      counter ++;
    }
  }

  return counter;
}
inline bool is_subset(int & a, int & b){
  bool isvalid = true;
  for (int i = 0; i<s; i ++){
    if ((1<<i) & a) { // if the ith bit of a is set
      if (!((1<<i) & b)) {
        //std::cout << a << " " << b;
        isvalid = false;
      }
    }
  }
  return isvalid;
}
int solve(int cc_id, int max_allowed, std::vector<CommandCenter> & commandcenters){
    int res=0;

    if (memo[cc_id][max_allowed] == -1){

      for (int i = 0; i < (1<<s); i++){
        if (is_subset(i,max_allowed)){
        //if (commandcenters[cc_id].num_sons == 0){
          //std::cout << "Examine " << i << "from " << max_allowed<< "At CC " << cc_id << std::endl;
        //}
          int count_trooper = is_allowed_or_count(commandcenters[cc_id].internal_control,i);
          if (count_trooper < 0){
            continue;
          }
          int cur_res = count_trooper;
          if (commandcenters[cc_id].num_sons == 0){ // reached the leaf

            res = std::max(res,cur_res);
            continue;
          }
          for (int child = 0; child < commandcenters[cc_id].num_sons; child++){
            int cc_son_id = commandcenters[cc_id].controls[child];
            int son_max = get_max_allowed(commandcenters[cc_id].external_control[child],i);
            //std::cout << "for " << i << " The maximum son would have " << son_max << std::endl;

            //std::cout << "CC son ID:" << cc_son_id << " state for son: "<< son_max << "under " << next_state<<std::endl;
            cur_res+=solve(cc_son_id,son_max,commandcenters);
            //std::cout << "current result of cc: " << cc_son_id << " son_max" << son_max << " res " << cur_res << std::endl;
          }

          res = std::max(res,cur_res);
        }
      }
      //std::cout << "CC ID:" << cc_id << " current state: "<< max_allowed << std::endl;
      //std::cout <<  res << std::endl;
      memo[cc_id][max_allowed] = res;
    }
    else {
      res = memo[cc_id][max_allowed] ;
    }
    return res;
}



void do_case(){
  std::cin >> k >> s >> m;
  std::vector<CommandCenter> commandcenters(k);

  int take_all = (1<<s) -1;
  memo = vecvec(k,std::vector<int>(take_all+1,-1));
  int u,v,h;
  for (int i = 0; i < m ; i++){
    std::cin >> u >> v >> h;
    int x,y;
    if (u ==v ){
      commandcenters[u].internal_control.reserve(h);
      for (int j = 0; j < h ; j ++){
        std::cin >> x >> y ;
        commandcenters[u].internal_control.push_back(std::make_pair(x,y));
      }
    }
    else {
      commandcenters[u].controls.push_back(v);
      vecpair control_to_one_cc(h);
      for (int j = 0; j < h; j++){
        std::cin >> x >> y;
        control_to_one_cc[j]= std::pair<int,int>(x,y);
      }
      commandcenters[u].external_control.push_back(control_to_one_cc);
      commandcenters[u].num_sons++;
    }
  }
  std::cout << solve(0,take_all,commandcenters) << std::endl;
  // Finish reading now

}

int main(){
  std::ios_base::sync_with_stdio(false);
  int T;
  std::cin>>T;
  while (T--){
    do_case();
  }
  return 0;
}
