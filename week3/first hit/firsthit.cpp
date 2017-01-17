//============================================================================
// Name        : hit.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <limits>
//#include <iomanip>
//#include <stdexcept>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef std::result_of<K::Intersect_2(K::Ray_2,K::Segment_2)>::type IT;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

double floor_to_double(const K::FT& x)
{
 double a = std::floor(CGAL::to_double(x));
 while (a > x) a -= 1;
 while (a+1 <= x) a += 1;
 return a;
}

void shorten_segment(K::Segment_2& s, const IT& o) {
	if ( const K::Point_2 *p = boost::get<K::Point_2>(&*o))
		s = K::Segment_2(s.source(), *p);
	else if (const K::Segment_2* t = boost::get<K::Segment_2>(&*o))
		if (CGAL::collinear_are_ordered_along_line
			(s.source(), t->source(), t->target()))
		  s= K::Segment_2(s.source(), t->source());
		else
		  s=K::Segment_2(s.source(),t->target());
	else
	     throw std::runtime_error("StrangeSegmentIntersection.");
}
int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
	int n;
	std::cin >> n;
  std::vector<S> segs;
  segs.reserve(n);
	while (n != 0) {
    segs.clear();
		long p0x, p0y, p1x, p1y;
		std::cin >> p0x >> p0y >> p1x >> p1y;
		P p0(p0x, p0y), p1(p1x, p1y);
		R ray(p0, p1);
		S rc(p0,p0);

		for(int i = 0; i < n; i++) {
			std::cin >> p0x >> p0y >> p1x >> p1y;
			P pl(p0x, p0y), pr(p1x, p1y);
			S s(pl,pr);
			segs.push_back(s);
		}
		std::random_shuffle(segs.begin(),segs.end());

// First find some hit
		int i = 0;
		for (; i < n; ++i)
			if (CGAL::do_intersect(segs[i],ray)){
				shorten_segment(rc,CGAL::intersection(segs[i],ray));
			break;
			}
			if (i == n) {std::cout << "no\n";goto next;}

		while ( ++i < n)
			if (CGAL::do_intersect(segs[i],rc))
				shorten_segment(rc,CGAL::intersection(segs[i],ray));
		std::cout << floor_to_double(rc.target().x()) << " " <<
				floor_to_double(rc.target().y()) << std::endl;
			next:
			std::cin >> n;
	}
	return 0;
}
