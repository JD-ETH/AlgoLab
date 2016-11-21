#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;


inline int dist(int &a, int &b, int &m){
	return (b-a+m)%m;
}
void find_jedi() {
	// read inputs
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(n);
	multimap<int, bool> allpts;
	int overlap = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		cin >> b[i];
		if (b[i] < a[i]) {
			overlap++;
		}
		allpts.insert(make_pair(a[i], true));
		allpts.insert(make_pair(b[i]+1, false));
	}

	// find one segment with minimum protection
	int counter = 11;
	int seg_ind=1;
	int last_id=0;
	// Find the minimum overlap
	for (map<int, bool>::iterator it = allpts.begin(); it != allpts.end() and (it-> first <= m);
			it++) {
		if (it->second) {
			overlap++;
		} else {
			overlap--;
			map<int, bool>::iterator it_c = it;
			if (overlap < counter and (++it_c)->first != it->first) {
				counter = overlap;
				seg_ind = it->first;
			}

		}
		last_id = it->first;
	}

	vector<int> jedi_index;


// Reorganize the data depending on the current index
	multimap<int, int> data; // Data without jedis defending this segment
//	vector<int>::iterator itjedi;
	for (int i = 0; i < n; i++) {
		if (dist(seg_ind,b[i],m)<=dist(a[i],b[i],m)){
			jedi_index.push_back(i); // Min Segment inside
			continue;
		}
		int key = (b.at(i) < seg_ind ? b.at(i) + m : b.at(i));
		int value = (a.at(i) < seg_ind ? a.at(i) + m : a.at(i));
		data.insert(pair<int, int>(key, value));
	}

	// Run the greedy algorithm counter + 1 times
	int best = 0;
	for (int p = 0, f = seg_ind - 1, lastseg = seg_ind + m; p <= counter; p++) {
		int num = 0;
		if (p != 0) { // Update starting and end point if not from zero
			int ind = jedi_index[p - 1];
			f = (b[ind] <= seg_ind ? b[ind] + m : b[ind]);
			lastseg = (a[ind] <= seg_ind ? a[ind] + m : a[ind]);
			num++;
		}

		for (multimap<int, int>::iterator it = data.begin(); it != data.end();
				it++) { // Iterate through
			if (it->second > f and it->first < lastseg) { // New jedi possible
				num++;
				f = it->first;
			}
		}

		best = max(best, num);

	}
	data.clear();
	cout << best << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		find_jedi();
	}
	return 0;
}
