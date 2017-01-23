#include <iostream>
#include <vector>
typedef std::vector<std::vector<int > > vecvec;

using std::cin;
using std::cout;

static vecvec memo;

// 0th 1th 2th 3th
// 2⁰ 2¹ 2²
bool is_feasible(int &a, int & f1, int &f0, int &w){ // a current, f1 current, f0 upper level
  bool even = true;
  for (int i = 0; i<w; i++){
    if (a & (1<<i) ) { // bitmask wants to put in tile in this level
      if (! (f0&(1<<i))) return false;
      if (! (f1&(1<<i)) ) return false;
      even = !even;
      // Impossible because was set 0 at this or upper level
    }
    else {
      if (!even) return false; // odd number of 1s
    }
  }

  return even;
}
inline int negate(int &a, int &w){
  int res = (1<<w)-a-1;
  return res;
}
inline int count_tiles(int &a, int &w){
  int counter = 0;
  for (int i = 0; i< w ; i++){
    if (a & (1<<i)) counter++;
  }
  //cout << counter;
  return (counter/2);
}
std::vector<int> generate_sons(int const & a, int &w){ // Set of children with 1 bit unset
  std::vector<int> new_son;
  for ( int i = 0; i < w; i++){
    if (1<<i & a) {
      new_son.push_back(a-(1<<i));
      }
    }
  //new_son.insert(0);

  return new_son;
}
int put_tiles(std::vector<int> & floor_mask, int row, int bit_mask,int &w){
  int res=0;
  if (memo[row][bit_mask] == -1){
    if (row <= 1) { // Nothing fits in first two rows
    }
    else if(bit_mask == 0){ //  mask = 0
      int ALL_ONES = 1 << w;
      ALL_ONES--;
      res = put_tiles(floor_mask,row-1,ALL_ONES,w);
    }
    else{
      //std::vector<int> sons = generate_sons(bit_mask,w);
      //int negated = negate(bit_mask,w);
      //cout << " for : " << row << " floor " << floor_mask[row] << " upper : " << floor_mask[row-1] << std::endl;
      if (is_feasible(bit_mask,floor_mask[row],floor_mask[row-1],w)){
        res = put_tiles(floor_mask,row-1, negate(bit_mask,w) ,w)+ count_tiles(bit_mask,w);
      }
      //for (std::vector<int>::iterator sit = sons.begin(); sit!= sons.end(); sit++){
        //int son = *sit; //cout << son << " ";
      for (int i = 0; i < w; i++){
        if (1<<i & bit_mask)
          res = std::max(res,put_tiles(floor_mask,row,bit_mask-(1<<i),w));
      }
    }
//
    memo[row][bit_mask] = res;
  }else{
    res = memo[row][bit_mask];
  }
  //cout << " for : " << row << " mask " << bit_mask << " res : " << res << std::endl;
  return res;
}
void do_case(){
  int h,w;
  int ignore;
  cin >> h >> w;
  if (w<4){
    for (int i = 0; i < (h*w); i ++) cin >> ignore;
    cout << 0 << std::endl;
  }
  else{
    w--; w--;
    vecvec floor(h,std::vector<int>(w,-1));
    std::vector<int> floor_mask(h);
    memo = vecvec(h,std::vector<int>(1<<w,-1));
    for (int i = 0; i < h; i++){
      int mask_i = 0;
      cin >> ignore;
      for (int j = 0; j < w; j ++){
        int free; // if 1, free
        cin >> free;
        floor[i][j] = free;
        mask_i += (free<<j);
      }
      cin >> ignore;
      floor_mask[i] = mask_i; // bit_mask for ith floor

    }
    cout << put_tiles(floor_mask, h-1, 0,w) << std::endl;
  }
}
int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--){
    do_case();
  }
}
