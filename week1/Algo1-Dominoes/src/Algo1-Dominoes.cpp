//============================================================================
// Name        : Algo1-Dominoes.cpp
// Author      : JD
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include <deque>
#include <algorithm>
#include <vector>
int main() {
	ios_base::sync_with_stdio(false);
	int test_case;

	cin >> test_case;
	for (int test_num = 0; test_num < test_case; test_num++) {
		int num;
		int counter = 0;
		vector<int> data;
		cin >> num;
		while (counter < num) {
			int current_height;
			cin >> current_height;
			data.push_back(current_height);
			counter += 1;
		}
		deque<int> mydeque;
		mydeque.push_back(data[0]); // Initialize the deque
		int start_index = 1;
		int data_index = start_index;
		int range = data[0];
		while (range > mydeque.size()) {
			// First append on the end of deque
			for (vector<int>::iterator itr = data.begin()+ data_index;itr!=data.begin()+start_index+range-1; itr++){
				mydeque.push_back(*itr);
			}

			// Next look for most influencial element in the deque
			deque<int> ranking_deque(mydeque); // Deque plus its index
			for (unsigned int i= 0; i<ranking_deque.size(); i ++){
				ranking_deque[i] += i;
			}
			deque<int>::iterator itr_max = max_element(ranking_deque.begin(),ranking_deque.end());
			int max_index = itr_max - ranking_deque.begin();

			// Update the start index

			data_index = start_index + mydeque.size()-1;
			start_index += max_index;
			range = *itr_max - max_index;
			// Finally discard everything before the maximum index
			for (int i = 0; i<max_index  ; i ++){
				mydeque.pop_front();
			}
			if (start_index + range -1 > data.size()) {range= data.size() +1-start_index; break;}
		}
		cout << start_index + range -1 << endl;
//		bool TERMINATE = false;
//		unsigned int start_index = 0;
//		unsigned int end_index;
//		unsigned int current_end_index;
//		while (!TERMINATE) {
//			current_end_index = start_index + data.at(start_index) - 1;
//			if (current_end_index > (num-1)) {
//				end_index = num-1;
//				break;
//			}
//			unsigned int temp_end = current_end_index;
//			for (unsigned int i = start_index; i < (current_end_index + 1); i++) {
//				end_index = data.at(i) + i - 1;
//
//				if (end_index > temp_end) {
//					temp_end = end_index;
//				}
//			}
//			if (temp_end == current_end_index) {
//				TERMINATE = true;
//				end_index = current_end_index;
//			} else {
//
//				start_index = temp_end;
//			}
//			end_index = temp_end;
//		}
//		cout << (end_index + 1) << endl;
	}
	return 0;
}
