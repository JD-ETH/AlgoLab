#include <iostream>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
//#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <vector>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Triangulation_data_structure<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K>  Delaunay;
typedef Delaunay::Point Point;
typedef Delaunay::Vertex_handle Vhandle;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
void do_case(){
  int a,s,b,e;
  std::cin >> a >> s >> b >> e;
  std::vector<Point > points(a);
  std::vector<int> density(a);
  for (int i = 0; i< a; i++){
    long x,y;
    std::cin >> x >> y;
    points[i] = Point(x,y);
    std::cin >> density[i];
  }
  std::vector<Point> shoots(s);
  for (int i = 0; i < s ; i ++){
    std::cin >> shoots[i];
  }
  std::vector<double> sqrd_dis(s);
  if (b != 0){
    std::vector<Point> bounty(b);
    for (int i = 0; i < b ; i ++){
      std::cin >> bounty[i];
    }

    Delaunay trg;
    trg.insert(bounty.begin(),bounty.end());

    for (int i=0;i < s; i++){
      Vhandle closest_vertex = trg.nearest_vertex(shoots[i]);
      sqrd_dis[i] = CGAL::squared_distance(closest_vertex->point(),shoots[i]); // Squared radius
    }
  }

  Program lp(CGAL::LARGER,true,0,false,0);
  for (int i = 0; i < a; i++){
    K::FT cur_dis;
    for (int j = 0; j<s; j++){
      cur_dis = CGAL::squared_distance(shoots[j],points[i]);
      if(b == 0 || cur_dis<=sqrd_dis[j]){ // the shoot takes effect
        if (cur_dis != 0) lp.set_a(j,i,1/ET(cur_dis));
        else lp.set_a(j,i,1);
      }
    }
    lp.set_b(i,density[i]);
  }
  for (int j = 0; j < s; j ++){
    lp.set_a(j,a,1);
    //lp.set_c(j,1);
  }
  lp.set_b(a,e);
  lp.set_r(a,CGAL::SMALLER);

  Solution sol = CGAL::solve_linear_program(lp,ET());
  if (sol.is_infeasible()) std::cout << "n" << std::endl;
  else std::cout << "y" << std::endl;
}

int main(){
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  while(t--){
    do_case();
  }
}
