//============================================================================
// Name        : odd.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/tuple/tuple.hpp>
#include <climits>
#include <iostream>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS,vecS,directedS,no_property,property<edge_weight_t,int> > Graph;
typedef property_map<Graph,edge_weight_t>::type EdgeWeightMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

void add_edges(Graph & G, int u, int v , int w){
	int uee=4*u; int ueo=uee+1; int uoe= ueo+1; int uoo = uoe+1;
	int vee=4*v; int veo=vee+1; int voe= veo+1; int voo = voe+1;
	EdgeWeightMap weights = get(edge_weight, G);
	Edge edge;
	if (w%2 == 0 ) // Even weight
		{
		tie(edge,tuples::ignore) = add_edge(uee,voe,G); weights[edge] = w;
		tie(edge,tuples::ignore) = add_edge(ueo,voo,G); weights[edge] = w;
		tie(edge,tuples::ignore) = add_edge(uoe,vee,G); weights[edge] = w;
		tie(edge,tuples::ignore) = add_edge(uoo,veo,G); weights[edge] = w;

		}
	else{ // odd weight
		tie(edge,tuples::ignore) = add_edge(uee,voo,G); weights[edge] = w;
		tie(edge,tuples::ignore) = add_edge(ueo,voe,G); weights[edge] = w;
		tie(edge,tuples::ignore) = add_edge(uoe,veo,G); weights[edge] = w;
		tie(edge,tuples::ignore) = add_edge(uoo,vee,G); weights[edge] = w;
	}
}
void do_case(){
	int n,m,s,t;
	cin >> n >>m >> s >> t;
	Graph G(4*n);
	for (int i = 0; i < m; i++){
		int u,v,w;
		cin >> u >> v >> w;
		add_edges(G,u,v,w);
	}
	vector<int> dis(4*n,-1);
	dijkstra_shortest_paths(G,s*4,distance_map(&dis[0]));
	(dis[4*t+3] < INT_MAX) ? cout << dis[4*t+3] << endl : cout << "no\n";

}
int main() {
	int t;
	cin >> t;
	while(t--){
		do_case();
	}
	return 0;
}
