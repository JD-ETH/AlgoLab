
#include <iostream>
#include <cassert>
#include <vector>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>

using namespace std;
using namespace CGAL;

typedef Gmpzf ET;
typedef Quadratic_program<double> Program;
typedef Quadratic_program_solution<ET> Solution;
static vector<int> cost,reward;
static vector<vector<int> > covariance;
static int n,m,C,R,V;
int main(){
	while(cin >> n && n != 0&& cin >> m){
		cost.resize(n);
		reward.resize(n);
		covariance=vector< vector<int > >(n,vector<int>(n));
		for (int i = 0; i < n ; i++){
			cin>>cost[i];
			cin>>reward[i];
		}
		for (int i = 0; i < n;i ++){
			for (int j = 0; j < n; j ++){
				cin >> covariance[i][j];
			}
		}

		Program qp (SMALLER,true,0,false,0);
		// Now constraints
		// 0th equation Sum Cost small then C
		// 1th equation Sum Return bigger then given

		for (int i = 0; i < n; i++){
			qp.set_a(i,0,cost[i]);
			qp.set_a(i,1,-reward[i]);
			for (int j=i; j < n; j++){
				qp.set_d(j,i,2*covariance[i][j]);
			}

		}

		while(m--){
			cin >> C >> R >> V;
			qp.set_b(0,C);
			qp.set_b(1,-R);
			Solution s = solve_quadratic_program(qp,ET());
			assert(s.solves_quadratic_program(qp));
			if (s.is_infeasible()) cout << "No.\n";
			else if ( to_double(s.objective_value())>V) cout << "No.\n";
			else cout <<"Yes.\n";
			}
		}
}
