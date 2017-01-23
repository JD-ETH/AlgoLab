
// Due to the short time limit and big size, it seems impossible to solve with DP and Brute
// No good solution for greedy either

// Chessboard-> graph!
// ========
// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
// Namespaces
using namespace std;
using namespace boost;


// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
// Interior Property Maps
typedef	property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::edge_descriptor			Edge;
typedef graph_traits<Graph>::in_edge_iterator  InEdgeIt; // Iterator

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder {
	Graph &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:
	// to initialize the Object
	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

	// to use the Function (add an edge)
	void addEdge(int from, int to, long capacity) {
		Edge e, reverseE;
		bool success;
		tie(e, success) = add_edge(from, to, G);
		tie(reverseE, success) = add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[reverseE] = 0;
		revedgemap[e] = reverseE;
		revedgemap[reverseE] = e;
	}
};
void do_case(){
  int n;
  cin >> n;
  Graph G(n*n);
  Vertex src = add_vertex(G);
  Vertex sink = add_vertex(G);
  EdgeCapacityMap capacitymap = get(edge_capacity, G);
  ReverseEdgeMap revedgemap = get(edge_reverse, G);
  ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
  EdgeAdder eaG(G, capacitymap, revedgemap);
  const int mvx[8] = {-1,-1,1,1,-2,-2,2,2};
  const int mvy[8] = {-2,2,-2,2,-1,1,-1,1};
  int placeable;
  long placeable_count = 0;
  for (int i = 0 ; i< n; i ++){
    for (int j = 0; j< n; j++){
      cin >> placeable;
      if (placeable){
        placeable_count++;
        if ((i+j)%2 == 0){ // feed in
          eaG.addEdge(src,i*n+j,1);
          int relate_x,relate_y;
          for (int k = 0; k<8; k ++){
            relate_x = i+mvx[k];
            relate_y = j+mvy[k];
            if (relate_x>= 0 && relate_x < n && relate_y >=0 && relate_y < n){
              // On the board
              eaG.addEdge(i*n+j,relate_x*n+relate_y,1);
            }
          }
        }
        else {
          eaG.addEdge(i*n+j,sink,1);
        }
      }
    }
  }
  long flow = push_relabel_max_flow(G,src,sink);

  cout << placeable_count-flow << endl;

}


int main(){
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--){
    do_case();
  }
  return 0;
}
