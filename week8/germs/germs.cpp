#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef Triangulation_vertex_base_with_info_2<K::FT,K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>  Tds;
typedef Delaunay_triangulation_2<K,Tds> Delaunay;
typedef Delaunay::Edge_iterator EdIt;
typedef Delaunay::Vertex_iterator VtIt;
typedef Delaunay::Vertex_handle Vertex_handle;
typedef Delaunay::Point Point;

double ceil_to_double(EK::FT const & x){
  double a = std::ceil(CGAL::to_double(x));
  while (a<x) a+=1;
  while (a-1 >= x) a -=1;
  return a;
}
EK::FT S_to_hrs(EK::FT const &S){
  return CGAL::sqrt((CGAL::sqrt(S)-1)/2);
}

K::FT l,b,r,t;
void do_case(int n){
  cin >> l >> b >> r >> t;
  vector<pair<Point,K::FT> > bact(n);
  vector<K::FT > die_at;
  die_at.reserve(n);
  // Delaunay with info on vertices
  for (int i = 0; i < n; i++) {
    K::FT x, y;
    cin >> x >> y;
    K::FT to_frame= std::min(t-y,std::min( y-b,std::min(x-l,r-x)));
    //cout << to_frame;
    bact[i] = make_pair(Point(x,y),4*to_frame*to_frame);
  }
  Delaunay tri;
  tri.insert(bact.begin(),bact.end());

  // Finite Edges
  for (EdIt edit = tri.finite_edges_begin();
          edit!=tri.finite_edges_end(); edit++){
            Vertex_handle vi = edit->first->vertex(tri.cw(edit->second));
            Point const & gi = vi->point();
            K::FT & info_gi = vi->info();

            Vertex_handle vj = edit->first->vertex(tri.ccw(edit->second));
            Point const & gj = vj -> point();
            K::FT & info_gj = vj->info();

            K::FT squared_edge = CGAL::squared_distance(gi,gj);
            info_gi = std::min(info_gi,squared_edge);
            info_gj = std::min(info_gj,squared_edge);

  }

  // Select all minimum

  for (VtIt vtit = tri.finite_vertices_begin(); vtit!=tri.finite_vertices_end();vtit++){
    die_at.push_back(vtit->info());

  }

  std::sort(die_at.begin(),die_at.end());
  EK::FT first = S_to_hrs(EK::FT(die_at[0]));
  EK::FT mid = S_to_hrs(EK::FT(die_at[n/2]));
  EK::FT last = S_to_hrs(EK::FT(die_at[n-1]));
  cout << ceil_to_double(first) << " " << ceil_to_double(mid) << " " << ceil_to_double(last) << endl;
}
int main(){
  ios_base::sync_with_stdio(false);
  int n;
  while (cin >> n && n!= 0){
    do_case(n);
  }
}
