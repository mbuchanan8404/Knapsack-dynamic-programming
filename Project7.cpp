/*
* Matthew Buchanan
* CS-340
* Project 7: Knapsack dynamic programming
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

/* Class to perform knapsack dynamic programming algorithm */
class KnapSack
{
public:
	vector<vector<int>> scoreMatrix;
	vector<int> sack;
	int score, items, maxWeight;
	int * v, * w;

	KnapSack()
	{
		score = 0;
	};

	~KnapSack()
	{
		if (v)
			delete[] v;
		if (w)
			delete[] w;
	};

	/* Use parameters from readFile() to initialize values */
	void buildKnapSack(int i, int m)
	{
		items = i;
		maxWeight = m;
		v = new int[i];
		w = new int[m];
		scoreMatrix.resize(items + 1, vector<int>(maxWeight + 1, 0));
	};

	/* Function to read input file and construct knapsack */
	void readFile()
	{
		int a = 0, b = 0;
		ifstream in;
		in.open("knapsack.txt");
		in >> a >> b;
		buildKnapSack(a, b);
		for (int i = 0; i < items; i++)
		{
			in >> w[i];
			in >> v[i];
		}
	}

	/* Build the score map and perform traceback to fill the sack */
	void fillMap()
	{
		// Build score map
		for (int i = 1; i < items + 1; i++)
		{
			for (int j = 1; j < maxWeight + 1; j++)
			{
				if (w[i - 1] <= j && v[i - 1] + scoreMatrix[i - 1][j - w[i - 1]] > scoreMatrix[i - 1][j])// if i is less than weight limit and is the optimal choice
					scoreMatrix[i][j] = scoreMatrix[i - 1][j - w[i - 1]] + v[i - 1];
				else
					scoreMatrix[i][j] = scoreMatrix[i - 1][j];// do not include item i
			}
		}
		score = scoreMatrix[items][maxWeight];
		// Trace back and add items to knapsack
		int i = items;
		int j = maxWeight;
		while (i > 0 && j > 0)
		{
			if (scoreMatrix[i - 1][j - w[i - 1]] + v[i - 1] == scoreMatrix[i][j])// if 
			{
				sack.push_back(i);
				j -= w[i - 1];
			}
			--i;
		}
	}

	/* Display contents of sack */
	void displaySack()
	{
		cout << "Value of knapsack contents: " << score << endl;
		cout << "Contents of knapsack (weight, value) :" << endl;
		for (int i = sack.size() - 1; i >= 0; --i)
			cout << "Item #" << sack[i] << "  " << '<' << w[sack[i] - 1] << ", " << v[sack[i] - 1] << '>' << endl;
	}

	/* Display raw score map */
	void displayMap()
	{
		cout << "Score Map:" << endl;
		for (int i = 0; i < items + 1; i++)
		{
			for (int j = 0; j < maxWeight + 1; j++)
				cout << setw(2) << scoreMatrix[i][j] << "  ";
			cout << endl;
		}
		cout << endl << endl;
	}

};/* End class KnapSack */


/* Begin main */
int main()
{
	KnapSack test;
	test.readFile();
	test.fillMap();
	test.displayMap();
	test.displaySack();
	system("PAUSE");
}
/* End main */