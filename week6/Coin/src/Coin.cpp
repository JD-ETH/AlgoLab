//============================================================================
// Name        : Coin.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/push_relabel_max_flow.hpp>
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

void do_case() {
	int n, m;
	cin >> n >> m;
	vector<int> score_cur(n, 0);
	vector<int> score_final(n);
	Graph G(n + m); // first m games, n people

	EdgeCapacityMap capacitymap = get(edge_capacity, G);
	ReverseEdgeMap revedgemap = get(edge_reverse, G);
	ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
	EdgeAdder eaG(G, capacitymap, revedgemap);

	Vertex src = add_vertex(G);
	Vertex sink = add_vertex(G);
	int match_num =0;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		if (c == 1)
			score_cur[a]++;
		else if (c == 2)
			score_cur[b]++;
		else {
			eaG.addEdge(src, i, 1);
			eaG.addEdge(i, m + a, 1);
			eaG.addEdge(i, m + b, 1);
			match_num++;
		}
	}

	long flow = 0;
	long diff;
	bool impossible = false;
	;
	for (int i = 0; i < n; i++) {
		cin >> score_final[i];
		if (score_final[i] != score_cur[i]) {
			diff = score_final[i] - score_cur[i];
			if (diff < 0) {
				impossible = true;
			}
			eaG.addEdge(m + i, sink, diff);
			flow += diff;
		}
	}

	if (match_num != flow) impossible = true;
	if (impossible) {
		cout << "no"<< endl;
		return;
	}
//	long final_flow = push_relabel_max_flow(G,src,sink);
	long final_flow = edmonds_karp_max_flow(G, src, sink);
//	cout << final_flow << flow;
	if (final_flow == flow)
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
