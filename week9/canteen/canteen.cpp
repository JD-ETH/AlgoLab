 #include <iostream>
#include <cstdlib>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
// Namespaces

using namespace boost;
using namespace std;

// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
		property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long,
						property<edge_reverse_t, Traits::edge_descriptor,
								property<edge_weight_t, long> > > > > Graph;
// Interior Property Maps
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t>::type EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt; // Iterator

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
	Graph &G;
	EdgeCapacityMap &capacitymap;
	EdgeWeightMap &weightmap;
	ReverseEdgeMap &revedgemap;

public:
	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap,
			ReverseEdgeMap &revedgemap) :
			G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(
					revedgemap) {
	}

	void addEdge(int u, int v, long c, long w) {
		Edge e, reverseE;
		tie(e, tuples::ignore) = add_edge(u, v, G);
		tie(reverseE, tuples::ignore) = add_edge(v, u, G);
		capacitymap[e] = c;
		weightmap[e] = w;
		capacitymap[reverseE] = 0;
		weightmap[reverseE] = -w;
		revedgemap[e] = reverseE;
		revedgemap[reverseE] = e;
	}
};

void do_case(){
  int n;
  cin >> n;
  Graph G(n);
  Vertex src = add_vertex(G);
  Vertex sink = add_vertex(G);
  EdgeCapacityMap capacitymap = get(edge_capacity, G);
  EdgeWeightMap weightmap = get(edge_weight, G);
  ReverseEdgeMap revedgemap = get(edge_reverse, G);
  ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
  EdgeAdder EaG(G, capacitymap, weightmap, revedgemap);
  const long MAX_PRICE = 20;
  for (int i = 0; i < n; i ++) {
    int a,c;
    cin >> a >> c;
    EaG.addEdge(src,i,a,c);
  }
  int student=0;
  for (int i = 0; i < n; i ++) {
    int s,p;
    cin >> s >> p;
    student += s;
    EaG.addEdge(i,sink,s,MAX_PRICE-p);
    //cout << "Stu: " << student ;
  }

  for (int i = 0; i < n-1; i ++) {
    int v,e;
    cin >> v >> e;
    EaG.addEdge(i,i+1,v,e);
  }

  successive_shortest_path_nonnegative_weights(G, src, sink);
  long cost = find_flow_cost(G);
  OutEdgeIt e, eend;
  long flow = 0;
  for (tie(e, eend) = out_edges(vertex(src, G), G); e != eend; ++e) {
		flow += capacitymap[*e] - rescapacitymap[*e];
	}
  if (flow == student) cout << "possible" << " ";
  else cout << "impossible" << " ";
  cout << flow << " " << -cost+flow*MAX_PRICE << endl;
}
int main() {
	int t;
	cin >> t;
	while (t--)
		do_case();
	return 0;
}
