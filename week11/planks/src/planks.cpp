//============================================================================
// Name        : planks.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<vector<int> > vecvec;

//
//using namespace std;
//
//
//vector<int> get_indices(long s,int n){
//	vector<int> indices(n,0);
//	for (int i=0; i< n; ++i){
//		if (s& 1<<i) indices[i] = 1;
//	}
//	return indices;
//}
//pair<bool,vector<int> > solve(int n, vector<int> length,int goal){
//
//	for (long s = 0; s< 1<<n; ++s){
//		int sum = 0;
//		for (int i = 0; i <n ; ++i){
//			if (s & 1 <<i ) sum += length[i];
//			if (sum > goal) break;
//		}
//		if (sum == goal) {
//
//			return make_pair(true, get_indices(s,n));
//		}
//	}
//	return make_pair(false,vector<int>(0));
//}
//
//vector<int> find_new_vec(pair<bool,vector<int> > sol, vector<int>& length){
//	vector<int> new_vec;
//	for (int i = 0; i < length.size(); i++){
//		if (sol.second[i]==0){
//			new_vec.push_back(length[i]);
//
//		}
//	}
//	return new_vec;
//}
//
//void do_case(){
//	int n;
//	cin >> n;
//	vector<int> length(n);
//	long total_sum=0;
//	for (int i = 0; i < n; i ++) {
//		cin >> length[i];
//		total_sum += length[i];
//	}
//	if (total_sum %4 != 0) {
//		cout << 0 << endl;
//	}
//	long goal =  total_sum/4;
//
//	// Find numbers sum up to the first length
//	pair<bool,vector<int> > sol1 = solve(n,length,goal);
//	if (!sol1.first ) {
//		cout << 0 <<endl;
//		return;
//	}
//
//	// Out of the remaining
//	vector<int> new_length_1 = find_new_vec(sol1,length);
//
//	// Sum up to same number, remaining
//	pair<bool,vector<int> > sol2 = solve(new_length_1.size(),new_length_1,goal);
//	if (!sol2.first ) {
//		cout << 0 <<endl;
//		return;
//	}
//
//
//	vector<int> new_length_2 = find_new_vec(sol2,new_length_1);
//
//	pair<bool,vector<int> > sol3 = solve(new_length_2.size(),new_length_2,goal);
//	if (!sol3.first ) {
//		cout << 0 <<endl;
//		return;
//	}
//
//	cout << 1 << endl;
//	return;
//
//
//
//}

// This is the master solution using brute force and split and conquer techniques

// The back-track approach

void back_track(int id, int ubound,vecvec &F, vecvec &assignment, const vector<int> &planks){
	if (id>= ubound){  // current id bigger then upperbound
		vector<int> tuple(4,0);
		for (int i = 0; i < 4; i ++){
			for (int j = 0; j < assignment[i].size(); ++j){
				tuple[i] += planks[assignment[i][j]]; // create new tuple;
			}
		}
		F.push_back(tuple);
		return;
	}

	for ( int i = 0; i < 4 ;++i){
		assignment[i].push_back(id);
		back_track(id+1,ubound,F,assignment,planks); // Recursive call
		assignment[i].pop_back(); // Remove id-th plank from set
	}
}
void do_case(){
	int n;
	cin >> n;
	vector<int> planks;
	int sum = 0;
	for ( int i = 0; i < n; i ++){
		int plank; cin >> plank;
		sum += plank;
		planks.push_back(plank);
	}
	if (sum %4 != 0) {
		cout << 0 << endl;
		return;
	}
	vecvec F1,assignment(4);
	back_track(0,n/2,F1,assignment,planks);

	vecvec F2,assignment2(4);
	back_track(n/2,n,F2,assignment2,planks);

	sort(F2.begin(), F2.end());

	long long n_sol = 0;
	for (int idx = 0; idx < F1.size(); idx++){
		vector<int> member = F1[idx];
		for (int i = 0; i < 4 ; ++i){
			member[i] = sum/4-member[i];
		}
		pair<vecvec::iterator,vecvec::iterator> bounds;
		bounds = equal_range(F2.begin(),F2.end(), member);
		long long counter = distance(bounds.first, bounds.second);
		n_sol += counter;
	}

	cout << n_sol/24 << endl;

}
int main() {
	int t;
	cin >> t;
	while (t--){
		do_case();
	}
	return 0;
}
