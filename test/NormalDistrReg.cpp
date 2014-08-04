#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#define alpha 0.1

double normal(double m, double s, double x)
{
	return (1.0/(s*sqrt(2*acos(-1.0)))) * exp(-0.5*pow(((x-m)/s), 2));
}

double partialMu(double m, double s, double x)
{
	return ((x-m)/(pow(s, 3)*sqrt(2*acos(-1.0)))) * exp(-0.5*pow(((x-m)/s), 2));
}

double partialSigma(double m, double s, double x)
{
	return (((x-m)/(pow(s, 3)*sqrt(2*acos(-1.0)))) * exp(-0.5*pow(((x-m)/s), 2))) - ((1.0/(pow(s, 2)*sqrt(2*acos(-1.0))))*exp(-0.5*pow(((x-m)/s), 2)));
}

int main(void)
{
	ifstream inputFile ("NormalDistrInput.txt");
	int L = 0;
	inputFile >> L;
	double Y[L];
	double X[L];
	for (int l = 0; l < L; l++)
	{
		inputFile >> X[l] >> Y[l];
	}
	double mu = 14;
	double sigma = 1;
	double avgDiff = 10.0;
	while (avgDiff > 0.0001)
	{
		double muNew, sigmaNew;
		//cout << "In loop\n";
		for (int s = 0; s < 2; s++)
		{
			avgDiff = 0;
			double totalDiff = 0.0;
			for (int l2 = 0; l2 < L; l2++)
			{
				double difference = Y[l2] - normal(mu, sigma, X[l2]);
				avgDiff = avgDiff + pow(difference, 2);
				switch (s)
				{
					case 0:
						totalDiff = totalDiff + alpha * (difference) * partialMu(mu, sigma, X[l2]);
						break;
					case 1:
						totalDiff = totalDiff + alpha * (difference) * partialSigma(mu, sigma, X[l2]);
						break;
				}
			}
			if (s == 0)
				muNew = mu + totalDiff;
			else
				sigmaNew = sigma + totalDiff;
		}
		mu = muNew;
		sigma = sigmaNew;
		avgDiff = avgDiff/L;
		cout << avgDiff << "\n";
		cout << "MU: " << mu << ", SIGMA: " << sigma << "\n";
	}
	
	cout << avgDiff << "\n";
	cout << "MU: " << mu << ", SIGMA: " << sigma << "\n";
	
	return 0;
}
