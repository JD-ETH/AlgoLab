// Includes
// ========
// STL includes
#include <iostream>
#include <cstdlib>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/cycle_canceling.hpp>
//#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <map>
#include <set>
#include <vector>
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
                property <edge_weight_t, long> > > > > Graph;
// Interior Property Maps
typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_weight_t >::type       EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;
typedef graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    EdgeWeightMap &weightmap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap)
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

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
struct Reservation {
  int s,t,d,a,p;
};
void do_case(){
  const int MAX_PRICE = 100;

  int N,S;
  cin >> N >> S;
  vector<int> L(S);
  for (int i = 0; i < S; ++i){
    cin >> L[i];
  }
  const int INF_CAP = 100*S;
  const int MAXT = 100000;
  vector<Reservation> reservations;
  vector<set<int> > compressed(S);
  for (int i =0; i < S; ++ i){
    compressed[i].insert(0); // Station zero
    compressed[i].insert(MAXT); // End Station
  }

  for (int i = 0; i < N ; ++ i ){
    int s,t,d,a,p;
    cin >> s >> t >> d >> a >> p;
    s--; t--;
    compressed[s].insert(d); compressed[t].insert(a);
    reservations.push_back({s,t,d,a,p});
  }

  vector<map<int, int> > M(S); // Mappings for the coordinate compression

  vector<int> psum(S+1,0); // sums of coordinate lengths
  for (int s = 0; s < S ; ++s){
    int i = 0; // coordinate mapping for station s
    for (int t : compressed[s]){
      M[s][t] = i; // Linking to compressed cooridnates
      i++;
    }
    psum[s+1] = psum[s] + M[s].size();
  }

  Graph G(psum.back());
  Vertex src = add_vertex(G);
  Vertex sink = add_vertex(G);
  EdgeCapacityMap capacitymap = get(edge_capacity, G);
  EdgeWeightMap weightmap = get(edge_weight, G);
  ReverseEdgeMap revedgemap = get(edge_reverse, G);
  ResidualCapacityMap rescapacitymap = get(edge_residual_capacity, G);
  EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

  for (int i = 0; i<S ; ++i) {
    eaG.addEdge(src, psum[i], L[i],0);
    eaG.addEdge(psum[i+1]-1, sink, INF_CAP, 0);
    int it = -1, lastt = 0;
    for (int t: compressed[i]){
      if (it != -1) {
        eaG.addEdge(psum[i]+it, psum[i]+it+1, INF_CAP,MAX_PRICE*(t-lastt));

      }
      it++; lastt=t;
    }
  }
  for (int i= 0; i < N; i ++){
    eaG.addEdge(psum[reservations[i].s] + M[reservations[i].s][reservations[i].d],
    psum[reservations[i].t] + M[reservations[i].t][reservations[i].a],1,
    ((reservations[i].a-reservations[i].d)*MAX_PRICE - reservations[i].p));
  }

  successive_shortest_path_nonnegative_weights(G,src,sink);
  int flow = 0;
  OutEdgeIt e, eend;
  for(tie(e, eend) = out_edges(vertex(src,G), G); e != eend; ++e) {
      flow += capacitymap[*e] - rescapacitymap[*e];
  }
  int cost = MAX_PRICE*100000*flow-find_flow_cost(G);
  cout << cost << endl;
}

int main(){
  int t;
  cin >> t ;
  while (t--){
    do_case();
  }
}
