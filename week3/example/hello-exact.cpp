#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <iostream>
#include <iomanip>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;

int main()
{
  K::Point_2 p(2,1), q(1,0), r(-1,-1);
  K::Line_2 l(p,q);
  K::FT d = sqrt(CGAL::squared_distance(r,l));
  std::cout << CGAL::to_double(d) << std::endl;
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2) 
	    << CGAL::to_double(d) << std::endl;
}
