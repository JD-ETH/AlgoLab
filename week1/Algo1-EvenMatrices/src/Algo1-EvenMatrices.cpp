//============================================================================
// Name        : Algo1-EvenMatrices.cpp
// Author      : JD
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
//#include <cstdio>
//#include <ctime>
using namespace std;

int main() {
//	ios_base::sync_with_stdio(false);
//    std::clock_t start;
//    double duration;
//    start = std::clock();
	int test_case;
	cin >> test_case;
	for (int test_num = 0; test_num < test_case; test_num++) {
		int dim;
		cin >> dim;
		vector<vector<int> > data;
		for (int i = 0; i < dim; i++) {
			vector<int> curr_row;
			for (int j = 0; j < dim; j++) {
				int curr_num;
				cin >> curr_num;
				curr_row.push_back(curr_num);
			}
			data.push_back(curr_row);
		}
		// Finish reading

		int sum = 0;
//		vector<vector<int> > par_sum;
		vector<vector<int> > par_sum_odd;
//		vector<int> par_sum_row_first;
		vector<int> par_sum_odd_row_first;
		for (int j = 0; j < dim; j++) {
			sum += data[0][j];
//			par_sum_row_first.push_back(sum);
			par_sum_odd_row_first.push_back(sum % 2);
		}
//		par_sum.push_back(par_sum_row_first); // Calculate first row
		par_sum_odd.push_back(par_sum_odd_row_first);
		for (int i = 1; i < dim; i++) {
//			vector<int> par_sum_row;
			vector<int> par_sum_odd_row;
			int row_sum = 0;
			for (int j = 0; j < dim; j++) {
				row_sum += data[i][j];
//				par_sum_row.push_back(par_sum[i - 1][j] + row_sum);
				par_sum_odd_row.push_back((par_sum_odd[i-1][j]+row_sum) % 2);
			}
//			par_sum.push_back(par_sum_row);
			par_sum_odd.push_back(par_sum_odd_row);
		}
		// Calculated partial summations

//		// three structures containing information about number of odds so far;(EXCLUDING CURRENT)
//		vector<vector<int> > row_sofar;
//		vector<vector<int> > row_sofar_ev;
//		for (int i = 0; i < dim; i++) {
//			vector<int> row_sofar_row;
//			vector<int> row_sofar_ev_row;
//			int counter = 0;
//			row_sofar_ev_row.push_back(0);
//			for (int j = 0; j < dim; j++) {
//				row_sofar_row.push_back(counter);
//				counter += par_sum_odd[i][j];
//			}
//			for (int j = 1; j < dim; j++) {
//				row_sofar_ev_row.push_back(j - row_sofar_row[j]);
//
//			}
//			row_sofar.push_back(row_sofar_row);
//			row_sofar_ev.push_back(row_sofar_ev_row);
//		}

		vector<vector<vector<int> > > stripe_sum; // indices, row begins, row number, column length
		// Calculate the "Stripe Sum"
		stripe_sum.push_back(par_sum_odd); // First for all cases starting from line 0
		for (int i = 1; i < dim; i++) {
			vector<vector<int> > stripe_sum_d;
			vector<int> stripe_row_first;
			int row_stripe_sum=0;
			for (int k = 0; k < dim; k++) {
				row_stripe_sum += data[i][k];
				stripe_row_first.push_back(row_stripe_sum % 2);
			}
			stripe_sum_d.push_back(stripe_row_first);
			for (int deltaj = 1; deltaj < (dim - i); deltaj++) {
				int row_sum_curr = 0;
				vector<int> stripe_sum_row;
				for (int k = 0; k < dim; k++) {
					row_sum_curr += data[i + deltaj][k];
					stripe_sum_row.push_back(
							(row_sum_curr + stripe_sum_d[deltaj-1][k]) % 2);
				}
				stripe_sum_d.push_back(stripe_sum_row);
			}
			stripe_sum.push_back(stripe_sum_d);
		}

		vector<vector<int> > col_sofar; // [COL_INDEX][ROW_INDEX]
		vector<vector<int> > col_sofar_ev;
		for (int j = 0; j < dim; j++) {  // For col j
			vector<int> col_sofar_row;
			vector<int> col_sofar_row_ev;
			int counter = 0;
			col_sofar_row_ev.push_back(0);
			for (int i = 0; i < dim; i++) { // add all from row i
				col_sofar_row.push_back(counter);
				counter += par_sum_odd[i][j];

			}
			for (int i = 1; i < dim; i++) {
				col_sofar_row_ev.push_back(i - col_sofar_row[i]);
			}
			col_sofar.push_back(col_sofar_row);
			col_sofar_ev.push_back(col_sofar_row_ev);
		}

		vector<vector<vector<int> > > stripe_sofar;
		vector<vector<vector<int> > > stripe_sofar_ev;

		for (int i = 0; i < dim; i++) {
			vector<vector<int> > stripe_sofar_d;
			vector<vector<int> > stripe_sofar_d_ev;

			for (int j = 0; j < (dim - i); j++) {
				vector<int> stripe_sofar_col;
				vector<int> stripe_sofar_col_ev;

				int counter = 0;
				int counter_ev = 0;
				stripe_sofar_col_ev.push_back(counter_ev);
				stripe_sofar_col.push_back(counter); // Initialize the first one
				for (int k = 0; k < dim-1; k++) {
//					stripe_sofar_col.push_back(
//							stripe_sofar_col.back() + col_sofar[k][i + j]
//									- col_sofar[k][i]
//									+ stripe_sum[i][j][k - 1]); // So far exclude current, include last k-1
				if (stripe_sum[i][j][k]) {counter+=1;}
				else {counter_ev+=1;}
				stripe_sofar_col.push_back(counter);
				stripe_sofar_col_ev.push_back(counter_ev);
				}
				stripe_sofar_d.push_back(stripe_sofar_col);
				stripe_sofar_d_ev.push_back(stripe_sofar_col_ev);
			}
			stripe_sofar.push_back(stripe_sofar_d);
			stripe_sofar_ev.push_back(stripe_sofar_d_ev);
		}

//
//		vector<vector<int> > block_sofar;
//		vector<vector <int> > block_sofar_ev;
//		block_sofar.push_back(row_sofar[0]);
//		block_sofar_ev.push_back(row_sofar_ev[0]);
//		for (int i = 1; i < dim; i++) {
//			vector<int> block_row;
//			vector<int> block_row_ev;
//			for (int j = 0; j < dim; j++) {
//
//				block_row.push_back(block_sofar[i - 1][j] + row_sofar[i][j]);
//				block_row_ev.push_back(block_sofar_ev[i-1][j] + row_sofar_ev[i][j]);
//			}
//
//			block_sofar.push_back(block_row);
//			block_sofar_ev.push_back(block_row_ev);
//		}

		int pairs = 0;
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) { // Doubly iterate through matrix
				// Directly add the number of even pairs
				if (par_sum_odd[i][j] ) { // In case the currently value is odd
//					pairs += (col_sofar[j][i]+row_sofar[i][j]); // current column and current row
					pairs += (col_sofar[j][i]+stripe_sofar[0][i][j]); // current column and current row

					//          if l = 0         k = 0
//					cout << " i j " << i << j << " pairs:" << pairs<<endl;
				} else {
//					pairs += (col_sofar_ev[j][i]+row_sofar_ev[i][j]+1); // current column and current row and itself
					pairs += (col_sofar_ev[j][i]+stripe_sofar_ev[0][i][j]+1);
					//          if l = 0         k = 0
//					cout << " i j " << i << j  << " pairs:" << pairs<<endl;
				}
//				if (par_sum[i][j] % 2 == 0) { // If the current sum is even

				for (int k = 1; k <= i; k++) { // Iterates over k rows
					if ((par_sum_odd[i][j] + par_sum_odd[k-1][j])%2) { // Currently odd without upper block
						pairs += stripe_sofar[k][i - k][j]; // odd stripes so far

//						cout << " i j k " << i << j << k << "pairs: " << pairs<<endl;
					} else {
						pairs += stripe_sofar_ev[k][i-k][j]; // All even stripes before

//						cout << " i j k " << i << j << k  << "pairs: " << pairs<<endl;
					}
				}
//				}
//					// add 1, add all even in same row before, add all even in same column before,
//					// add ev-row x ev-col x ev-matrix
//					// add ev  odd   odd
//					// add od od ev
//					// add od ev od
//					pairs += row_sofar_ev[i][j] // Same row sofar
//							+ col_sofar_ev[j][i] // Same col so far
//							+ 1 // Itself
//							+ row_sofar_ev[i][j] * col_sofar_ev[j][i] * block_sofar_ev[i][j] // even, even, even
//							+ row_sofar[i][j]*col_sofar[j][i]*block_sofar_ev[i][j] // od,od ev
//							+ row_sofar[i][j]*col_sofar_ev[j][i]*block_sofar[i][j] // od,ev,od
//							+ row_sofar_ev[i][j] * col_sofar[j][i]*block_sofar[i][j]; // ev, od od
//				}
//				if (par_sum[i][j] % 2 == 1) { // If the current sum is odd
//					// add all odd in same row before, add all odd in same column before,
//					// add od-row x od-col x od-matrix
//					// add ev  ev   odd
//					// add od ev ev
//					// add ev od ev
//					pairs += row_sofar[i][j] // Same row sofar
//							+ col_sofar[j][i] // Same col so far
//							+ row_sofar[i][j]*col_sofar[j][i]*block_sofar[i][j] // od, od, od
//							+ row_sofar[i][j]*col_sofar_ev[j][i]*block_sofar_ev[i][j]// od,ev, ev
//							+ row_sofar_ev[i][j]*col_sofar_ev[j][i]*block_sofar[i][j] // ev,ev,od
//							+ row_sofar_ev[i][j]*col_sofar[j][i]*block_sofar_ev[i][j]; // ev, od ev
//				}
//				S_block = Sij-Skj-Stripe_ijk
//				if (par_sum[i][j] % 2 == 0) { // If even
//					pairs += 1 + row_sofar_ev[i][j] + col_sofar_ev[j][i];}
//				else {pairs += row_sofar[i][j] + col_sofar[j][i];}
//				for (int k = 1; k <= i; k++) {
//					for (int l = 1; l <= j; l++) {
//						if (k == 0 and l == 0) {
//							if (par_sum[i][j] % 2 == 0) {
//								pairs += 1;
////								cout << "i and j,k l" << i << j << k << l;
//							}
//						} else if (k == 0) {
//							if ((par_sum[i][j] - par_sum[i][l-1]) % 2 == 0) {
//								pairs += 1;
////								cout << "i and j,k l" << i << j << k << l;
//							}
//						} else if (l == 0) {
//							if ((par_sum[i][j] - par_sum[k - 1][j]) % 2 == 0) {
//								pairs += 1;
////								cout << "i and j,k l" << i << j << k << l;
//							}
//						}
//						// Sij-Sil-Skj+Skl
//						else {
//							if ((par_sum_odd[i][j] - par_sum_odd[i][l - 1]
//									- par_sum_odd[k - 1][j] + par_sum_odd[k - 1][l - 1])
//									% 2 == 0) {
//								pairs += 1;
////								cout << "i and j,k l" << i << j << k << l;
//							}
//						}
//					}

			}
		}

		cout << pairs << endl;

//	    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
//
//	    std::cout<<"printf: "<< duration <<'\n';
	}
	return 0;
}
