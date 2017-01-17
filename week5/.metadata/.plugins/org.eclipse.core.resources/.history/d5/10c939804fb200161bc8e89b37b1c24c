//============================================================================
// Name        : SecretService.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <vector>
#include <algorithm>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <iostream>
#include <climits>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property,
		property<edge_weight_t, int> > Graph;
typedef adjacency_list<vecS, vecS, undirectedS> Un_Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef graph_traits<Un_Graph>::vertex_descriptor Un_Vertex;
typedef graph_traits<Un_Graph>::edge_descriptor Un_Edge;

static int n, m, a, s, c, d;
vector<vector<int> > age_to_shelters;
bool Escape_success (int t){
	int edge_max = t-d;
	Un_Graph g(a+s);
	for (int i = 0; i < a; i++){
		for (int j = 0; j < s; j ++){
			if ( age_to_shelters[i][j] <= edge_max) {
				add_edge(i,a+j,g);
			}
		}
	}
	vector<Un_Vertex> matemap(a+s);
	edmonds_maximum_cardinality_matching(g, make_iterator_property_map(matemap.begin(),get(vertex_index,g)));
	return (matching_size(g,&matemap[0]) == a);
}
void do_case() {
	// Read

	cin >> n >> m >> a >> s >> c >> d;
	Graph G(n);
	vector<int> agents(a);
	vector<int> shelters(s);
	age_to_shelters = vector<vector <int> >(a, vector<int>(s, INT_MAX));
	WeightMap weightmap = get(edge_weight, G);
	while (m--) {
		Edge e;
		bool success;
		char ch;
		cin >> ch;
		int u, v, w;
		cin >> u >> v >> w;
		if (ch == 'S') {
			tie(e, success) = add_edge(u, v, G);
			weightmap[e] = w;
		} else {
			tie(e, success) = add_edge(u, v, G);
			weightmap[e] = w;
			tie(e, success) = add_edge(v, u, G);
			weightmap[e] = w;
		}
	}
	for (int i = 0; i < a; i++)
		cin >> agents[i];
	for (int i = 0; i < s; i++)
		cin >> shelters[i];

	// First solve the dijstra path problem multiple times
	int max_dist =0;
	for (int i = 0; i < a; i++) {
		vector<Vertex> predmap(n);
		vector<int> distmap(n);
		Vertex start = agents[i];
		dijkstra_shortest_paths(G,
				start, // We MUST provide at least one of the two maps
				predecessor_map(
						make_iterator_property_map(predmap.begin(),
								get(vertex_index, G))).	// predecessor map as Named Parameter
				distance_map(
						make_iterator_property_map(distmap.begin(),
								get(vertex_index, G))));// distance map as Named Parameter
		for (int j = 0; j < s; j++) {
			int ind = shelters[j];
			if (distmap[ind] < INT_MAX){
				age_to_shelters[i][j] = distmap[ind];
				max_dist = max (max_dist,distmap[ind]);
			}
		}
	}

	// Find the shortest time
	int tmin = 0;
	int tmax = max_dist+d;
	while (tmin != tmax){
		int mid = (tmin+tmax)/2;
		if (Escape_success(mid)) {
			tmax = mid;
		}
		else tmin = mid + 1;
	}
	cout << tmin << endl;
}
int main() {
	int t;
	cin >> t;
	while (t--) {
		do_case();
	}
	return 0;
}
