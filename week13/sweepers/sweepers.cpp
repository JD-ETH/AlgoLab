#include <iostream>
#include <vector>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
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
typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> SimpleGraph;
// Interior Property Maps
typedef	property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::edge_descriptor			Edge;
typedef	graph_traits<Graph>::degree_size_type			degree_size_type;

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
// Three steps:
// sweepers can reach the exit -> even number of in and out  -> in every component at least one sweeper

void do_case(){
  int n,m,s;
  cin >>n >> m >>s;
  Graph G(n);
  SimpleGraph G2(n);
  Vertex src = add_vertex(G);
  Vertex sink = add_vertex(G);
  EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

  vector<int> spawn(s);
  vector<int> exits(s);
  vector<int> degrees(n);
  for (int i =0; i < s; i++){
    cin >> spawn[i];

    eaG.addEdge(src,spawn[i],1);

    degrees[spawn[i]]++;

  }
  for (int i =0; i < s; i++){
    cin >> exits[i];
    eaG.addEdge(exits[i],sink,1);
    degrees[exits[i]]++;
}
  for (int i = 0; i < m ; i++){
    int u,v;
    cin >> u >> v;
    eaG.addEdge(u,v,1);
    eaG.addEdge(v,u,1);
    add_edge(u,v,G2);
    degrees[u]++;
    degrees[v]++;
  }
  int flow = push_relabel_max_flow(G,src,sink);
  //cout << " the flow " << flow << endl;
  if (flow != s){  // Cant escape
    cout << "no" << endl;
    return;
  }
  // check for euler circuit condition
  for (int i = 0; i < n; i ++){
    if (degrees[i]%2 != 0){
      cout << "no"<< endl;
      return;
    }
  }
  // check for sweeper in every connected connected_components
  vector<int> component(num_vertices(G2));
  int num_comp = connected_components(G2, &component[0]);
  vector<int> rooms_in_component(num_comp,0);
  vector<bool> sweeper_in_component(num_comp,false);
  for (int i = 0; i < n;i++){
    rooms_in_component[component[i]]++;
  }
  for (int i = 0; i <s ;i++){
    sweeper_in_component[component[spawn[i]]] = true;// This component occupied
  }
  for (int i = 0; i<num_comp; i++){
    if (!sweeper_in_component[i] && rooms_in_component[i]>1){
      cout << "no" << endl;
      return;
    }
  }

  cout << "yes" << endl;
  return;

}
int main(){
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while(t--){
    do_case();
  }
  return 0;
}
