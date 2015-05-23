#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
extern "C"
{
#include <immintrin.h>
}

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

		/* transposed, using pointers */
		for (int i = 0; i < A.size(); i++)
		{
			for (int j = 0; j < B.size(); j++)
			{
				float* a = &A[i][0];
				float* b = &B[j][0];
				float temp = 0;
				for (int k = 0; k < A[0].size(); k++)
				{
					temp += *a++ * *b++;
				}
				C[i][j] = temp;
			}
		}

		/* AVX
		__m256 reg00, reg01, reg02, reg03, reg04;
		float scratch[8];
		
		for (int i = 0; i < A.size(); i++)
		{
			for (int j = 0; j < B.size(); j++)
			{
				float temp = 0.0;
				for (int k = 0; k < A[0].size(); k = k + 32)
				{
					reg00 = _mm256_loadu_ps(&A[i][k]);
					reg01 = _mm256_loadu_ps(&B[j][k]);
					reg00 = _mm256_mul_ps(reg00, reg01);

					reg01 = _mm256_loadu_ps(&A[i][k + 8]);
					reg02 = _mm256_loadu_ps(&B[j][k + 8]);
					reg01 = _mm256_mul_ps(reg01, reg02);

					reg00 = _mm256_add_ps(reg00, reg01);

					reg01 = _mm256_loadu_ps(&A[i][k + 16]);
					reg02 = _mm256_loadu_ps(&B[j][k + 16]);
					reg01 = _mm256_mul_ps(reg01, reg02);

					reg02 = _mm256_loadu_ps(&A[i][k + 24]);
					reg03 = _mm256_loadu_ps(&B[j][k + 24]);
					reg02 = _mm256_mul_ps(reg02, reg03);

					reg01 = _mm256_add_ps(reg01, reg02);
					reg00 = _mm256_add_ps(reg00, reg01);

					_mm256_storeu_ps(scratch, reg00);
					temp += scratch[0] + scratch[1] + scratch[2] + scratch[3]
						+ scratch[4] + scratch[5] + scratch[6] + scratch[7];
				}
				C[i][j] = temp;
			}
		}
		*/

		/* multiplication with transposed B
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