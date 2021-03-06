//============================================================================
// Name        : Coin.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>

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
// Seperate incoming and outgoing flows
void do_case() {
	long l, p;
	cin >> l >> p;
	Graph G(l); // 2l vertices from 0 to l is in, then out
	map<Edge, int> least;
	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);
	Edge some_e;
	Vertex sink = add_vertex(G);
	Vertex src = add_vertex(G);
	long demand = 0;
	long total=0,total_need = 0;;
	for (int i = 0; i < l; i++) {
		int supply, need;
		cin >> supply >> need;
		eaG.addEdge(src, i, supply);
		eaG.addEdge(i, sink, need);
		total+=supply;
		demand += need;
	}
//	if (demand > total) { cout << "no, not enough" << endl; return;}
	for (int i = 0; i < p; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		if (c== 0) eaG.addEdge(a, b, d);
		else {
			eaG.addEdge(src,b,c);
			eaG.addEdge(a,sink,c);
			eaG.addEdge(a,b,d-c);
			demand +=c;
		}
	}
	long flow = push_relabel_max_flow(G,src,sink);
//	long flow = edmonds_karp_max_flow(G, src, sink);
//	cout << "The flow: " << flow << endl;

//	cout << final_flow << flow;
	if (demand == flow)
		cout << "yes" << endl;
	else
		cout << "no" << endl;

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

