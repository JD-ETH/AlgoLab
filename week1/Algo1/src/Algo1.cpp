//============================================================================
// Name        : Algo1.cpp
// Author      : JD
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

int main() {
	// Define Variables



	int test_case;
	// Reading Inputs
	cin >> test_case;
	for (int test_num = 0; test_num < test_case; test_num++) {
		int correct_pairs = 0;
		int num;
		int read_counter = 0;
		int temp_sum = 0;
		int num_odd = 0;
		vector<int> raw_data;
		vector<int> partial_sum;
		vector<int> odd_partial;
		vector<int> odd_sofar;
		//cout
		//		<< "Please input a integer, describing how many numbers there are...";
		cin >> num;
		while (read_counter < num) {
			int curr_num;
			cin >> curr_num;
			raw_data.push_back(curr_num);
			read_counter += 1;
		}
		//cout << "Finish reading all " << num << " values \n";

		// Calculate Partial Sum
		for (int i = 0; i < num; i++) {
			odd_sofar.push_back(num_odd); // Number of odd numbers until i-1
			temp_sum += raw_data[i];
			partial_sum.push_back(temp_sum);
			odd_partial.push_back(temp_sum % 2);
			num_odd += (temp_sum % 2);

		}
		//cout << "Calculated partial Sum...Now find pairs\n";

		// Loop and find sum
		for (int i = 0; i < num; i++) {
			if (partial_sum[i] % 2) {
				correct_pairs += odd_sofar[i]; // if odd, Correct pairs are the ones until i/1
			} else {
				correct_pairs += (i + 1 - odd_sofar[i]); // if even, correct pairs are the even ones before plus 1
			}
		}
		cout << correct_pairs << endl;
	}
	return 0;
}
