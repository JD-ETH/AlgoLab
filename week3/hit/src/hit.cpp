//============================================================================
// Name        : hit.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <CGAL/Exact_predicates_inexact_constructions_kernel_with_sqrt.h>
#include <iostream>
#include <iomanip>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
int main() {
	int t;
	std::cin >> t;
	while (t != 0) {
		int n;
		std::cin >> n;
		long p0x, p0y, p1x, p1y;
		std::cin >> p0x >> p0y >> p1x >> p1y;
		P p0(p0x, p0y), p1(p1x, p1y);
		R ray(p0, p1);
//		P p[2 * n];
//		S s[n];
		bool hit=false;
		for(int i = 0; i < n; i++) {
			std::cin >> p0x >> p0y >> p1x >> p1y;
			P pl(p0x, p0y), pr(p1x, p1y);
			S seg(pl,pr);
			if(CGAL::do_intersect(ray,seg)) {hit = true;break;}
		}
		std::cout << (hit? "yes" : "no") << std::endl;
	}
	return 0;
}
