#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <deque>
#include <queue>
#include <climits>

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define ST first
#define ND second
#define PB push_back
#define MP make_pair
#define deb(a)

using namespace std;

typedef pair<int, int> PII;
typedef vector < PII > VPII;
typedef vector<int> VI;
typedef long long int LL;

const int H = 103, W = 17, W2 = (1 << W);
int res[H][W2], arr[H][W];


void do_test() {
	int h, w;
	cin >> h >> w;

	int trash;
	if (h < 3 || w < 3) {
		REP(i, h) {
			REP(j, w) {
				cin >> trash;
			}
		}
		cout << 0 << "\n";
		return;
	}

	// Cutting out border.
	h -= 2;
	w -= 2;
	int bitmasks = 1 << w;

	REP(i, w + 2) {
		cin >> trash;
	}

	REP(i, h) {
		cin >> trash;
		REP(j, w) {
			cin >> arr[i][j];
		}
		cin >> trash;
	}


	REP(i, w + 2) {
		cin >> trash;
	}



	REP(b, bitmasks) {
		res[0][b] = 0;
	}

	for (int i = 1; i < h; i++) {
		// If we don't want to use new row at all.
		int temp = 0;
		REP(b, bitmasks) {
			temp = max(temp, res[i - 1][b]);
		}
		res[i][0] = temp;
		deb(cout << "temp "<< i << " " << res[i][0] << endl;)

		for(int b = 1; b < bitmasks; b++) {
			res[i][b] = 0;
			// Leaving a square of the new row empty.
			REP(j, w) {
				if ((1 << j) & b) {
					res[i][b] = max(res[i][b], res[i][b - (1 << j)]);
				}
			}
			// deb(cout << res[i][b] << endl;)

			// Checking if there are only even consecutive ones and counting them.
			bool to_consider = true;
			int cnt = 0, cur_cnt = 0;
			REP(j, w) {
				if (b & (1 << j)) {
					if (!arr[i][j] || !arr[i - 1][j]) {
						to_consider = false;
						break;
					}
					cur_cnt++;
				} else {
					if (cur_cnt % 2) {
						to_consider = false;
						break;
					}
					cnt += cur_cnt;
					cur_cnt = 0;
				}
			}
			if (cur_cnt % 2) {
				to_consider = false;
			} else {
				cnt += cur_cnt;
			}

			if (to_consider) {
				deb(cout << "cons " << b <<  " " << (1<<w) - 1 - b << " " << res[i-1][(1<<w) - 1 - b] << " " << cnt<< "\n";)
				res[i][b] = max(res[i][b], res[i - 1][(1 << w) - 1 - b] + cnt / 2);
			}
			deb(cout << i << " " << b << " " << res[i][b] << endl;)
		}
	}

	int max_res = 0;
	REP(b, bitmasks) {
		max_res = max(max_res, res[h - 1][b]);
	}

	cout << max_res << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		do_test();
	}
	return 0;
}