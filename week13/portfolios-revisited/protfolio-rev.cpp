#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <vector>

typedef CGAL::Gmpz ET; // Fraction
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main(){
  int n,m;
  std::cin >> n >> m;
  while (! (n==0 && m == 0)){
    //std::cout << " current n " << n << " current m " << m<< std::endl;
    std::vector<int> costs(n);
    std::vector<int> returns(n);
    std::vector<std::vector<int> > variances(n,std::vector<int>(n));
    double MAX_UNIT_RETURN= 0;
    for (int i = 0; i < n; i++){
      std::cin >> costs[i];
      std::cin >> returns[i];
      if((double)returns[i]/costs[i] > MAX_UNIT_RETURN){
        MAX_UNIT_RETURN = (double)returns[i]/costs[i];
      }
    }
    for (int i = 0; i < n; i ++){
      for (int j = 0; j < n ; j ++){
        std::cin >> variances[i][j];
      }
    }
    int investment;
    int risk;
    Program qp(CGAL::SMALLER, true, 0 , false,0);
    for(int i =0; i<n; i++){
      qp.set_a(i,0,(double)costs[i]);
      qp.set_a(i,1,(double)returns[i]);
    }
    for (int i = 0; i < n; i++){
      for (int j = 0; j <= i; j++){

          qp.set_d(i,j,2.0*(double)variances[i][j]); // Somehow only works when j < i

      }
    }
    qp.set_r(1,CGAL::LARGER);
    for (int q = 0; q < m; q++){
      std::cin >> investment >> risk;
      int max_return = investment* MAX_UNIT_RETURN;
      int min_return = 0;
      //std::cout << max_return<<std::endl;
      while(max_return != min_return){
        //std::cout << "Current Max: "<< max_return << " and min:" << min_return <<std::endl;
        int cur_return = (min_return+max_return+1)/2;

        qp.set_b(0,(double)investment);
        qp.set_b(1,(double)cur_return);



        Solution s = CGAL::solve_quadratic_program(qp,ET());

        if (!s.is_infeasible() && CGAL::to_double(s.objective_value()) <= risk ){ //possible
          min_return = cur_return;
          Solution::Variable_value_iterator opt =
                        s.variable_values_begin();
          //std::cout << " current risk total:" << CGAL::to_double(s.objective_value()) << std::endl;
          //for (int pp = 0; pp< 3; pp++){
          //   std::cout << CGAL::to_double(*opt) <<std::endl;
          //   opt++;
           //}
        }
        else {
          //std::cout << " current risk total:" << CGAL::to_double(s.objective_value()) << std::endl;
          max_return = cur_return-1;
        }

      }
      std::cout << min_return << std::endl;

    }
    std::cin >> n >> m;
}
  return 0;
}










// Input sequence: n,m,
// n lines of 2 int , cost and return
// n lines of covariances
// m lines o investors, ci and vi
// terminated by 00
