//============================================================================
// Name        : MoveBook.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main() {
	int t;
	std::ios_base::sync_with_stdio(false);
	std::cin >> t;

	while (t--) {
		int n, m;
		std::cin >> n >> m;
		std::vector<int> s(n), w(m);
		std::multiset<int, std::greater<int> > ws;

	for (int i = 0; i < n; ++i)
		std::cin >> s[i];
	for (int i = 0; i < m; ++i)
		std::cin >> w[i];

	// First check whether the answer is impossible.
	int maxw = -1;
	int maxs = -1;
	for (int i = 0; i < n; ++i)
		maxs = std::max(maxs, s[i]);
	for (int i = 0; i < m; ++i)
		maxw = std::max(maxw, w[i]);
	if (maxw > maxs) {
		std::cout << "impossible" << std::endl;
		continue; // Go to next test case.
	}

	// Precomputation: sort the strengths.
	std::sort(s.begin(), s.end(), std::greater<int>());

	// Now simulate the greedy algorithm.
	for (int i = 0; i < m; ++i)
		ws.insert(w[i]);
	int r = 0;
	while (!ws.empty()) {
		++r;
		for (int i = 0; i < n; ++i) {
			auto b = ws.lower_bound(s[i]);
			if (b != ws.end()) {
				ws.erase(b);
			} else {
				break;
			}
		}
	}

	std::cout << 3 * r - 1 << std::endl;
}
return 0;
}
 // Output the correct answer
