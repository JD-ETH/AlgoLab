#include <iostream>
#include <vector>
#include <climits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
//#include <boost/graph/connected_components.hpp>
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		no_property,				// interior properties of vertices
		property<edge_weight_t, int> 		// interior properties of edges
		>					Graph;
typedef graph_traits<Graph>::edge_descriptor		Edge;		// Edge Descriptor: an object that represents a single edge.
typedef graph_traits<Graph>::vertex_descriptor		Vertex;
typedef property_map<Graph, edge_weight_t>::type	WeightMap;	// property map to access the interior property edge_weight_t

void do_case(){
  int k;
  std::cin >> k;
  //std::vector<std::vector<int> > weights(k);
  int num_in_layer = 1;
  int node_num = (k+1)*k/2;
  int addrow[6] = {0,0,-1,-1,1,1};
  int addpos[6] = {1,-1,-1,0,0,1};

  Graph G(node_num*2); // first half In and out!
  std::vector<std::vector< int > > weights(k);
  WeightMap weightmap = get(edge_weight, G);
  Edge edge; bool success;
  int curr_node = 0;
  int connectrow, connectpos;
  for (int i = 0; i < k; i++){
    int num_in_layer = i+1;
    for (int j =0; j < num_in_layer; j++){
      int weight;
      std::cin >> weight;
      weights[i].push_back(weight);
      std::tie(edge,success) = add_edge(curr_node,curr_node+node_num,G); // in->Out
      curr_node++;
      weightmap[edge] = weight;
      // Now add connectivities, in total 6 possibilities
      for (int p = 0; p< 6; p++){
        connectrow = i+addrow[p];
        connectpos = j+addpos[p];
        if(connectrow >= 0 && connectrow <k && connectpos >=0 && connectpos <=connectrow){
          // Valid spot, add connectibity
          std::tie(edge,success) = add_edge(i*(i+1)/2+j+node_num,connectrow*(connectrow+1)/2+connectpos,
                                    G);
        }
      }
    }
  }

  // Graph construction done; 3 times dijkstra
  std::vector<Vertex> predmap(node_num*2);	// We will use this vector as an Exterior Property Map: Vertex -> Dijkstra Predecessor
	std::vector<int> distmap1(node_num*2),distmap2(node_num*2),distmap3(node_num*2);
	Vertex start = 0; Vertex left_end = k*(k-1)/2; Vertex right_end = k*(k+1)/2-1;
  dijkstra_shortest_paths(G, start, // We MUST provide at least one of the two maps
		predecessor_map(make_iterator_property_map(predmap.begin(), get(vertex_index, G))).	// predecessor map as Named Parameter
		distance_map(make_iterator_property_map(distmap1.begin(), get(vertex_index, G))));	// distance map as Named Parameter
  dijkstra_shortest_paths(G, left_end, // We MUST provide at least one of the two maps
  	predecessor_map(make_iterator_property_map(predmap.begin(), get(vertex_index, G))).	// predecessor map as Named Parameter
  	distance_map(make_iterator_property_map(distmap2.begin(), get(vertex_index, G))));	// distance map as Named Parameter
  dijkstra_shortest_paths(G, right_end, // We MUST provide at least one of the two maps
  	predecessor_map(make_iterator_property_map(predmap.begin(), get(vertex_index, G))).	// predecessor map as Named Parameter
  	distance_map(make_iterator_property_map(distmap3.begin(), get(vertex_index, G))));	// distance map as Named Parameter

  // Now compare and find smallest
  int res = INT_MAX;
  for (int i = 0; i < k ; i++){
    for (int j = 0 ; j < (i+1); j++){
      int ind = i*(i+1)/2 +j;
      res = std::min(res, distmap1[ind]+distmap2[ind]+distmap3[ind]+weights[i][j]);
    }

  }

  std::cout << res << std::endl;
}
int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  while(t--){
    do_case();
  }
  return 0;
}
