#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <deque>
#include <queue>
#include <climits>
#include <map>

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
typedef map<int, int> MII;

const int MAX_VOL = 10003;

int res = 0;

void dfs(int cur, MII& used, VI& prices, VI& volumes, VI& cheapest, MII& vol_price, MII& vol_cnt, int n, int last) {
	if (cur == 0) {

		int temp = 0;
		for (auto v : used) {
			// cout << "u " << v.ST << " " << v.ND << "\n";
			temp += min(v.ND, vol_cnt[v.ST]);
		}
		res = max(res, temp);
		return;
	}

	// cout << cur << "\n";

	for (auto el : vol_price) {
		int v = el.ST;
		// cout << "_" << v << "\n";
		if (v < last) {
			continue;
		}
		int p = el.ND;
		// if (cur >= v) cout << cheapest[cur - v] << " " << cheapest[cur] << " -- " << v << " " << p << endl;
		if ((cur - v >= 0) && (cheapest[cur - v] == cheapest[cur] - p)) {
			// bool is_in = (used.find(i) != used.end());
			if (used.find(v) == used.end()) {
				used[v] = 1;
			} else {
				used[v]++;
			}
			dfs(cur - v, used, prices, volumes, cheapest, vol_price, vol_cnt, n, v);
			used[v]--;
			// if (!is_in) {
			// 	used.erase(i);
			// }
		}
	}
	// cout << "out " << cur << "\n";
}

void do_test() {
	int n, k;
	cin >> n >> k;
	VI prices_temp(n), volumes_temp(n);
	VI prices, volumes;
	map<int, int> vol_price;
	map<int, int> vol_cnt;
	int range = k + 1 + MAX_VOL;
	VI cheapest(range), used_volume(range), used_price(range);

	REP(i, n) {
		cin >> prices_temp[i] >> volumes_temp[i];
		if (vol_price.find(volumes_temp[i]) == vol_price.end() || vol_price[volumes_temp[i]] > prices_temp[i]) {
			vol_price[volumes_temp[i]] = prices_temp[i];
			vol_cnt[volumes_temp[i]] = 0;
		}
	}

	REP(i, n) {
		if (vol_price[volumes_temp[i]] == prices_temp[i]) {
			volumes.PB(volumes_temp[i]);
			vol_cnt[volumes_temp[i]]++;
			prices.PB(prices_temp[i]);
		}
	}
	n = volumes.size();

	REP(i, range) {
		cheapest[i] = INT_MAX;
	}

	// for (auto el : vol_cnt) {
	// 	cout << el.ST << " " << el.ND << endl;
	// }

	cheapest[0] = 0;
	for (int i = 1; i < range; i++) {
		REP(j, n) {
			if ((volumes[j] <= i) && (cheapest[i - volumes[j]] != INT_MAX)) {
				int new_price = cheapest[i - volumes[j]] + prices[j];
				if (new_price < cheapest[i]) {
					cheapest[i] = new_price;
					used_volume[i] = volumes[j];
					used_price[i] = prices[j];
				}
			}
		}
	}

	int cheapest_res = INT_MAX; //, start;
	for (int i = k; i <= k + MAX_VOL; i++) {
		if (cheapest[i] < cheapest_res) {
			cheapest_res = cheapest[i];
			// start = i;
		}
	}

	VI to_check;
	for (int i = k; i <= k + MAX_VOL; i++) {
		if (cheapest[i] == cheapest_res) {
			to_check.PB(i);
		}
	}

	int res_div = 0;
	res = 0;
	for (int start : to_check) {
		MII s;
		dfs(start, s, prices, volumes, cheapest, vol_price, vol_cnt, n, 0);
		// set<int> used;
		// while (start > 0) {
		// 	int v = used_volume[start];
		// 	int p = used_price[start];
		// 	// cout << v << " " << start << "\n";
		// 	REP(i, n) {
		// 		// bool added = false;
		// 		if (volumes[i] == v && prices[i] == p) {
		// 			if (used.find(i) == used.end()) {
		// 				// cout << i << "\n";
		// 				used.insert(i);
		// 				break;
		// 			}

		// 		}
		// 	}
		// 	start -= v;
		// }
		// res_div = max(res_div, (int) used.size());
	}

	cout << cheapest_res << " " << res << "\n";
	deb(cout << "----------\n";)

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