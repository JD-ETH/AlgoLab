//============================================================================
// Name        : hope.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Name        : Coin.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

class node {
public:
	int index;
	int s;
	vector<int> sons;
	void add_son(int);
	vector<int> read_son();
	vector<vector<int> > own_supervision;
	vector<multimap<int, int> > external;
	vector<set<int> > supvisors;
	bool violet_own(int);
	vector<int> sup_out(int, int);
	bool violet(int, vector<int>);
	int leaf_score(int);
	int state_to_num(int);
	int enforce(vector<int>);
	vector<int> valid_memo;
	vector<int> find_sub_set(int);
};

static vector<vector<int> > memo;
static vector<node> nodes;
static int S;
int node::enforce(vector<int> ext) {
	int force = 0;
	for (int i = 0; i < ext.size(); i++) {
		force = (1 << ext[i]) | force;
//		cout << ext[i];
	}
//	cout << "the force int " << force;
	return force;

}
bool node::violet(int state, vector<int> ext) {
	for (int i = 0; i < s; i++) {
		if (state & 1 << i) {
			if (find(ext.begin(), ext.end(), i) != ext.end()) {
				return true;
			}
		}
	}
	return false;
}
vector<int> node::sup_out(int state, int ind) {
	vector<int> ext_controlled;
	// Find corresponding indices of troopers in other node
	for (int i = 0; i < s; i++) {
		if (state & 1 << i) {
			set<int>::iterator it = supvisors[ind].find(i);
			if (it != supvisors[ind].end()) {
				pair<multimap<int, int>::iterator, multimap<int, int>::iterator> ret;
				ret = external[ind].equal_range(i);
				for (multimap<int, int>::iterator mit = ret.first;
						mit != ret.second; ++mit) {
					ext_controlled.push_back(mit->second);
				}
			}

		}
	}
	return ext_controlled;
}
int node::state_to_num(int state) {
	int num = 0;
	for (int i = 0; i < s; i++) {
		if (state & 1 << i)
			num++;
	}
	return num;
}

int node::leaf_score(int state) {
	int score;
	if (violet_own(state))
		score = 0;
	else
		score = state_to_num(state);
	return score;
}

bool node::violet_own(int state) {

	bool violated=false;
	if (valid_memo[state] == -1){
	vector<int> controlled;
	for (int i = 0; i < s; i++) {
		if (state & 1 << i)
			controlled.push_back(i);
	}
	if (controlled.size() == 1){
		valid_memo[state] = 0;
		return false;
	}

	for (int i = 0; i < controlled.size(); i++) {
		int check_ind = controlled[i];
		for (int j = 0; j < s; j++) {
			if ((own_supervision[check_ind][j] == 1)
					and (find(controlled.begin(), controlled.end(), j)
							!= controlled.end())) {
				// Found some j being controlled and is an edge
				violated = true;
				valid_memo[state] = 1;
				return true;
			}
		}

	}
	valid_memo[state] = 0;
}
	else violated = valid_memo[state];

	return violated;
}
void node::add_son(int x) {
	sons.push_back(x);
}

vector<int> node::find_sub_set(int state){
	vector<int> sub_set;
	for (int i = 0; i < s; i++) {
		if (state & 1 << i){
			int new_state = state-(1<<i);
			sub_set.push_back(new_state);
			//cout << "new state" << new_state;
		}
	}
	return sub_set;

}

vector<int> node::read_son() {
	return sons;
}

int solve(node &n, int take) {
	// Take is 0 till 1<<14 means the current Trooper will be controlled
	int res = 0;
	int id = n.index;
//	cout << "testing for " <<id << " with state: " << take << endl;
	if (memo[id][take] == -1) {
		vector<int> cur_sub_set = n.find_sub_set(take);
		int cur_res=0;
		for ( int i = 0; i < cur_sub_set.size();i++){
			cur_res = max(cur_res,solve(n,cur_sub_set[i])); // Maximum of current subset
		}
		if (n.violet_own(take)) { // If violated, look for the best of the subset
//			res = 0;
			memo[id][take] = cur_res;
			return cur_res;
		}
		int num_sons = n.sons.size();
		if (num_sons == 0) {
			res = n.state_to_num(take);
			memo[id][take] = res;
			return res;
		} else {
			res += n.state_to_num(take);
			for (int i = 0; i < num_sons; i++) {
				int new_id = n.read_son().at(i);
				vector<int> supervised = n.sup_out(take, i);
				//int one_child = 0;
				int enforced = 0;
				if (!supervised.empty()) {
					enforced = n.enforce(supervised);} // state of enforced agent in the cur child
				int not_enforced = (1<<(n.s))-enforced-1; // All allowed agents

				res += solve(nodes[new_id],not_enforced);

			}
			res = max(res,cur_res);
			memo[id][take]=res;
			return res;
		}
	} else
		res = memo[id][take];
	return res;
}

