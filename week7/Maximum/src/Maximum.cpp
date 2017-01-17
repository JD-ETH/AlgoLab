//============================================================================
// Name        : Maximum.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;
using namespace CGAL;

typedef Gmpz ET;
typedef Quadratic_program<int> Program;
typedef Quadratic_program_solution<ET> Solution;
void do_case2(int & a, int& b){
	Program qp(LARGER,false,0,false,0);
	// constraints
	const int X=0;
	const int Y=1;
	const int Z_sq=2;
	qp.set_u(X,true,0);
	qp.set_u(Y,true,0);
	qp.set_l(Z_sq,true,0);
	qp.set_a(X,0,1);
	qp.set_a(Y,0,1);
	qp.set_b(0,-4);
	qp.set_a(X,1,4);
	qp.set_a(Y,1,2);
	qp.set_a(Z_sq,1,1);
	qp.set_b(1,-a*b);
	qp.set_a(X,2,-1);
	qp.set_a(Y,2,1);
	qp.set_b(2,-1);

	// Objective
	qp.set_d(X,X,2*a);
	qp.set_d(Y,X,0);
	qp.set_d(Z_sq,Z_sq,2);
	qp.set_c(Y,b);

	// Solve
	Solution s = solve_quadratic_program(qp,ET());
	assert (s.solves_quadratic_program(qp));

	// Output
	if (s.is_infeasible()) {
		cout << "no\n";
	}
	else if (s.is_unbounded()) cout << "unbounded\n";
	else {
		cout << (int)ceil(to_double((s.objective_value()))) << endl;
	}



}
void do_case1(int & a, int& b){
	Program qp(SMALLER,true,0,false,0);
	// constraints
	const int X=0;
	const int Y=1;
	qp.set_a(X,0,1);
	qp.set_a(Y,0,1);
	qp.set_b(0,4);
	qp.set_a(X,1,4);
	qp.set_a(Y,1,2);
	qp.set_b(1,a*b);
	qp.set_a(X,2,-1);
	qp.set_a(Y,2,1);
	qp.set_b(2,1);

	// Objective
	qp.set_d(X,X,2*a);
	qp.set_d(Y,X,0);
	qp.set_c(Y,-b);

	// Solve
	Solution s = solve_quadratic_program(qp,ET());
	assert (s.solves_quadratic_program(qp));

	// Output
	if (s.is_infeasible()) {
		cout << "no\n";
	}
	else if (s.is_unbounded()) cout << "unbounded\n";
	else {
		cout << (int)to_double((-s.objective_value()) )<< endl;
	}



}
int main() {
	int p,a,b ;
	while (cin >> p && p != 0 && cin >> a >> b){
		if (p == 1){
			do_case1(a,b);
		}
		else do_case2(a,b);
	}
	return 0;}
