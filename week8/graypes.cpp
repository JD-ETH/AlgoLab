#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <iostream>
using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel IK;
typedef Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef Delaunay_triangulation_2<IK> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;

double ceil_to_double(EK::FT const & x)
{
double a = std::ceil(CGAL::to_double(x));
while (a < x) a += 1;
while (a-1 >= x) a -= 1;
return a;
}
static int N;

void do_case(){
    vector<IK::Point_2> pts;
    for (int i = 0; i < N ; ++i){
      IK::Point_2 pt;
      cin >> pt;
      pts.push_back(pt);
    }

    // Construction
    Triangulation t;
    t.insert(pts.begin(),pts.end());

    cout << "Finished Delanuay \n";
    // Iterate through
    IK::FT dis = numeric_limits<IK::FT>::max();
    for (Edge_iterator eit=t.finite_edges_begin(); eit != t.finite_edges_end(); eit++){
      dis = std::min(dis,t.segment(*eit).squared_length());
    }

    EK::FT time_cs = 50 * CGAL::sqrt(EK::FT(dis));
    cout << ceil_to_double(time_cs) << endl;
}
int main(){
  ios_base::sync_with_stdio(false);
  while (cin >> N && N!=0){
    do_case();
  }
}
