//============================================================================
// Name        : LightPattern.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <vector>
#include <iostream>
using namespace std;

static vector<vector<int> > memo;
static vector<int> pattern;
static vector<int> init;
//static vector<int> goal;
static vector<int> diff;
int f(int i, int rev) { // 1 is reversed ith group
	int res;
	if (memo[i][rev] == -1) {
		if (i == 0) {
			res = min(diff[rev],1+diff[(rev+1)%2]);
		} else {
			res = min(f(i - 1, rev) + diff[2 * i + rev],
					f(i - 1, (rev + 1) % 2) + diff[2 * i + (rev + 1) % 2] +1); // Choose to reverse
		}
		memo[i][rev] = res;
//		cout << "For step " << i << " reverse " << rev << " The result "<< res << endl;
	} else {
		res = memo[i][rev];
	}
	return res;
}

void do_case() {
	int n, k, p;
	cin >> n >> k >> p;
	pattern.clear();
	init.clear();
	init.resize(n);
	pattern.resize(k);
	memo.clear();
	memo.resize(n / k);
//	cout << p << endl;
	for (int i = 0; i < k; ++i) {  // assuming a 32 bit int
		pattern[k-1 - i] = p % 2;
		p = p/2;


	}
//	for (int i = 0; i < k; ++i) {  cout << pattern[i];}
	diff.clear();
	diff.resize(2 * n / k);
	for (int i = 0; i < n; i++) {
		cin >> init[i];
	}
	vector<int> foo(2,-1);
	for (int i = 0; i < n / k; i++) { // every group
		int count = 0;
		memo[i] = foo;
		for (int j = 0; j < k; j++) {
			if (init[i * k + j] != pattern[j]) {
				count++;
			}

		}
		diff[2 * i] = count;
		diff[2 * i + 1] = k - count;
//		cout << count << endl;
	}
	cout << f(n / k-1, 0) << endl;
}
int main() {
	int t;
	cin >> t;
	while (t--) {
		do_case();
	}
	return 0;
}
