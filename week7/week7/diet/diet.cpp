#include <iostream>
#include <cassert>
#include <vector>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;
using namespace CGAL;

typedef Gmpzf ET;
typedef Quadratic_program<int> Program;
typedef Quadratic_program_solution<ET> Solution;
static vector<int> min_nutr,max_nutr,price;
static vector<vector<int> > food;
static int n,m;
int main(){
	while(cin >> n && n != 0&& cin >> m){
		min_nutr.resize(n);
		max_nutr.resize(n);
		price.resize(m);
		food=vector< vector<int > >(m,vector<int>(n));
		for (int i = 0; i < n ; i++){
			cin>>min_nutr[i];
			cin>>max_nutr[i];
		}
		for (int i = 0; i < m;i ++){
			cin >> price[i];
			for (int j = 0; j < n; j ++){
				cin >> food[i][j];
			}
		}

		Program qp (LARGER,true,0,false,0);
		// Now constraints
		for (int i = 0; i < m; i++){
			//qp.set_a(i,0,1);
			qp.set_c(i,price[i]);
			for (int j=0; j < n; j ++){
				// Now for every nutrients
				qp.set_a(i,j,food[i][j]);
				qp.set_a(i,j+n,-food[i][j]);
			}

		}
		//qp.set_b(0,1);
		//qp.set_r(0,EQUAL);
		for (int j = 0; j < n; j ++){
			qp.set_b(j,min_nutr[j]);
			qp.set_b(j+n,-max_nutr[j]);
		}

		Solution s = solve_linear_program(qp,ET());
		assert(s.solves_linear_program(qp));
		if (s.is_infeasible()) cout << "No such diet.\n";
		//else cout <<(int) to_double(s.objective_value()) << endl;
		else cout <<(int) s.objective_value() << endl;
		}
}
