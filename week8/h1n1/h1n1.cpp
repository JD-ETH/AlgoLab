  #include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
  #include <CGAL/Delaunay_triangulation_2.h>
  #include <vector>
  #include <map>
  #include <stack>
  #include <iostream>

   typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
   typedef CGAL::Delaunay_triangulation_2<K> delaunay_t;
   typedef delaunay_t::Edge_iterator Edge_iterator;
   typedef delaunay_t::Face_iterator Face_iterator;
   typedef delaunay_t::Vertex_handle Vertex_handle;
   typedef delaunay_t::Edge Edge;
   typedef delaunay_t::Face_handle Face_handle;
   typedef K::Point_2 Point;
   typedef K::Segment_2 Segment;
   typedef K::FT FT;
   typedef std::map<Edge,FT> EdgeLenthMap;


   bool DFS(delaunay_t & tri, Face_handle &fit, long dis, std::map<Face_handle,int>& visit_map, int i){


       for (int e = 0; e < 3; ++e) { // all three edges
         //FT edge_len = length_map[std::make_pair(cur,e)];
           // Account for the same edge from other side!
           FT edge_len = tri.segment(fit,e).squared_length();
           //std::cout << edge_len;
         if (edge_len >= FT(dis)) {
           Face_handle f_neigh = fit -> neighbor(e);
           if (visit_map[f_neigh] == i){
           //std::cout << e << "Visited \n";
            continue;}
           if (tri.is_infinite(f_neigh)) {
             //std::cout << "escaped \n";
             return true;}
           visit_map[f_neigh] =i;
           if(DFS(tri,f_neigh,dis,visit_map,i)) return true;

          }
     }
     return false;
   }


   void test_case(int n){
     std::vector<Point> infected(n);
     for (std::size_t i = 0; i < n; ++i)
     {
     std::cin >> infected[i];
     }
     int m;
     std::cin >> m;
     std::vector<Point> query(m);
     std::vector<long> ds(m);
     for (std::size_t i = 0; i < m; ++i)
     {
     std::cin >> query[i];
     std::cin >> ds[i];
     }

     delaunay_t grid;
     grid.insert(infected.begin(),infected.end());

     std::map<Face_handle,int> visit_map;
     for (Face_iterator fit = grid.faces_begin();
          fit != grid.faces_end(); fit ++){
       visit_map[fit] = -1;
     }
     //EdgeLenthMap edge_len_map = get_edge_dis(grid);
     for (std::size_t i = 0; i < m; ++i){
       //determine(grid,edge_len_map, query[i],ds[i]);
       Vertex_handle vt = grid.nearest_vertex(query[i]);
       FT d = CGAL::squared_distance(query[i],vt->point()); // From current to closest
       if (d < FT(ds[i])) {
         std::cout << "n";
         continue;
       }

       Face_handle f_begin = grid.locate(query[i]);
       visit_map[f_begin] = i;

       if (grid.is_infinite(f_begin) || DFS(grid, f_begin,4*ds[i],visit_map,i+1)) std::cout << "y";
       else std::cout << "n";
     }


     std::cout << std::endl;
   }
   int main()
   {
   std::ios_base::sync_with_stdio(false);

   int n;
  while (std::cin >> n && n != 0) test_case(n);
   }
