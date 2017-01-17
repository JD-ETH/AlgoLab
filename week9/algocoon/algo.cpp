#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <climits>
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
						property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::edge_iterator Edge_iterator;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;
// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
	Graph &G;
	EdgeCapacityMap &capacitymap;
	ReverseEdgeMap &revedgemap;

public:
	EdgeAdder(Graph &G, EdgeCapacityMap &capacitymap,
			ReverseEdgeMap& revedgemap) :
			G(G), capacitymap(capacitymap), revedgemap(revedgemap) {
	}

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
  int n,m;
  cin >> n >> m;
  Graph G(n); // Source as 0
  EdgeCapacityMap capacitymap = get(edge_capacity, G);
  ReverseEdgeMap revedgemap = get(edge_reverse, G);
  ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
  EdgeAdder eaG(G, capacitymap, revedgemap);
  for (int i = 0; i < m; i++) {
    int u,v;
    long c;
    cin >>u >> v >> c;
    eaG.addEdge(u,v,c);
  }
  int minsrc,minsnk;
  long min_flow = INT_MAX;
  long flow;
  for (int i = 1; i <n; i++){
    flow = push_relabel_max_flow(G,0,i);
    if (flow<min_flow){
      minsrc = 0;
      minsnk = i;
      min_flow = flow;
    }
    flow = push_relabel_max_flow(G,i,0);
    if (flow<min_flow){
      minsrc = i;
      minsnk = 0;
      min_flow = flow;
    }    //eaG.addEdge(i,sink,1,0); // Connect sink
  }

  cout << min_flow << endl;
  // BFS find figure
  push_relabel_max_flow(G,minsrc,minsnk);
  vector<int> vis(n);
  vis[minsrc] = true;
  std::queue<int> Q;
  Q.push(minsrc);
  int count =1;
  while(!Q.empty()){
    OutEdgeIt ebeg,eend;
    const int u = Q.front();
    Q.pop();
    for (tie(ebeg,eend) = out_edges(u,G); ebeg!= eend; ++ebeg){
      const int v = target(*ebeg,G);
      if (rescapacitymap[*ebeg]== 0 || vis[v]) continue;
      Q.push(v);
      vis[v]=true;
      count ++;
    }
  }
  cout << count << " ";
  for (int i = 0; i < n; i++){
    if  (vis[i]) cout << i << " ";
  }

  cout << endl;
}



int main() {
	int t;
	cin >> t;
	while (t--)
		do_case();
	return 0;
}
