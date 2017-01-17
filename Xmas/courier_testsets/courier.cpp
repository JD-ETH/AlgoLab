#include <iostream>
#include <vector>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

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

// This is a bipartie matching problem. find the max reward subset and max
// subset of tickets not bought
// The problem can be reformulated as to find the maximum independent set
// Or equivalently minimum vertex cover
// Which again correspond to the max-flow problem

void testcases() {
	// Create Graph and Maps
  int Z,J;
  cin >> Z >> J;
	Graph G(Z+J);
  Vertex src = add_vertex(G);
  Vertex sink = add_vertex(G);
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);
  int total_rewards=0;
  for (int i = 0; i < Z ; i++){
    int cap;
    cin >> cap;
    eaG.addEdge(i+J,sink,cap);
  }
  for (int i = 0; i < J ; i++){
    int cap;
    cin >> cap;
    total_rewards += cap;
    eaG.addEdge(src,i,cap);
  }
  const int MAX_CAP = 5000;
  for (int i = 0; i < J; i++){
    int num;
    cin >> num;
    for (int j = 0; j < num; j++){
      int buy_zone;
      cin >> buy_zone;
      eaG.addEdge(i,buy_zone+J,MAX_CAP);
    }
  }


	// Calculate flow
	// If not called otherwise, the flow algorithm uses the interior properties
	// - edge_capacity, edge_reverse (read access),
	// - edge_residual_capacity (read and write access).
	long flow = push_relabel_max_flow(G, src, sink);

	cout << total_rewards -flow << endl;
}

// Main function to loop over the testcases
int main() {
	ios_base::sync_with_stdio(false);
	int T;
  cin >> T;
	for (; T > 0; --T)	testcases();
	return 0;
}
