
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
//#include <boost/graph/edmonds_karp_max_flow.hpp>

using namespace std;
using namespace boost;

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
typedef graph_traits<Graph>::in_edge_iterator InEdgeIt;
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
  int g,s,l;
  cin >> g >> s >> l;
  Graph G(g+s+2);
  EdgeCapacityMap capacitymap = get(edge_capacity,G);
  ReverseEdgeMap revedgemap = get(edge_reverse,G);
  ResidualCapacityMap rescapacitymap = get(edge_residual_capacity,G);
  EdgeAdder eaG(G,capacitymap,revedgemap);
  const int src = 0;
  const int sink = g+s+1;
  for(int i= 0; i < l; i ++){
    int u,v;
    cin >> u >> v;
    eaG.addEdge(u+1,v+g+1,1);
  }
  for (int i = 0;i <g ; i ++){
    eaG.addEdge(src,i+1,1);
  }
  for (int i = 0;i <s ; i ++){
    eaG.addEdge(g+i+1,sink,1);
  }

  push_relabel_max_flow(G,src,sink);
  vector<int> sats,stations;


// BFS
  vector<int> vis(g+s+2, false); // visited flags
  std::queue<int> Q; // BFS queue (from std:: not boost::)
  vis[src] = true; // Mark the source as visited
  Q.push(src);
  while (!Q.empty()) {
    const int u = Q.front();
    Q.pop();
    OutEdgeIt ebeg, eend;
    InEdgeIt ibeg, iend;
    for (tie(ebeg, eend) = out_edges(u, G); ebeg != eend; ++ebeg) {
      const int v = target(*ebeg, G);
      //cout << "Edge: " << u << " " << v << " ";
      //cout << rescapacitymap[*ebeg] << endl;
      // Only follow edges with spare capacity, left to right if empty
      if ((u<v &&rescapacitymap[*ebeg] == 0) || vis[v] || (u>v &&rescapacitymap[*ebeg] == 0)) continue; // Visited or not possible
      vis[v] = true;
      //cout << "New visit" << v << endl;
      Q.push(v);
    }

  }

  for (int i = 1; i < g+s+1; i++){
    if (i <= g && !vis[i]) stations.push_back(i-1);
    if (i>g && vis[i]) sats.push_back(i-g-1);
  }

  cout << stations.size() << " " << sats.size() << endl;
  for (int i = 0; i < stations.size(); i ++) cout << stations[i] << " ";
  for (int i = 0; i < sats.size(); i ++) cout << sats[i] << " ";
  cout << endl;
  }

int main() {
  int t;
  cin >> t;
  while (t--) {
    do_case();
  }
}
