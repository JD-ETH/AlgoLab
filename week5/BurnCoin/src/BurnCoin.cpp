//============================================================================
// Name        : BurnCoin.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

static vector<int> coins;
static vector<vector<int> > memo;
int f(int i, int j) {
	int res;
	if (memo[i][j] == -1) {
		if (i == j) {
			res = coins[i];
		} else if (i + 1 == j) {
			res = max(coins[i], coins[j]);
		} else {
			res = max(min(f(i + 2, j), f(i + 1, j - 1)) + coins[i],
					min(f(i, j - 2), f(i + 1, j - 1)) + coins[j]);
		}
		memo[i][j] = res;
	}
	else {
		res = memo[i][j];
	}

	return res;
}
void do_testcase() {
	int n;
	cin >> n;
	coins.resize(n);
	memo.resize(n);

	for (int i = 0; i < n; i++) {
		cin >> coins[i];
		memo[i] = vector<int>(n, -1);
	}
	cout << f(0, n - 1) << endl;
}
int main() {
	int t;
	cin >> t;
	while (t--) {
		do_testcase();
	}
	return 0;
}
