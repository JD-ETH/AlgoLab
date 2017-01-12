#include <iostream>
#include <cassert>
#include <vector>
#include <math.h>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef std::vector<std::vector<int > > vecvec;
bool qp_solvable(int dim, vecvec const & hs, vecvec const & ts){
  Program lp(CGAL::LARGER,false,0,false,0);
  for (int i = 0; i < hs.size();i++){ //healthy
    int ind_h = 0;
    for (int xi = 0; xi <= dim; xi++){
      for (int yi = 0; yi <= dim; yi++){
        for (int zi = 0; zi <= dim; zi++){
          if (xi+yi+zi <= dim){
            lp.set_a (ind_h,i,pow(hs[i][0],xi)*pow(hs[i][1],yi)*pow(hs[i][2],zi));
            ind_h++;
          }
          else break;
        }
      }
    }
    //lp.set_a (ind_h,i,-1);
    lp.set_b (i,1);

  }
  int sizeh = hs.size();
  for (int i = 0; i < ts.size();i++){ // tumor
    int ind_t = 0;
    for (int xi = 0; xi <= dim; xi++){
      for (int yi = 0; yi <= dim; yi++){
        for (int zi = 0; zi <= dim; zi++){
          if (xi+yi+zi <= dim){
            lp.set_a (ind_t,i+sizeh,pow(ts[i][0],xi)*pow(ts[i][1],yi)*pow(ts[i][2],zi));

            ind_t++;
          }
          else break;
        }
      }
    }
    //lp.set_a (ind_t,i,-1);
    lp.set_r(i+sizeh,CGAL::SMALLER);
    lp.set_b (i+sizeh,0);
    lp.set_c(ind_t,-1);
  }

// Do you need objective?
  Solution s = CGAL::solve_linear_program(lp, ET());
  return !s.is_infeasible();

}

int do_case(){
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

  int dmin = 0 ; int dmax = 31; int dmid;
  while (dmin != dmax){
    //std::cout << "Solving for " << dmin << " and" << dmax << std::endl;
    dmid = (dmin+dmax)/2;
    if (qp_solvable(dmid,hs,ts)){
      dmax = dmid;
      //std::cout << "Solvable for " << dmid << std::endl;
    }

    else dmin = dmid+1;
  }
  if (dmin < 31) std::cout << dmin << std::endl;
  else std::cout << "Impossible!" << std::endl;
}
int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  while (t--) {
    do_case();
  }
}
