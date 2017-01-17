#include <iostream>
#include <vector>

using namespace std;

int main() {
	long t;
	cin >> t;
	while (t--) {
		long n;

		cin >> n;

		long mat[n][n]; // Data Storage
		for (long i = 0; i < n; i++) {
			for (long j = 0; j < n; j++) {
				cin >> mat[i][j];
			}
		}

		long total = 0;
		long colSums[2][n][n]; // 3D matrix
		for (long numRowsAfter = 0; numRowsAfter < n; numRowsAfter++) { // Num of Rows in the matrix being observed， start with most easy
			for (long row = 0; row < n - numRowsAfter; row++) { // Starting row number
				for (long col = 0; col < n; col++) { // columen number 
					if (numRowsAfter == 0) {
						colSums[numRowsAfter % 2][row][col] = mat[row][col]; // Initialize with original data 
					} else {
						colSums[numRowsAfter % 2][row][col] = 
								colSums[(numRowsAfter + 1) % 2][row][col]
										^ mat[row + numRowsAfter][col]; // Bitwise XOR.
											// odd or even, sum of current column
					} 
				}

//				for (long col = 0; col < n; col++) {
//					cout << colSums[numRowsAfter % 2][row][col] << " ";
//				}
//				cout << endl;
				long curTotal = 0; // we could just add straight to the total, this just for debugging
				long lastEvenCount = 0;
				long lastOddCount = 0;
				for (long i = 0; i < n; i++) { // Every coloum
					long val = colSums[numRowsAfter % 2][row][i]; 

					long count = 0; 
					if (val == 0) { // if even
						count++;
					}

					if (val == 0) { // if even
						count += lastEvenCount;
					} else { // if odd
						count += lastOddCount;
					}
					curTotal += count;

					lastEvenCount = count; 
					lastOddCount = (i + 1) - lastEvenCount;
				}
				total += curTotal;
//				cout << "total even matrices in row " << row << " to row "
//						<< (row + numRowsAfter) << ": " << curTotal
//						<< " (total=" << total << ")" << endl;
			}
		}
		cout << total << endl;

	}

}

