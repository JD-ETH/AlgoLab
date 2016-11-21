#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <climits>

using namespace std;

/*
Idea: Search for furthest possible parent
Problem: Search goes too long
Solution: Path compression on search!
*/

map<string, int> ids;
vector<int> ages;
vector<int> parents;
vector<int> oldests;
vector<string> names;
string root;

void read_species(int N){
	for (int n = 0; n < N; n++){
		string name; cin >> name;
		ids[name] = n;
		names[n] = name;
		int age; cin >> age;
		ages[n] = age;
	}
}

void read_parents(int N){
	for(int n = 0; n < N; n++){
		string child, parent; cin >> child >> parent;
		int child_id = ids[child];
		int parent_id = ids[parent];
		parents[child_id] = parent_id;
		oldests[child_id] = parent_id;
	}
	for (int n = 0; n < N+1; n++){
		if (parents[n] == -1)
			root = names[n];
	}
}

int find(int id, int age){
	int oldest = oldests[id];
	int parent = parents[id];
	int next;
	if(ages[oldest] < age)
		next = oldest;
	else
		next = parent;
	if(next >= 0 && ages[next] > age)
		return id;
	if(next < 0 && ages[ids[root]] > age)
		return id;
	if(next < 0 && ages[ids[root]] <= age)
		return ids[root];
	return oldests[id] = find(next, age);
}

void do_query(){
	string name; cin >> name;
	int age; cin >> age;

	int result = find(ids[name], age);

	if (result == -1)
		cout << root << " ";
	else
		cout << names[result] << " ";
}

void do_test(){
	int N, Q; cin >> N >> Q;
	ages = vector<int>(N);
	names = vector<string>(N);
	read_species(N);
	parents = vector<int>(N, -1);
	oldests = vector<int>(N, -1);
	read_parents(N-1);

	for(int q = 0; q < Q; q++){
		do_query();
	}

}

int main(){
	std::ios_base::sync_with_stdio(false);
	int T; cin >> T;
	for(int t = 0; t < T; t++){
		do_test();
		ids.clear();
		cout << endl;
	}
}
