#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_data_structure_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <algorithm>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> vertex_t;
typedef CGAL::Triangulation_face_base_2<K> face_t;
typedef CGAL::Triangulation_data_structure_2<vertex_t,face_t> triangulation_t;
typedef CGAL::Delaunay_triangulation_2<K,triangulation_t> Delaunay;
typedef Delaunay::Vertex_handle Vhandle;
typedef Delaunay::Vertex_circulator Vcirc;
typedef Delaunay::Edge_iterator Edge_iterator;
typedef Delaunay::Vertex_iterator viterator_t;
typedef std::pair<K::Point_2,int> IPoint;
typedef boost::disjoint_sets_with_storage<> Uf; // Member

struct Edge{
  Edge(int u_, int v_, K::FT sql_) :u(u_),v(v_),sql(sql_) {}
  int u, v;
  K::FT sql;
};

inline bool operator<(const Edge& e, const Edge &f ) {return e.sql < f.sql;}

void handle_missions(){
  std::size_t n,m;
  double p;
  std::cin >> n >> m >> p;

  std::vector<IPoint> jammers; jammers.reserve(n);
  for (std::size_t i = 0; i < n ; ++i){
    int x,y;
    std::cin >> x >> y;
    jammers.push_back(IPoint(K::Point_2(x,y),i));
  }
  // Delaunay
  Delaunay trg;
  trg.insert(jammers.begin(), jammers.end());
  std::vector<Edge> edges;
  for (Edge_iterator edit = trg.finite_edges_begin(); edit != trg.finite_edges_end();edit++){
    edges.push_back(Edge(edit->first->vertex((edit->second+1)%3)->info(),
                        edit->first->vertex((edit->second+2)%3)->info(),
                        trg.segment(*edit).squared_length()));
  }
  std::sort(edges.begin(), edges.end());

  Uf ufp(n);
  typedef std::vector<Edge>::const_iterator ECI;
  for (ECI e = edges.begin(); e!= edges.end() && e->sql <= p; ++e)
    ufp.union_set(e->u,e->v);
  K::FT a=0;
  K::FT b=0;
  Uf ufa(n);
  Uf ufb(n);
  ECI ai = edges.begin();
  ECI bi = edges.begin();
  for (std::size_t i= 0; i < m; ++i){
    int x0,y0,x1,y1;
    std::cin >> x0>> y0 >> x1 >> y1;
    K::Point_2 p0(x0,y0),p1(x1,y1);
    Vhandle v0 = trg.nearest_vertex(p0);
    Vhandle v1 = trg.nearest_vertex(p1);
    K::FT d = 4* std::max(CGAL::squared_distance(v0->point(),p0),
                          CGAL::squared_distance(v1->point(),p1));
    if (d<= p && ufp.find_set(v0->info()) == ufp.find_set(v1->info())){
      std::cout << "y";
      if (d>b) b =d;
      for(; bi != edges.end() && ufb.find_set(v0->info())!=ufb.find_set(v1->info()); ++bi){
        ufb.union_set(bi->u,bi->v); // Minimum possible radius
      }
    }
    else{
        std::cout << "n";
    }
    if (d> a) a = d;
    for (; ai!= edges.end()&& ufa.find_set(v0->info())!= ufa.find_set(v1->info());++ai){
      ufa.union_set(ai->u,ai->v);  // it must connect everything
      }
    }
  if (ai!=edges.begin() && (ai-1)->sql>a) a=(ai-1)->sql;
  if (bi!=edges.begin() && (bi-1)->sql>b) b=(bi-1)->sql;
  std::cout << "\n" << a << "\n" << b << "\n";
  }
  int main(){
  std::ios_base::sync_with_stdio(false);
  std::cout<<std::setiosflags(std::ios::fixed)<<std::setprecision(0);
  int t;
  std::cin >> t;
  while(t--){
    handle_missions();
  }

}
