#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
 #include <CGAL/Delaunay_triangulation_2.h>
 #include <vector>
 #include <iostream>

 typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
 typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;

 double ceil_to_double(EK::FT const & x)
 {
 double a = std::ceil(CGAL::to_double(x));
 while (a < x) a += 1;
 while (a-1 >= x) a -= 1;
 return a;
 }

 void test_case(int n)
 {
 std::vector<IK::Point_2> graypes(n);
 for (std::size_t i = 0; i < n; ++i)
 {
 std::cin >> graypes[i];
 }

 typedef CGAL::Delaunay_triangulation_2<IK> delaunay_t;
 delaunay_t trg;
 trg.insert(graypes.begin(), graypes.end());

 IK::FT min_squared_distance = std::numeric_limits<IK::FT>::max();
 for (auto e = trg.finite_edges_begin(); e != trg.finite_edges_end(); ++e)
 {
 min_squared_distance = std::min(
 min_squared_distance,
 trg.segment(*e).squared_length());
 }
 EK::FT time_cs = 50 * CGAL::sqrt(EK::FT(min_squared_distance));

 std::cout << ceil_to_double(time_cs) << "\n";
 }

 int main()
 {
 std::ios_base::sync_with_stdio(false);
 int n;
while (std::cin >> n && n != 0) test_case(n);
 }
