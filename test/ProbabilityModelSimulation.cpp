#include <iostream>
#include <fstream>
#include <cmath>
#include <bitset>
#include <cstdlib>
using namespace std;
#define NUM_ROWS 128
#define NUM_COLS 32
#define NUM_LAYERS 4
#define NUM_BITS 15

int main(int args, char* argv)
{
	//ifstream loadFile ("LoadData.txt");
	//ifstream runFile ("RunData.txt");
	ifstream infile ("Instructions.txt");
	int numI = 0;
	infile >> numI;
	double freq = atof(argv[1]);
	int camInfo[NUM_ROWS][NUM_COLS][NUM_LAYERS];
	int containsData[NUM_ROWS*NUM_COLS] = {0};
	int nandBits[NUM_LAYERS][2][2][2][2];
	for (int i1 = 0; i1 < 2; i1++)
	{
		for (int i2 = 0; i2 < 2; i2++)
		{
			for (int i3 = 0; i3 < 2; i3++)
			{
				for (int i4 = 0; i4 < 2; i4++)
				{
					nandBits[i1][i2][i3][i4] = 0;
				}
			}
		}
	}
	
	int possMatches = 0;
	double predictedMatches = 0;
	for (int i = 0; i < numI; i++)
	{
		char type;
		infile >> type;
		if (type == 'l')
		{
			int row, col;
			infile >> row >> col;
			if (containsData[(NUM_COLS*row)+col] == 1)
			{
				for (int layerr = 0; layerr < NUM_LAYERS; layerr++)
				{
					bitset <NUM_BITS> bitRep (camInfo[row][col][layerr]);
					nandBits[layerr][bitRep[0]][bitRep[1]][bitRep[2]][bitRep[3]]--;
				}
			}
			for (int layer = 0; layer < NUM_LAYERS; layer++)
			{
				infile >> camInfo[row][col][layer];
				bitset <NUM_BITS> newBitRep (camInfo[row][col][layer]);
				nandBits[layer][newBitRep[0]][newBitRep[1]][newBitRep[2]][newBitRep[3]]++;
			}
			containsData[(NUM_COLS*row)+col] = 1;
		}
		else
		{
			int row;
			infile >> row;
			int pattern[NUM_LAYERS];
			for (int layer = 0; layer < NUM_LAYERS; layer++)
				infile >> pattern[layer];
			double* colProcess = (double) malloc(sizeof(double) * NUM_COLS);
			int sizeColProcess = 0;
			for (int c = 0; c < NUM_COLS; c++)
			{
				double probabilities[NUM_LAYERS];
				int flag = 1;
				if (containsData[(row*NUM_COLS) + c] == 0)
				{
					cout << "WARNING: THIS LOCATION CONTAINS NO DATA CURRENTLY; NOT COUNTING AS A MISMATCH DUE TO THIS WARNING...\n";
					continue;
				}
				for (int l = 0; l < NUM_LAYERS; l++)
				{
					if (camInfo[row][c][l] != pattern[l])
					{
						flag = 0;
						break;
					}
					bitset <NUM_BITS> bitRepCheckInfo (camInfo[row][c][l]);
					probabilities[l] = predictedProbability(freq, (double) nandBits[bitRepCheckInfo[0]][bitRepCheckInfo[1]][bitRepCheckInfo[2]][bitRepCheckInfo[3]]/(NUM_ROWS*NUM_COLS), c);
				}
				if (flag == 1)
				{
					colProcess[sizeColProcess] = pIE(probabilities, NUM_LAYERS);
					sizeColProcess++;
				}
			}
			possMatches++;
			if (sizeColProcess = 0)
				predictedMatches = predictedMatches + 1;
			else
				predictedMatches = predictedMatches + pIE(colProcess, sizeColProcess);
		}
	}

	cout << "Accuracy: " << predictedMatches/possMatches << "\n";

	return 0;
}
