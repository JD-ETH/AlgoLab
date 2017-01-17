#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <iostream>

 typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
 typedef CGAL::Delaunay_triangulation_2<K> delaunay_t;
 typedef delaunay_t::Vertex_handle Vertex_handle;
 double ceil_to_double(K::FT const & x)
 {
 double a = std::ceil(CGAL::to_double(x));
 while (a < x) a += 1;
 while (a-1 >= x) a -= 1;
 return a;
 }

 void test_case(int n)
 {
 std::vector<K::Point_2> old(n);
 for (std::size_t i = 0; i < n; ++i)
 {
 std::cin >> old[i];
 }


 delaunay_t trg;
 trg.insert(old.begin(), old.end());

 int m;
 std::cin >> m;
 while(m--){
   K::Point_2 pt;
   std::cin >> pt;
   Vertex_handle vertex = trg.nearest_vertex(pt);
   K::FT dis = CGAL::squared_distance(pt,vertex->point());
   std::cout << CGAL::to_double(dis) << "\n";
 }


 }


  int main()
  {
  std::ios_base::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(0);
  int n,m;
 while (std::cin >> n && n != 0) test_case(n);
  }
