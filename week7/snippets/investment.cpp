#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>

// choose exact floating-point type
typedef CGAL::Gmpzf ET;

// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
  // read minimum expected return rate
  std::cout << "What is your desired expected return rate? ";
  double rho; std::cin >> rho;

  // by default, we have a QP with Ax >= b
  Program qp (CGAL::LARGER, true, 0, false, 0);

  // now set the non-default entries:
  const int sw = 0;
  const int cs = 1;

  // constraint on expected return: 0.1 sw + 0.51 cs >= rho
  qp.set_a(sw, 0, 0.1);
  qp.set_a(cs, 0, 0.51);
  qp.set_b(    0, rho);

  // strategy constraint: sw + cs = 1
  qp.set_a(sw, 1, 1);
  qp.set_a(cs, 1, 1);
  qp.set_b(    1, 1);
  qp.set_r(    1, CGAL::EQUAL); // override default >=

  // objective function: 0.09 sw^2 - 0.05 sw cs - 0.05 cs sw + 0.25 cs^2
  // we need to specify the entries of the symmetric matrix 2D, on and below the diagonal
  qp.set_d(sw, sw,  0.18); //  0.09 sw^2
  qp.set_d(cs, sw, -0.10); // -0.05 cs sw
  qp.set_d(cs, cs,  0.5);  //  0.25 cs^2

  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_quadratic_program(qp, ET());
  assert (s.solves_quadratic_program(qp));

  // output
  if (s.status() == CGAL::QP_INFEASIBLE) {
    std::cout << "Expected return rate " << rho << " cannot be achieved.\n";
  } else {
    assert (s.status() == CGAL::QP_OPTIMAL);
    Solution::Variable_value_iterator opt =
      s.variable_values_begin();
    CGAL::Quotient<ET> sw_fraction = *opt;
    CGAL::Quotient<ET> cs_fraction = *(opt+1);
    std::cout << "Minimum risk investment strategy:\n";
    std::cout << 100.0*CGAL::to_double(sw_fraction)
        << "%" << " into Swatch\n";
    std::cout << 100.0*CGAL::to_double(cs_fraction)
        << "%" << " into Credit Suisse\n";
    std::cout << "Risk = " << CGAL::to_double(s.objective_value()) << "\n";
  }
  return 0;
}
