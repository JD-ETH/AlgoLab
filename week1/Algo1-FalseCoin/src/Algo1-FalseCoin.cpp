//============================================================================
// Name        : Algo1-FalseCoin.cpp
// Author      : JD
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int main() {

	ios_base::sync_with_stdio(false);
	int test_case;
	cin >> test_case;
	for (int test_num = 0; test_num < test_case; test_num++) {
		int num_coin;
		int num_weigh;
		cin >> num_coin;
		cin >> num_weigh;
		set<int> candidates;

		for (int i = 1; i < num_coin + 1; i++) {
			candidates.insert(i); // one index for every coin
		}

		set<int> sol1(candidates);
		set<int> sol2(candidates);

		for (int i = 0; i < num_weigh; i++) { // Everytime it weighs
			int num_coin_per_weigh;
			cin >> num_coin_per_weigh;
			set<int> left;
			set<int> right;
			for (int i = 0; i < num_coin_per_weigh; i++) { // read left set
				int curr_coin;
				cin >> curr_coin;
				left.insert(curr_coin);
			}
			for (int i = 0; i < num_coin_per_weigh; i++) { // read right set
				int curr_coin;
				cin >> curr_coin;
				right.insert(curr_coin);
			}
			set<int> diff;
			set<int> intersect;
			char sym;
			cin >> sym; // read the symbol and response accordingly
			if (sym == '=') {
				left.insert(right.begin(), right.end());

				set_difference(sol1.begin(), sol1.end(), left.begin(),
						left.end(), inserter(diff, diff.begin()));
				sol1 = diff;
				diff.clear();
				set_difference(sol2.begin(), sol2.end(), left.begin(),
						left.end(), inserter(diff, diff.begin()));
				sol2 = diff;
				diff.clear();
			} else if (sym == '<' or sym == '>') {

				set_intersection(sol1.begin(), sol1.end(), left.begin(),
						left.end(), inserter(intersect, intersect.begin()));
				sol1 = intersect;
				intersect.clear();
				set_intersection(sol2.begin(), sol2.end(), right.begin(),
						right.end(), inserter(intersect, intersect.begin()));
				sol2 = intersect;
				intersect.clear();
			}

		}

		if (sol1.size() == 1) {
			cout << *(sol1.begin()) << endl;
		}

		else if (sol2.size() == 1) {
			cout << *(sol2.begin()) << endl;
		}

		else {
			cout << 0 << endl;
		}

	}
	return 0;
}
