#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list<vecS,vecS,directedS> Traits;
typedef adjacency_list<vecS,vecS,directedS,no_property,
    property<edge_capacity_t,long,
        property<edge_residual_capacity_t,long,
            property<edge_reverse_t,Traits::edge_descriptor,
                property<edge_weight_t, long> > > > > Graph;
typedef property_map<Graph,edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph,edge_weight_t>::type EdgeWeightMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph,edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;


class EdgeAdder {
  Graph &G;
  EdgeCapacityMap & capacitymap;
  EdgeWeightMap & weightmap;
  ReverseEdgeMap & revedgemap;

public:
    EdgeAdder(Graph &G, EdgeCapacityMap & capacitymap, EdgeWeightMap &weightmap,
        ReverseEdgeMap & revedgemap):
        G(G), capacitymap(capacitymap), weightmap(weightmap),revedgemap(revedgemap){

        }

    void addEdge(int u , int v, long c, long w){
      Edge e , reverseE;
      bool suc;
      tie(e, suc) = add_edge(u,v,G);
      tie(reverseE,suc) = add_edge(v,u,G);
      capacitymap[e] = c;
      weightmap[e] = w;
      capacitymap[reverseE] = 0;
      weightmap[reverseE] = -w;
      revedgemap[e] = reverseE;
      revedgemap[reverseE] = e;
    }
};

void do_case(){
  int n,m,l;
  cin >> n >> m >>l;
  Graph G(n+m);
  Vertex src = add_vertex(G);
  EdgeCapacityMap capacitymap =get(edge_capacity,G);
  EdgeWeightMap weightmap = get(edge_weight,G);
  ReverseEdgeMap revedgemap = get(edge_reverse,G);
  ResidualCapacityMap rescapacitymap = get(edge_residual_capacity,G);
  EdgeAdder EaG(G,capacitymap,weightmap,revedgemap);
  const long MAX_PRIORITY =1<<7;
  EaG.addEdge(src,0,l,0);
  for (int i = 1; i < n; i++) EaG.addEdge(i-1,i,l,MAX_PRIORITY);
  for (int i = 0; i < m; i ++){
    int u, v,w;
    cin >> u >> v >> w;
    EaG.addEdge(u,n+i,1,(v-u)*MAX_PRIORITY-w);
    EaG.addEdge(n+i,v,1,0);
  }

  successive_shortest_path_nonnegative_weights(G,src,n-1);
  cout << MAX_PRIORITY * l * (n-1)-find_flow_cost(G)<< endl;
  //
}

int main(){
  int t;
  cin >> t;
  while( t--){
    do_case();
  }
  return 0;
}
