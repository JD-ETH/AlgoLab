//============================================================================
// Name        : TheeV.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Circle_2.h>
#include <iostream>
#include <math.h>
#include <limits>
using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef CGAL::Circle_2<K> Circle;
typedef K::Point_2 P;

bool covered(vector<P> & v, long long r_square) {
	vector<P> v_out;
	K::FT r_sq = r_square;
	Circle circ(v[0], r_sq, CGAL::CLOCKWISE);
	for (int i = 1; i < v.size(); i++) {
		if (circ.has_on_unbounded_side(v[i])) {
			v_out.push_back(v[i]);
		}
	}
//	cout << "Number of points still outside" << v_out.size();
	Min_circle mc(v_out.begin(), v_out.end(), true);
	Traits::Circle c = mc.circle();
	return (r_sq >= c.squared_radius());

}

void do_case() {
	// read input
	int n;
	cin >> n;
	vector<P> v(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		v[i] = P(x, y);
	}

	long long rmin = 0; // initialization
	long long rmax = 5547713893634347; // 2^50
//	cout << rmax;
	while (rmin != rmax) {
		long long r = (rmin + rmax) / 2;
//		cout << "Current r" << r ;
		if (covered(v, r)) {
//			cout << "Too big r = " << r << "rmin = " << rmin;
			rmax = r;
		} else {
//			cout << "Too small r = " << r<<  "rmax = " << rmax << "rmin = " << rmin;
			rmin = r + 1;
		}
	}

	cout << rmin << endl;
}
int main() {
	int t;
	cin >> t;
	while (t--) {
		do_case();
	}
	return 0;
}
