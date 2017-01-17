//============================================================================
// Name        : hit.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <iomanip>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
int main() {
	int n;
	std::cin >> n;
	while (n != 0) {

		long p0x, p0y, p1x, p1y;
		std::cin >> p0x >> p0y >> p1x >> p1y;
		P p0(p0x, p0y), p1(p1x, p1y);
		R ray(p0, p1);
//		P p[2 * n];
//		S s[n];
		bool hit=false;
		int counter =0;
		for(int i = 0; i < n; i++) {
			std::cin >> p0x >> p0y >> p1x >> p1y;
			P pl(p0x, p0y), pr(p1x, p1y);
			S seg(pl,pr);
			if(CGAL::do_intersect(ray,seg)) {hit = true;counter =n- i; break;}
		}
		while(counter--){
		std::cin.ignore(1000,'\n');} // Skip Lines
		
		std::cout << (hit? "yes" : "no") << std::endl;
		std::cin >> n;
	}
	return 0;
}
