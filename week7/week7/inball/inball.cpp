#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>


using namespace std;
using namespace CGAL;

typedef Gmpz ET;
typedef Quadratic_program<double> Program;
typedef Quadratic_program_solution<ET> Solution;

static vector<int> bs;
static vector<vector <int > > as;
static vector<int> normsquare;
static int n,d;

int main(){
  while (cin >> n && n != 0 && cin >> d){
    bs.resize(n);

    as = vector< vector<int> > (n, vector<int>(d));
    normsquare.clear();normsquare.resize(n);
    for (int i = 0; i < n; i ++){
      int norm= 0;
      for (int j = 0; j < d ; j ++){
        cin >> as[i][j];
        norm += (as[i][j]*as[i][j]);
      }
      cin >> bs[i];
      normsquare[i] = round(sqrt((double)norm));
    }

    Program lp(SMALLER,false,0,false,0);
    // Now linear constraints
    // d*norm+aixi<=bi
    lp.set_l(d,true,0);

    for(int i = 0; i < n ; i ++){
      lp.set_a(d,i,normsquare[i]);
      lp.set_b(i,bs[i]);
      for (int j = 0; j < d ; j ++){
        lp.set_a(j,i,as[i][j]);
      }
    }

    // Assign the final function
    lp.set_c(d,-1);
    // Solve
    Solution s = solve_linear_program(lp,ET());
    assert(s.solves_linear_program(lp));
    if (s.is_infeasible()) cout << "none\n";
    else if ( s.is_unbounded()) cout << "inf\n";
    else cout  << (int)floor(to_double(-s.objective_value()))<< "\n";
  }

}
