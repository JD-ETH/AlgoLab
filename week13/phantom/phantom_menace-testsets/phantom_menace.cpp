
#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

// Namespaces
using namespace std;
using namespace boost;

// Minimum Cut equals to maximum flow!

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

void do_case(){
  int n,m,s,d;
  cin >> n >> m >> s >> d;
  Graph G(n*2);
  int MAX_CAP = std::min(s,d);
  Vertex src = add_vertex(G);
  Vertex sink = add_vertex(G);
  EdgeCapacityMap capacitymap = get(edge_capacity, G);
  ReverseEdgeMap revedgemap = get(edge_reverse, G);
  ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
  EdgeAdder eaG(G, capacitymap, revedgemap);
  for (int i =0; i < m; i++){
    int u,v;
    cin >> u >> v;
    eaG.addEdge(u+n,v,MAX_CAP);
  }
  for (int i = 0; i < n; i ++){
    eaG.addEdge(i,i+n,1); // Vertex capacity
  }
  for (int i =0; i < s; i++){
    int start;
    cin >> start;
    eaG.addEdge(src,start,1);
  }

  for (int i =0; i < d; i++){
    int des;
    cin >> des;
    eaG.addEdge(des+n,sink,1);
  }

  long flow = push_relabel_max_flow(G,src,sink);
  cout << flow << endl;

}

int main(){
	std::ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while(t--){
    do_case();
  }
  return 0;
}
