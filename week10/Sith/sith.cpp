#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
using namespace boost;
using namespace std;
using namespace CGAL;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_iterator EdgeIt;


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>  Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Delaunay;
typedef Delaunay::Point Point;
typedef Delaunay::Edge_iterator  Edge_iterator;


bool solve(int k, vector<pair<Point,int> > & pts, K::FT r){
  //cout << "testing for k = " << k;
  Delaunay tri;
  K::FT r_squared = r * r;
  tri.insert(pts.begin()+k,pts.end());
  Graph G(pts.size()-k);
  for (Edge_iterator edit = tri.finite_edges_begin(); edit != tri.finite_edges_end(); edit++){
    if (tri.segment(*edit).squared_length()<= r_squared){
//      cout << tri.segment(*edit).squared_length() << ": ";
//      cout << r_squared << endl;
        add_edge(edit->first->vertex(tri.cw(edit->second))->info()-k,
                  edit->first->vertex(tri.ccw(edit->second))->info()-k,G);
        //cout << "Edge added";
    }
  }

  vector<int> component(num_vertices(G));
  int num = connected_components(G,&component[0]);
  vector<int> comps_count(num,0);
  for (int i= 0; i < component.size(); i++){
    comps_count[component[i]]++;
  }
  sort(comps_count.begin(),comps_count.end());

  return (comps_count.back()>=k);
}

void do_case(){
  //cout << "Start Reading \n";
  int n;
  K::FT r;
  cin >> n>>r;
  std::vector<std::pair<Point,int> > pts;
  for (int i = 0; i < n; i ++){
    int x,y;
    cin >> x >> y;
    pts.push_back(std::make_pair(Point(x,y),i));
  }



  int kmin, kmax;
  kmin = 1;
  kmax = n/2;

  while ( kmin != kmax){
    //cout << "kmin: "<< kmin << "kmax: " << kmax;
   int mid = kmin +  ((kmax-kmin+1)/2);
   bool capable = solve(mid,pts,r);
   if (capable) {
     //cout << "sucess"<< endl;
     kmin = mid;}
    else kmax = mid-1;
  }

  cout << kmin<< endl;
}


int main() {
  ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) {
		do_case();
	}
	return 0;
}
