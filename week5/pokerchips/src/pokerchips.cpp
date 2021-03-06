//============================================================================
// Name        : pokerchips.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
//#include <unordered_map>
#include <set>
#include <vector>
using namespace std;
static vector<int> memo;
static map<vector<int>, int> memory;
static vector<vector<int> > stack;
static vector<int> zero_vec;
static int n;

//long long vectostate(vector<int> vec){
//	long long cur_state;
//
//	return cur_state;
//}
//
//vector<int> statetovec(long long cur_state){
//	vector<int> vec;
//
//	return vec;
//}
int solve(vector<int> &vec) {

	int res = 0;
	if (vec == zero_vec) {
//		cout << "Here is zero";
		return res;
	} // All empty

	map<vector<int>, int>::iterator it = memory.find(vec);
	if (it == memory.end()) {
//		cout << "Never found ";
		set<int> colors;
		multimap<int, int> colormap;
		vector<int> upmost(n);
		for (int i = 0; i < n; i++) {
			upmost[i] = stack[i][vec[i]];
//			cout << "At " << i <<  " the color is "<< upmost[i];
			if (upmost[i] != -1) {
				colors.insert(upmost[i]);
			}
			colormap.insert(make_pair(upmost[i], i)); // color and stack number
		}
		int add_points = 0;

		for (set<int>::iterator sit = colors.begin(); sit != colors.end(); // all possible moves
				sit++) { // Check for one color
			vector<int> new_state(vec); // copy of original
			vector<int> candidate;
			pair<multimap<int, int>::iterator, multimap<int, int>::iterator> mit =
					colormap.equal_range(*sit);  // corresponding stacks
			int count = 0;
			candidate.clear();
			for (multimap<int, int>::iterator mmit = mit.first;
					mmit != mit.second; ++mmit) { // Same color multiple
				count++;
//				new_state[mmit->second]--; // Corresponding stacks removes one
				candidate.push_back(mmit->second);
			}
			if (count >= 2) {  // Multiple possibilities exist
				for (int i = 1; i < 1 << count; i++) { // Check all possibilities
					vector<int> new_state(vec);
					int points=0;
					for (int j = 0; j < count; j++) {
						if (i & 1 << j){
							new_state[candidate[j]]--;
							points ++;}
					}
					if (points >1){
						res = max(res, solve(new_state)+(1<<(points-2)));}
					else res = max(res,solve(new_state));
				}
//				cout << " This move would add points: " << add_points;
			} else {
				new_state[candidate[0]]--;
				res = max(res, solve(new_state));
			}

//			if (count >= 3) {
//				cout << "The count " << count <<" would add points: " << add_points;
//			cout << "and transition from: ";
//			for (int i = 0; i < vec.size(); i++)
//				cout << vec[i] << ",";
//
//			cout << "into";
//			for (int i = 0; i < vec.size(); i++)
//				cout << new_state[i]<< ",";
//			cout << endl;
//			}

		}
		memory.insert(make_pair(vec, res));
	} else
		res = it->second;

	return res;
}
void do_case() {

	cin >> n;
	vector<int> ini_state(n);
	memory.clear();
	stack.clear();
	stack.resize(n);
	zero_vec = vector<int>(n, 0);
	for (int i = 0; i < n; i++) {
		cin >> ini_state[i];
	}
	for (int i = 0; i < n; i++) {
		stack[i].resize(ini_state[i] + 1);
		stack[i][0] = -1;
		for (int j = 0; j < ini_state[i]; j++)
			cin >> stack[i][j + 1];
	}
	cout << solve(ini_state) << endl;
//	for (map<vector<int>,int>::iterator it = memory.begin(); it != memory.end(); it++){
//	cout << "	Current state: ";
//	for (int i = 0; i < it->first.size(); i++)
//		cout << it->first[i]<< ",";
//	cout << endl;
//	cout << " Result in total points: " << it->second << endl;}
}
int main() {
	int t;
	cin >> t;
	while (t--) {
		do_case();
	}
	return 0;
}
