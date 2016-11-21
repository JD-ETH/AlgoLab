//============================================================================
// Name        : Algo1-DeckofCards.cpp
// Author      : JD
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
	int test_case;
	cin >> test_case;
	for (int test_num = 0; test_num < test_case; test_num++) {
		// Read data and compute partial sum
		int num;
		cin >> num;
		int goal;
		cin >> goal;
		vector<int> data;
		vector<int> parsum;
		int curr_sum = 0;
		parsum.push_back(curr_sum); // parsum first unit is 0
		for (int i = 0; i < num; i++) {

			int cur_num;
			cin >> cur_num;
			curr_sum += cur_num;
			data.push_back(cur_num);
			parsum.push_back(curr_sum);
		}

		// double iterate through
		int score = 2147483646;
		int score_temp = 1;
		int index_l;
		int index_r;

		for (int i = 1; i < num; i++) {
			for (int j = i; j < num; j++) {
				score_temp =   goal- parsum.at(j) + parsum.at(i - 1); // now index start from 1
				if (abs(score_temp) < score) { // Update as current best
					index_l = i - 1;
					index_r = j - 1;
					score = abs(score_temp);

				}

				if (score_temp < 0){ // Sum already bigger then goal
					break;
				}
				if (score_temp == 0) {
					index_l = i - 1;
					index_r = j - 1;
					goto stop;
				}

			}
		}
		stop: cout << index_l << " " << index_r << endl;

	}
	return 0;
}