void do_case() {
	int k, s, m;
	// easiest case 1
	cin >> k >> s >> m;
	S = s;
	nodes.clear();
	nodes.resize(k);
	memo.clear();
	memo.resize(k);
	for (int i = 0; i < k; i++) {
		nodes[i].s = s;
		nodes[i].index = i;
		nodes[i].valid_memo=vector<int>(1<<s,-1);
		memo[i] = vector<int>(1 << S, -1);
		nodes[i].own_supervision = vector<vector<int> >(s, vector<int>(s, 0)); // Initilize sxs matrix
	}

	for (int i = 0; i < m; i++) {
		int u, v, h;
		cin >> u >> v >> h;
		if (u == v) {
			// In the same node
			while (h--) {
				int s1, s2;
				cin >> s1 >> s2;
				nodes[u].own_supervision[s1][s2] = 1;
				nodes[u].own_supervision[s2][s1] = 1;
			}
		} else {
			nodes[u].add_son(v);
			multimap<int, int> temp;
			set<int> sup;
			while (h--) {
				int s1, s2;
				cin >> s1 >> s2;
				temp.insert(make_pair(s1, s2));
				sup.insert(s1);
			}
			nodes[u].supvisors.push_back(sup);
			nodes[u].external.push_back(temp);
		}

	}
//	cout << "Read Finished" << endl;
//	vector<int> empty;
	int score ;
	score = solve(nodes[0],(1<<S) -1);
	cout << score << endl;
//	for (int i = 0; i < k; i++) {
//		for (int j = 0; j < 1 << S; j++) {
//			cout << "for node state " << i << " " << j << "the memo " << memo[i][j]<< endl;
//		}
//	}

}
int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) {
		do_case();
	}
	return 0;
}

////============================================================================
//// Name        : hope.cpp
//// Author      :
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
////============================================================================
//// Name        : Coin.cpp
//// Author      :
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
//#include <iostream>
//#include <vector>
//#include <map>
//#include <algorithm>
//using namespace std;
//
//
//class node {
//public:
////	int level;
//	int index;
//	vector<int> sons;
//
////	void set_level(int);
////	int get_level();
//	void add_son(int);
//	vector<int> read_son();
//};
//
//
//static vector<vector<int > > memo;
//static vector<node> nodes;
//
//
//void node::add_son(int x){
//	sons.push_back(x);
//}
//
//vector<int> node::read_son(){
//	return sons;
//}
//
//int solve(node &n, int take){
//	// Take is 1 means the current Trooper will be controlled
//	int res = 0;
//	int id = n.index;
//	if (memo[id][take] == -1){
//		int num_sons = n.sons.size();
//		if (num_sons == 0) {
////			cout << "Reached the leaf" << endl;
//			res = take ? 1:0 ; // Leaf
//		}
//		else{
//			res +=take;
//			for (int i = 0; i < num_sons; i ++){
//				int new_id = n.read_son().at(i);
//				if (take) res+= solve(nodes[new_id],take^1);
//				else res+= max(solve(nodes[new_id],0),solve(nodes[new_id],1));
//			}
//		}
////		cout << "Assign new value " << res << "at: " << id << " " << take << endl;
//		memo[id][take] = res;
//	}
//	else res = memo[id][take];
//
//	return res;
//}
//
//void do_case(){
//	int k,s,m;
//	// easiest case 1
//	cin >> k >> s >> m;
//	nodes.clear();nodes.resize(k);
//	memo.clear();memo.resize(k);
//	for (int i= 0; i < k; i ++) {
//		nodes[i].index = i;
//		memo[i] = vector<int>(2,-1);
//	}
//
//	int ignore;
//	for (int i = 0; i < m; i ++){
//		int u,v,h;
//		cin >> u >> v >> h;
//		for (int j = 0; j < h; j++ ) cin >> ignore >> ignore;
//		nodes[u].add_son(v);
//
//	}
//
//	cout << max(solve(nodes[0],0),solve(nodes[0],1)) << endl;
//
//}
//int main() {
//	ios_base::sync_with_stdio(false);
//	int t;
//	cin >> t;
//	while (t--) {
//		do_case();
//	}
//	return 0;
//}
//
//
