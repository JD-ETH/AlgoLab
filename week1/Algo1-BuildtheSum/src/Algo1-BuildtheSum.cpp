//============================================================================
// Name        : Algo1-BuildtheSum.cpp
// Author      : JD
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

int main() {
	int test_case;
	int num;
	int read_counter;
	//cout << "Input an integer, defining the number of tests...";
	cin >> test_case;
	for (int test_num =0; test_num < test_case ; test_num ++){
		float curr_sum=0;
		read_counter = 0;

		// Reading Inputs
		//cout << "Please input a integer, describing how many numbers there are...";
		cin >> num;
		while (read_counter < num){
			float curr_num;
			cin >> curr_num;
			read_counter +=1;
			curr_sum += curr_num;
		}
		cout << curr_sum  << endl;
	}

	return 0;
}
