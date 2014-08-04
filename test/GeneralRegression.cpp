#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#define NUM_VAR 2
#define alpha 0.15

double predicted(double a, double b, double x)
{
	//return (a*sqrt(x)) + b;
	return a*exp(b*x);
}

double partialA(double a, double b, double x)
{
	//return sqrt(x);
	return exp(b*x);
}

double partialB(double a, double b, double x)
{
	//return 1;
	return x*a*exp(b*x);
}

int main(void)
{
	ifstream infile ("RegressionIn.txt");
	int L = 0;
	infile >> L;
	double X[L];
	double Y[L];
	for (int i = 0; i < L; i++)
		infile >> X[i] >> Y[i];
	double A = 1;
	double B = 1;
	double avgDiff = 10000;
	while (avgDiff > 0.001)
	{
		double Anew = A;
		double Bnew = B;
		avgDiff = 0;
		for (int l = 0; l < L; l++)
		{
			double difference = Y[l] - predicted(A, B, X[l]);
			avgDiff = avgDiff + pow(difference/Y[l], 2);
			Anew = Anew + (alpha * difference * partialA(A, B, X[l]));
			Bnew = Bnew + (alpha * difference * partialB(A, B, X[l]));
		}
		A = Anew;
		B = Bnew;
		avgDiff = avgDiff/L;
		cout << avgDiff << "\n";
		cout << "A: " << A << ", B: " << B << "\n";
	}

	cout << "A: " << A << ", B: " << B << "\n";
	return 0;
}
