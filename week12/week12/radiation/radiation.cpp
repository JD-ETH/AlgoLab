#include <iostream>
#include <cassert>
#include <vector>
#include <math.h>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>

// choose exact integral type
typedef CGAL::Gmpzf ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef std::vector<std::vector<int > > vecvec;
bool qp_solvable(int dim, vecvec const & hs, vecvec const & ts){
  Program lp(CGAL::LARGER,false,0,false,0);
  for (int i = 0; i < hs.size();i++){ //healthy
    int ind_h = 0;
    for (int xi = 0; xi <= dim; xi++){
      double powx = pow(hs[i][0],xi);
      for (int yi = 0; yi <= dim; yi++){
        double powy = pow(hs[i][1],yi);
        for (int zi = 0; zi <= dim; zi++){
          if (xi+yi+zi <= dim){
            lp.set_a (ind_h,i,powx*powy*pow(hs[i][2],zi));
            ind_h++;
          }
          else break;
        }
      }
    }
    //lp.set_a (ind_h,i,1);
    lp.set_b (i,1);

  }
  int sizeh = hs.size();
  for (int i = 0; i < ts.size();i++){ // tumor
    int ind_t = 0;
    for (int xi = 0; xi <= dim; xi++){
      double powx = pow(ts[i][0],xi);
      for (int yi = 0; yi <= dim; yi++){
        double powy = pow(ts[i][1],yi);
        for (int zi = 0; zi <= dim; zi++){
          if (xi+yi+zi <= dim){
            lp.set_a (ind_t,i+sizeh,powx*powy*pow(ts[i][2],zi));

            ind_t++;
          }
          else break;
        }
      }
    }
    //lp.set_a (ind_t,i,-1);
    lp.set_r(i+sizeh,CGAL::SMALLER);
    lp.set_b (i+sizeh,-1);
    lp.set_c(ind_t,-1);
  }

// Do you need objective?
  CGAL::Quadratic_program_options options;
  options.set_pricing_strategy(CGAL::QP_BLAND);
  Solution s = CGAL::solve_linear_program(lp, ET(),options);
  return !s.is_infeasible();

}

void do_case(){
  int h,t;
  std::cin >> h >> t;
  vecvec hs(h,std::vector<int>(3,0));
  vecvec ts(t,std::vector<int>(3,0));

  for (int i = 0; i < h ; i++){
    for (int j = 0; j < 3; j++){
      std::cin >> hs[i][j];
    }
  }
  for (int i = 0; i < t ; i++){
    for (int j = 0; j < 3; j++){
      std::cin >> ts[i][j];
    }
  }
  int dmin = 0 ; int dmax = 1; int dmid;
  while(!qp_solvable(dmax,hs,ts) && dmax <= 30){
    dmin = dmax;
    dmax *= 2;
  }
  if (dmax > 30 && !qp_solvable(30,hs,ts)) {
    std::cout << "Impossible!"<<std::endl;
    return;
  }
  dmax = std::min(30,dmax);
  while (dmin != dmax){
    //std::cout << "Solving for " << dmin << " and" << dmax << std::endl;
    dmid = (dmin+dmax)/2;
    if (qp_solvable(dmid,hs,ts)){
      dmax = dmid;
      //std::cout << "Solvable for " << dmid << std::endl;
    }

    else dmin = dmid+1;
  }
  std::cout << dmin << std::endl;
  }
int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  while (t--) {
    do_case();
  }
  return 0;
}
