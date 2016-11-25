#include <iostream>
#include <cassert>
#include <vector>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef Gmpzf ET;
typedef Quadratic_program<double> Program;
typedef Quadratic_program_solution<ET> Solution;


void do_case(){
  int l,s,w;
  cin >> l >> s >> w;
  vector<P> lights(l),stamps(s);
  vector<S> wall(w);
  vector<K::FT> Ms(s);
  for (int i = 0; i < l; i++) {cin >> lights[i];}
  for (int i = 0; i < s; i++) {cin >> stamps[i]>>Ms[i];}
  for (int i = 0; i < w; i++) {
    P p1,p2;
    cin >> p1>>p2;
    wall[i]=S(p1,p2);
  }



  // now compute squared distances if availabe
  vector<vector < K::FT> > dis_squared(s,vector<K::FT> (l)); // sxl
  for ( int i = 0; i < s; i ++){
    for (int j = 0; j < l; j ++){
      S light_trace(stamps[i],lights[j]);
      dis_squared[i][j] = light_trace.squared_length();
      for (int k = 0; k < w; k++){
        if (do_intersect(light_trace,wall[k])){
          dis_squared[i][j] = -1;break;
        }
      }
    }
  }

  // Now compute if possible
  Program lp(SMALLER,true,1,true,1<<12);
  for(int i = 0; i < s ; i ++){
    lp.set_c(i,1);
    lp.set_b(i,Ms[i]);
    lp.set_b(i+s,-1);
    //cout << i << ": " << Ms[i]<<endl;
    for (int j = 0; j < l; j++){
      if (dis_squared[i][j]>0){
      lp.set_a(j,i,1.0/to_double(dis_squared[i][j]));
      lp.set_a(j,i+s,-1.0/to_double(dis_squared[i][j]));
      }
    }
  }

  Solution sol = solve_linear_program(lp,ET());
  //cout << sol;
  if (sol.is_infeasible()) cout << "no\n";
  else cout << "yes\n";
}
int main(){
  int t;
  cin >> t;
  while (t--){
    do_case();
  }
}
