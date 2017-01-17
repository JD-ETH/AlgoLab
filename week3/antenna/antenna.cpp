#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;

int main() {
  for (;;) {
    int n;

    cin >> n;

    if (!n) {
      break;
    }

    vector<P> v(n);

    for (int i = 0; i < n; i++) {
      long x, y;

      cin >> x >> y;
      v[i] = P(x, y);
    }

    Min_circle mc(v.begin(), v.end(), true);
    Traits::Circle c = mc.circle();

    cout << ceil(sqrt(c.squared_radius())) << "\n";
  }

  return 0;
}
