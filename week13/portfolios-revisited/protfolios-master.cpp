#include <iostream>
#include <cstdio>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <vector>

using namespace std;

#ifdef CGAL_USE_GMP

#include <CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET;

#else

#include <CGAL/MP_Float.h>

typedef CGAL::MP_Float ET;

#endif

// program and solution types

typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
  for (;;) {
    int n, m;
    cin >> n >> m;

    if (!n && !m) {
      return 0;
    }

    Program qp(CGAL::LARGER, true, 0, false, 0);

    vector<int> cost(n), ret(n);
    for (int i = 0; i < n; i++) {
      cin >> cost[i] >> ret[i];

      qp.set_a(i, 0, (double)ret[i] );
      qp.set_a(i, 1,  (double)cost[i]);
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int val;

        cin >> val;

        if (j <= i) {
          qp.set_d(i, j, 2 * ((double)val ));
        }
      }
    }

    for (int i = 0; i < m; i++) {
      int c, v;

      cin >> c >> v;

      qp.set_b(1, c);
      qp.set_r(1, CGAL::SMALLER);

      int li = 0, ls = 1000000;
      int sol;
      while (li <= ls) {
        std::cout << "Current Max: "<< ls << " and min:" << li <<std::endl;
        int cur = (li + ls) / 2;

        qp.set_b(0, cur);

        Solution s = CGAL::solve_quadratic_program(qp, ET());

        if (s.is_infeasible() || CGAL::to_double(s.objective_value()) > v) {
          ls = cur - 1;
          std::cout << " current risk total:" << CGAL::to_double(s.objective_value()) << std::endl;
        } else {
          std::cout << " current risk total:" << CGAL::to_double(s.objective_value()) << std::endl;
          li = cur + 1;
          sol = cur;
        }
      }

      cout << sol << "\n";
    }
  }

  return 0;
}
