//============================================================================
// Name        : bonus.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


// The forward way is a easy DP, what is the return?
// Same thing pretend to solve twice in parallel

// Every Step: x+y  The distance traveled in total
// two choices: x1, x2 The movement in x direction

#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<vector<int> > > mat3d;
mat3d memo;
int n;
bool in_bound(int x,int n,int d){
	int y = d-x;
	return (x>=0 && x <n && y>=0 && y<n);
}
int add_if_different(const vector<vector<int> > & data, int x1,int x2,int d){
	if (!(in_bound(x1,n,d) && in_bound(x2,n,d))) return 0;
	else if(x1!=x2){
		return data[x1][d-x1]+data[x2][d-x2];
	}
	else return data[x1][d-x1];
}
int solve(const vector<vector<int> > & data, int d, int x1, int x2){

	if (!(in_bound(x1,n,d) && in_bound(x2,n,d))) {
		// Out of bound and no need to calculate
		//cout << "Out of bound solve terminated\n";
		return -1;
	}
	else if (memo[d][x1][x2]== -1){ // never calculated
		if (d== (2*n -2)) {
			return 0;
			//cout << "Finished calculating\n";
		}
		// The solution will be the choise of this current step
		// Four options:
		int res = max (solve(data,d+1,x1,x2)+add_if_different(data,x1,x2,d+1), // x1 x2 remains
				solve(data,d+1,x1,x2+1)+add_if_different(data,x1,x2+1,d+1));
		res = max(solve(data,d+1,x1+1,x2)+ add_if_different(data,x1+1,x2,d+1),res);
		res = max(solve(data,d+1,x1+1,x2+1)+ add_if_different(data,x1+1,x2+1,d+1),res);
		memo[d][x1][x2]=res;
		memo[d][x2][x1]=res; // Symmetric, half of the time needed
		//cout << "Current Step at " << d << " " << x1 << " " << x2 << endl;
		//cout << "Newly calculated result: " << res << endl;
		return res;
	}

	else return memo[d][x1][x2];
}
void do_case(){

	cin >> n;
	vector<vector<int> > original(n,vector<int>(n,0));
	for (int i = 0; i < n ; i ++){
		for (int j = 0; j< n; j++){
			cin >> original[i][j];
		}
	}
	memo = mat3d(2*n-1, vector<vector<int> >(n,vector<int>(n,-1)));

	cout << solve(original, 0, 0, 0)+original[0][0] << endl;
}

int main() {

	int t;
	cin >> t;
	while(t--){
		do_case();
	}

	return 0;
}
