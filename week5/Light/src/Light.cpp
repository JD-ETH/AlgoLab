//============================================================================
// Name        : Light.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;
// Test for the M=1 case
// Try expand for multiple M, by save all candidates and select

static int N, M;
static vector<vector<int> > switch_off, switch_on;
static vector<int> par_sum;
static multimap<int, int> par_sum2;
static vector<int> par_sum_2;
static vector<pair<int, int> > candidates;
int count_switch(int s) {
	int count = 0;
	for (int i = 0; i < 16; ++i) {
		if (s & 1 << i)

			count++;
	}
	return count;
}
void do_case() {

	// Init and input

	cin >> N >> M;
	int b[M];
	for (int i = 0; i < M; i++)
		cin >> b[i];
	switch_off.clear();
	switch_off.resize(N);
	switch_on.clear();
	switch_on.resize(N);
	candidates.clear();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int t1, t2;
			cin >> t1 >> t2;
			switch_off[i].push_back(t1);
			switch_on[i].push_back(t2);
		}
	}
	int half = ceil(N / 2);
	// get partial sum for room 0
	par_sum.clear();
	par_sum.resize(1 << half);
	par_sum2.clear();

	for (int s = 0; s < 1 << half; ++s) {
		int sum = 0;
		for (int i = 0; i < half; ++i) {
			if (s & 1 << i)
				sum += switch_on[i][0]; // Switched on
			else
				sum += switch_off[i][0]; // Switched off
		}
		par_sum[s] = sum;

	}
	for (int s = 0; s < 1 << (N - half); ++s) {
		int sum2 = 0;
		for (int i = 0; i < (N - half); ++i) {
			if (s & 1 << i)
				sum2 += switch_on[i + half][0]; // Switched on
			else
				sum2 += switch_off[i + half][0]; // Switched off
		}
		par_sum2.insert(make_pair(sum2, s));
	}
	// binary search find possible solutions

	for (int s = 0; s < 1 << half; ++s) { // go through list 1
//		cout << "current trial " << s << endl;
		int goal = b[0] - par_sum[s];
		if (goal < 0)
			continue;
		pair<multimap<int, int>::iterator, multimap<int, int>::iterator> ret;
		ret = par_sum2.equal_range(goal);
		for (multimap<int, int>::iterator it = ret.first; it != ret.second;
				it++) {
			if (it->first != goal) {
				break;
			} else {
				candidates.push_back(make_pair(s, it->second));
//				cout << s << " and " << it->second << endl;
			}
		}
//		count = min(count, count_1 + count_2);
	}

	for (int j = 1; j < M; j++) { // Now check for all other rooms
		vector<pair<int, int> > survivors;
		// partial sum again
		par_sum.clear();
		par_sum.resize(1 << half);
		par_sum_2.clear();
		par_sum_2.resize(1 << (N - half));
		for (int s = 0; s < 1 << half; ++s) {
			int sum = 0;
			for (int i = 0; i < half; ++i) {
				if (s & 1 << i)
					sum += switch_on[i][j]; // Switched on
				else
					sum += switch_off[i][j]; // Switched off
			}
			par_sum[s] = sum;
		}
		for (int s = 0; s < 1 << (N - half); ++s) {
			int sum2 = 0;
			for (int i = 0; i < (N - half); ++i) {
				if (s & 1 << i)
					sum2 += switch_on[i + half][j]; // Switched on
				else
					sum2 += switch_off[i + half][j]; // Switched off
			}
			par_sum_2[s] = sum2;
		}
		for (vector<pair<int, int> >::iterator it = candidates.begin();
				it != candidates.end(); it++) {
			if (par_sum[it->first] + par_sum_2[it->second] == b[j]) {
				survivors.push_back(*it);
			}
		}
		candidates.clear();
		candidates = survivors;
		survivors.clear();
	}


	// Output
	if (candidates.size() != 0) {
		int res = N;
//		cout << "get res";
		for (vector<pair<int, int> >::iterator it = candidates.begin();
				it != candidates.end(); it++) {
			int count1 = count_switch(it->first);
			int count2 = count_switch(it->second);
//			cout << it-> first << " and " << it->second<< endl;
			res = min(res, count1 + count2);

		}
		cout << res << endl;
	} else
		cout << "impossible" << endl;
}



// Brute force approach
int main() {
	int t;
	cin >> t;
	while (t--) {
		do_case();
	}
	return 0;
}

////============================================================================

//// Name        : Light.cpp
//// Author      :
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
//
//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <map>
//using namespace std;
//// Test for the M=1 case
//// Try expand for multiple M
//
//static int N,M,b;
//static vector<int> switch_off,switch_on;
//static vector<int> par_sum;
//static multimap<int,int> par_sum2;
//int count_switch(int s){
//	int count=0;
//	for (int i=0; i<N/2; ++i){
//		if (s & 1 << i) count++;
//	}
//	return count;
//}
//void do_case() {
//
//	// Init and input
//
//	cin >> N >> M >> b;
//	switch_off.clear();switch_off.resize(N);
//	switch_on.clear();switch_on.resize(N);
//	for (int i = 0; i < N; i++) {
//		cin >> switch_off[i];
//
//		cin >> switch_on[i];
//	}
//
//	// get partial sum
//	par_sum.resize(1<<15);
//	par_sum2.clear();
//	for (int s = 0; s < 1<< 15 ; ++s) {
//		int sum = 0;
//		for (int i=0; i<N/2; ++i){
//			if (s & 1 << i) sum += switch_on[i]; // Switched on
//			else sum += switch_off[i]; // Switched off
//		}
//		par_sum[s] = sum;
//
//		int sum2 = 0;
//		for (int i=0; i<N/2; ++i){
//			if (s & 1 << i) sum2 += switch_on[i+N/2]; // Switched on
//			else sum2 += switch_off[i+N/2]; // Switched off
//		}
//		par_sum2.insert(make_pair(sum2,s));
//	}
//
//	// binary search find possible solutions
//	int count = N+1;
//	for (int s = 0; s < 1<< 15 ; ++s) { // go through list 1
//		int goal = b-par_sum[s];
//		if (goal < 0) continue;
//		int count_1 = count_switch(s);
//		int count_2 = N/2;
//		pair<multimap<int,int>::iterator,multimap<int,int>::iterator> ret;
//		ret = par_sum2.equal_range(goal);
//		for (multimap<int,int>::iterator it = ret.first; it!=ret.second; it++){
//			if (it->first != goal){break;}
//			else count_2 = min(count_2,count_switch(it->second));
//		}
//		count = min(count,count_1+count_2);
//	}
//
//
//	// Output
//	if (count <= N){ cout << count << endl;}
//	else cout << "impossible" <<endl;
//}
//// Brute force approach
//int main() {
//	int t;
//	cin >> t;
//	while (t--) {
//		do_case();
//	}
//	return 0;
//}
//
