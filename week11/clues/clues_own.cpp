// Part1 inclusion
#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_data_structure_2.h>

// Part2 typedef, using
typedef std::pair<int,bool> Vert_info;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<Vert_info,K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Delaunay;
typedef Delaunay::Point Point;
typedef Delaunay::Vertex_handle Vertex_handle;
typedef Delaunay::Edge_iterator Edge_iterator;
typedef Delaunay::Vertex_circulator Vertex_circulator;
typedef Delaunay::Vertex_iterator Vertex_iterator;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

// Part3 Function def

bool has_intersection(Delaunay const & trg, K::FT const & rr);
// Testing whether there is an edge in delaunay smaller then given distance

bool try_two_color(Delaunay const & trg, K::FT const & rr);
// 2-coloring the constructed delaunay triangulation


void do_case();
// reading input, constructing delaunay, give tested output

// Part4 Function body
bool has_intersection(Delaunay const & trg, K::FT const & rr){
  for(Edge_iterator edit = trg.finite_edges_begin(); edit != trg.finite_edges_end(); ++edit){
    if (trg.segment(*edit).squared_length() < rr ) return true;
  }
  return false;
}

bool try_two_color(Delaunay const & trg, K::FT const & rr) {
  // return whether its possible to do the two color
  for (Vertex_iterator vit = trg.finite_vertices_begin(); vit != trg.finite_vertices_end(); ++vit){
    vit->info().first = 0;
    vit->info().second = false;
    // initialize
  }
  int components=0;
  Delaunay trg1,trg2;
  for (Vertex_iterator vit = trg.finite_vertices_begin(); vit != trg.finite_vertices_end(); ++vit){
    if (vit->info().first == 0) {
      vit->info().first = ++components;
      vector<Vertex_handle> stack_vhdl(1,vit);
      do {
        Vertex_handle vhdl = stack_vhdl.back();
        stack_vhdl.pop_back();
        Vertex_circulator vcirc = trg.incident_vertices(vhdl);
        do if (!trg.is_infinite(vcirc) && CGAL::squared_distance(vhdl->point(),vcirc->point()) <= rr){
          if(vcirc->info() == vhdl->info()) return false;
          if(vcirc->info().first == 0){
            stack_vhdl.push_back(vcirc);
            vcirc->info().first = components;
            vcirc->info().second = !vhdl->info().second; // Reverse color, greedy
          }
        } while(++vcirc != trg.incident_vertices(vhdl));
      } while(!stack_vhdl.empty());
    }
    if(vit->info().second) trg1.insert(vit->point());
    else trg2.insert(vit->point());
  }
  return (!has_intersection(trg1,rr) && !has_intersection(trg2,rr));
}

void do_case(){
  int n,m; K::FT rr;
  cin >> n >> m >> rr;
  rr *= rr;
  vector<Point> stations(n);
  for (int i = 0; i < n; ++i){
    cin >> stations[i];
  }
  Delaunay delaunay;
  delaunay.insert(stations.begin(), stations.end());
  bool success = try_two_color(delaunay, rr);
  for (int i = 0; i < m; ++i){
    Point holmes, watson;
    cin >> holmes >> watson;
    if (success){
      if (CGAL::squared_distance(holmes,watson)<=rr ) {
        cout << "y"; continue;
      }
      Vertex_handle client1Vhdl = delaunay.nearest_vertex(holmes);
      Vertex_handle client2Vhdl = delaunay.nearest_vertex(watson);
      if (CGAL::squared_distance(holmes,client1Vhdl->point())<= rr &&
          CGAL::squared_distance(watson,client2Vhdl->point())<= rr &&
          client1Vhdl->info().first == client2Vhdl->info().first){
          cout << "y"; continue;
          }
      }
    cout << "n";
  }
  cout << endl;
}

// Part5 call main
int main(){
  int t;
  cin >> t ;
  while(t--){
    do_case();
  }
}
