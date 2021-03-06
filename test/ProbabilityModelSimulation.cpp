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

//Probability of a success
double predictedProbability(double frequency, double N, int c)
{
	double A = -0.311404;
	double B = -21.5501;
	double C = 42.639;
	double mu = 13.43311;
	double alpha = -3.14532;
	double beta = 9.86011;
	double preliminaryEfficiency = exp((A*frequency)+(B*sqrt(N))+C)/(1+exp((A*frequency)+(B*sqrt(N))+C));
	double stdDev = alpha*sqrt(preliminaryEfficiency) + beta;
	cout << preliminaryEfficiency << " " << stdDev << " " << N << "\n";
	double sumCols = 0.0;
	for (int k = 0; k < NUM_COLS; k++)
	{
		sumCols = sumCols + ( (1.0/(stdDev*sqrt(2*acos(-1.0))))*exp(-0.5*pow((k-mu)/stdDev, 2)) );
	}
	double stepSize = 0.01;
	double integral1 = 0.0;
	for (double c2 = 0; c2 < NUM_COLS; c2++)
	{
	double failureProb = 0.0;
	for (double k = c2-0.5; k < c2+0.5; k = k+stepSize)
	{
		double fVal1 = /*NUM_COLS*(1-preliminaryEfficiency)*/(1.0/(stdDev*sqrt(2*acos(-1.0))))*exp(-0.5*pow((k-mu)/stdDev, 2));
		double fVal2 = /*NUM_COLS*(1-preliminaryEfficiency)*/(1.0/(stdDev*sqrt(2*acos(-1.0))))*exp(-0.5*pow((k+stepSize-mu)/stdDev, 2));
		failureProb = failureProb + ((fVal1+fVal2)*0.5*stepSize);
	}
	integral1 = integral1 + failureProb;
	}
	double multiplier = (1.0-preliminaryEfficiency)*NUM_COLS/integral1;
	double failureProb = 0.0;
	for (double k = c-0.5; k < c+0.5; k = k+stepSize)
	{
		double fVal1 = multiplier*(1.0/(stdDev*sqrt(2*acos(-1.0))))*exp(-0.5*pow((k-mu)/stdDev, 2));
		double fVal2 = multiplier*(1.0/(stdDev*sqrt(2*acos(-1.0))))*exp(-0.5*pow((k+stepSize-mu)/stdDev, 2));
		failureProb = failureProb + ((fVal1+fVal2)*0.5*stepSize);
	}
	//double successProb = NUM_COLS*preliminaryEfficiency*(1-(exp(pow((c-mu)/stdDev, 2))/sumCols));
	//double failureProb = NUM_COLS*(1.0-preliminaryEfficiency)*(1.0/(stdDev*sqrt(2*acos(-1.0))))*exp(-0.5*pow((c-mu)/stdDev, 2))/sumCols;
	//failureProb = failureProb/(1/stepSize);
	cout << failureProb << " " << c << "\n";
	//return successProb;
	return 1-failureProb;
}

double group(double* p, int size, int currSize, int ind, int maxLength)
{
	if (currSize == size) //|| (ind == maxLength))
		return 1;
	double add1 = p[ind]*group(p, size, currSize+1, ind+1, maxLength);
	if ((size - currSize) == (maxLength - ind))
		return add1;
	return add1 + group(p, size, currSize, ind+1, maxLength);
}

double pIE(double* p, int size)
{
	/*if (size == 1)
	{
		cout << "yup\n";
		return p[0];
	}*/
	double result = 0;
	for (int s = 1; s <= size; s++)
	{
		//cout << (pow(-1.0, s-1)*group(p, s, 0, 0, size)) << "\n";
		result = result + (pow(-1.0, s-1)*group(p, s, 0, 0, size));
		//cout << result << "\n";
	}
	return result;
}


int main(int args, char** argv)
{
	//ifstream loadFile ("LoadData.txt");
	//ifstream runFile ("RunData.txt");
	/*double* example = (double*) malloc(sizeof(double) * 10);
	example[0] = 1;
	example[1] = 2;
	example[2] = 3;
	example[3] = 4;
	cout << pIE(example, 1) << "\n";*/
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
					for (int l = 0; l < NUM_LAYERS; l++)
						nandBits[l][i1][i2][i3][i4] = 0;
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
					nandBits[layerr][bitRep[NUM_BITS-1-0]][bitRep[NUM_BITS-1-1]][bitRep[NUM_BITS-1-2]][bitRep[NUM_BITS-1-3]]--;
				}
			}
			for (int layer = 0; layer < NUM_LAYERS; layer++)
			{
				infile >> camInfo[row][col][layer];
				bitset <NUM_BITS> newBitRep (camInfo[row][col][layer]);
				nandBits[layer][newBitRep[NUM_BITS-1-0]][newBitRep[NUM_BITS-1-1]][newBitRep[NUM_BITS-1-2]][newBitRep[NUM_BITS-1-3]]++;
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
			double* colProcess = (double*) malloc(sizeof(double) * NUM_COLS);
			int sizeColProcess = 0;
			for (int c = 0; c < NUM_COLS; c++)
			{
				double probabilities[NUM_LAYERS];
				int flag = 1;
				if (containsData[(row*NUM_COLS) + c] == 0)
				{
					cout << "WARNING: THIS LOCATION CONTAINS NO DATA CURRENTLY; NOT COUNTING AS A FAILURE...\n";
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
					probabilities[l] = 1-predictedProbability(freq, (double) nandBits[l][bitRepCheckInfo[NUM_BITS-1-0]][bitRepCheckInfo[NUM_BITS-1-1]][bitRepCheckInfo[NUM_BITS-1-2]][bitRepCheckInfo[NUM_BITS-1-3]]/(NUM_ROWS*NUM_COLS), c);
					//cout << probabilities[l] << "\n";
				}
				if (flag == 1)
				{
					colProcess[sizeColProcess] = pIE(probabilities, NUM_LAYERS);
					cout << colProcess[sizeColProcess] << "\n";
					sizeColProcess++;
				}
			}
			possMatches++;
			if (sizeColProcess == 0)
				predictedMatches = predictedMatches + 1;
			else
			{
				//cout << sizeColProcess << "BBBBBBB\n";
				double expected = 1 - pIE(colProcess, sizeColProcess);
				predictedMatches = predictedMatches + expected;
				cout << expected << "AAAAAAAAAAAAAAAAAAAAA\n";
			}
		}
	}
	

	for (int t1 = 0; t1 < NUM_LAYERS; t1++)
	{
		for (int t2 = 0; t2 < 2; t2++)
		{
			for (int t3 = 0; t3 < 2; t3++)
			{
				for (int t4 = 0; t4 < 2; t4++)
				{
					for (int t5 = 0; t5 < 2; t5++)
						cout << nandBits[t1][t2][t3][t4][t5] << " ";
				}
			}
		}
	}
	cout << "\n";
	cout << predictedMatches << " " << possMatches << "\n";
	cout << "Accuracy: " << predictedMatches/possMatches << "\n";

	return 0;
}
