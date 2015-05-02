#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int read_matrix(vector<vector<float>> &M, string filename)
{
	ifstream input_matrix;
	input_matrix.open(filename);
	if (!input_matrix.good())
	{
		cout << "Could not open " << filename << endl;
		return -1;
	}
	int rows = 0;
	int cols = 0;
	input_matrix >> rows;
	input_matrix >> cols;

	M.resize(rows);

	for (int i = 0; i < rows; i++)
	{
		M[i].resize(cols, 0);
		for (int j = 0; j < cols; j++)
		{
			input_matrix >> M[i][j];
		}
	}
	input_matrix.close();
	if (rows != M.size() || cols != M[0].size())
	{
		cout << "Input failed" << endl;
		return -1;
	}
	return 0;
}

int write_matrix(vector<vector<float>> &M, string filename)
{
	ofstream output_matrix;
	output_matrix.open(filename);
	if (!output_matrix.good())
	{
		cout << "Could not open " << filename << endl;
		return -1;
	}
	int rows = M.size();
	int cols = M[0].size();

	output_matrix << rows << " " << cols << endl;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			output_matrix << M[i][j] << " ";
		}
		output_matrix << endl;
	}
	output_matrix.close();
	return 0;
}

int generate_matrix(int rows, int cols, string filename)
{
	vector<vector<float>> M;
	M.resize(rows);
	for (int a = 0; a < rows; a++)
	{
		M[a].resize(cols, 0);
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			float temp = -500 + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 1000);
			M[i][j] = temp;
		}
	}

	write_matrix(M, filename);

	return 0;
}