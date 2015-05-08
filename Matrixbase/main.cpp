#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>

#include "function.hpp"

using namespace std;

int main()
{
	srand(time(NULL));

	vector<vector<float>> A;
	vector<vector<float>> B;

	//generate_matrix(128, 1024, "A.txt");
	//generate_matrix(1024, 128, "B.txt");
	
	read_matrix(A, "A.txt");
	//read_matrix(B, "B.txt");
	read_matrix_transpose(B, "B.txt");

	//if (A[0].size() != B.size())
	if (A[0].size() != B[0].size())
	{
		cout << "Matrix dimension error" << endl;
		return -1;
	}
	else
	{
		vector<vector<float>> C;
		C.resize(A.size());
		for (int a = 0; a < A.size(); a++)
		{
			//C[a].resize(B[0].size(), 0);
			C[a].resize(B.size(), 0);
		}

		cout << "Start Matrix Multiplication" << endl;
		//cout << "[ " << A.size() << " x " << A[0].size() << " ] x [ " << B.size() << " x " << B[0].size() << " ] = [ " << C.size() << " x " << C[0].size() << " ]" << endl;
		cout << "[ " << A.size() << " x " << A[0].size() << " ] x [ " << B[0].size() << " x " << B.size() << " ] = [ " << C.size() << " x " << C[0].size() << " ]" << endl;
		chrono::system_clock::time_point StartTime = chrono::system_clock::now();
		//---------------Matrix Multiplication---------------//

		/* multiplication with transposed B */
		for (int i = 0; i < A.size(); i++)
		{
			for (int j = 0; j < B.size(); j++)
			{
				for (int k = 0; k < A[0].size(); k++)
				{
					C[i][j] += A[i][k] * B[j][k];
				}
			}
		}
		

		/* block 2D-partitioning
		for (int k = 0; k < A.size(); k++)
		{
			for (int i = 0; i < A.size(); i++)
			{
				for (int j = 0; j < B.size(); j++)
				{
					C[i][j] += A[i][i] * B[i][j];
				}
			}

			for (int i = 0; i < A.size(); i++)
			{
				float temp1 = A[i].back();
				A[i].pop_back();
				A[i].emplace(A[i].begin(), temp1);
			}

			vector<float> temp2 = B.back();
			B.pop_back();
			B.emplace(B.begin(), temp2);
		}
		*/

		/* changing sequence
		for (int k = 0; k < B.size(); k++)
		{
			for (int i = 0; i < A.size(); i++)
			{
				for (int j = 0; j < B[0].size(); j++)
				{
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		*/

		/* original
		for (int i = 0; i < A.size(); i++)
		{
			for (int j = 0; j < B[0].size(); j++)
			{
				for (int k = 0; k < B.size(); k++)
				{
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
		*/

		//---------------Matrix Multiplication---------------//
	
		chrono::system_clock::time_point EndTime = chrono::system_clock::now();
		chrono::microseconds micro = chrono::duration_cast<chrono::microseconds>(EndTime - StartTime);
		cout << "Matrix Multiplication done" << endl;
		cout << "Time : " << micro.count() << endl;

		write_matrix(C, "C.txt");

		getchar();
		return 0;
}
}