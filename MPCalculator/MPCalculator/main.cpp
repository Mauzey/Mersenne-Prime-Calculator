// Alex Mounsey - SDFD211 @ City College Plymouth - March 2018
// Simple program that determines whether a number is a Mersenne Prime

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>

using namespace std;

// Known Mersenne Primes: http://mathworld.wolfram.com/MersennePrime.html
//#define P 3
//#define P 5
//#define P 7
#define P 13
//#define P 17
//#define P 19
//#define P 31
//#define P 61
//#define P 89
//#define P 107
//#define P 127
//#define P 521
//#define P 607

// Function declarations
void	squareVector(vector<int> srcVector, vector<int> &tgtVector);
void	carryVector(vector<int> &tgtVector);
void	subTwoVector(vector<int> &tgtVector);
void	modVector(vector<int> srcVector, vector<int> &tgtVector);
void	printVector(vector<int> tgtVector);

// Variables
vector<int> vectorA(P * 2, 0);
vector<int> vectorB(P * 4, 0);

double			elapsedTime;
LARGE_INTEGER	timerFrequency;
LARGE_INTEGER	timerStart, timerFinish;

void main(void) {
	// Set vectorA to a binary number to square
	vectorA.at(2) = 1;

	// Get how many ticks per second this system produces
	QueryPerformanceFrequency(&timerFrequency);

	// Start timer and begin calculations
	QueryPerformanceCounter(&timerStart);

	for (int k = 0; k < P - 2; k++) {
		cout << "P = " << P << " | Iteration = " << k + 1 << endl;

		// Square vectorA, and store result in vectorB
		cout << "Squaring     : ";
		squareVector(vectorA, vectorB);
		printVector(vectorB);

		// Perform carry function on vectorB
		cout << "Carrying     : ";
		carryVector(vectorB);
		printVector(vectorB);

		// Take 2 away from vectorB
		cout << "Subtracting 2: ";
		subTwoVector(vectorB);
		printVector(vectorB);

		// Perform mod function on vectorB. Store result in vectorA
		cout << "Modding      : ";
		modVector(vectorB, vectorA);
		printVector(vectorA);

		// Clear vectorB
		for (int i = 0; i < vectorB.size(); i++) vectorB.at(i) = 0;

		cout << endl;

	}

	// Log finish time, calculate total elapsed time and print result
	QueryPerformanceCounter(&timerFinish);
	elapsedTime = (timerFinish.QuadPart - timerStart.QuadPart) * 1000.0 / timerFrequency.QuadPart;

	cout << "Elapsed time: " << elapsedTime << "ms";

	// Pause until keypress
	_getch();
}

// Square a vector (srcVector) and store it in another (tgtVector)
void squareVector(vector<int> srcVector, vector<int> &tgtVector) {
	// Clear tgtVector
	for (int i = 0; i < tgtVector.size(); i++) tgtVector.at(i) = 0;

	// Perform square calculation
	for (int i = 0; i < srcVector.size() - 1; i++) {
		if (srcVector.at(i) == 1) {
			for (int j = 0; j < srcVector.size() - 1; j++) {
				if (srcVector.at(j) == 1) {
					tgtVector.at(i + j)++;
				}
			}
		}
	}
}

// Perform a binary carry on a specified vector
void carryVector(vector<int> &tgtVector) {
	for (int i = 0; i < tgtVector.size() - 1; i++) {
		if (tgtVector.at(i) > 16383) {	tgtVector.at(i) -= 16384;	tgtVector.at(i + 14)++; }
		if (tgtVector.at(i) > 8191) {	tgtVector.at(i) -= 8192;	tgtVector.at(i + 13)++; }
		if (tgtVector.at(i) > 4095) {	tgtVector.at(i) -= 4096;	tgtVector.at(i + 12)++; }
		if (tgtVector.at(i) > 2047) {	tgtVector.at(i) -= 2048;	tgtVector.at(i + 11)++; }
		if (tgtVector.at(i) > 1023) {	tgtVector.at(i) -= 1024;	tgtVector.at(i + 10)++; }
		if (tgtVector.at(i) > 511) {	tgtVector.at(i) -= 512;		tgtVector.at(i + 9)++; }
		if (tgtVector.at(i) > 255) {	tgtVector.at(i) -= 256;		tgtVector.at(i + 8)++; }
		if (tgtVector.at(i) > 127) {	tgtVector.at(i) -= 128;		tgtVector.at(i + 7)++; }
		if (tgtVector.at(i) > 63) {	tgtVector.at(i) -= 64;		tgtVector.at(i + 6)++; }
		if (tgtVector.at(i) > 31) {	tgtVector.at(i) -= 32;		tgtVector.at(i + 5)++; }
		if (tgtVector.at(i) > 15) {	tgtVector.at(i) -= 16;		tgtVector.at(i + 4)++; }
		if (tgtVector.at(i) > 7) {	tgtVector.at(i) -= 8;		tgtVector.at(i + 3)++; }
		if (tgtVector.at(i) > 3) {	tgtVector.at(i) -= 4;		tgtVector.at(i + 2)++; }
		if (tgtVector.at(i) > 1) {	tgtVector.at(i) -= 2;		tgtVector.at(i + 1)++; }
	}
}

// Subtract 2 (in binary) from a vector
void subTwoVector(vector<int> &tgtVector) {
	int index;

	// Check if the 2s unit == 1. If so, change to zero
	if (tgtVector.at(1) == 1) {
		tgtVector.at(1) = 0;
	// Otherwise perform calculation
	} else {
		for (int i = 2; i < tgtVector.size(); i++) {
			if (tgtVector.at(i) == 1) {
				index = i;
				tgtVector.at(index) = 0;
				i = tgtVector.size();
			}
		}

		// Change preceeding values from 0 to 1
		for (int i = index - 1; i > 0; i--) {
			tgtVector.at(i) = 1;
		}
	}
}

// Perform a binary mod on a vector
void modVector(vector<int> srcVector, vector<int> &tgtVector) {
	int count = 0;

	// Clear tgtVector
	for (int i = 0; i < tgtVector.size(); i++) tgtVector.at(i) = 0;

	// Copy P digits from srcVector to tgtVector
	do {
		for (int i = 0; i < P; i++) {
			tgtVector.at(i) += srcVector.at(i + count);

			if (tgtVector.at(i) > 1) {
				tgtVector.at(i) -= 2;
				tgtVector.at(i + 1)++;
			}
		}

		count += P;

	} while (count < srcVector.size());

	// Clear srcVector
	for (int i = 0; i < srcVector.size(); i++) srcVector.at(i) = 0;
}

// Print a vector to the console
void printVector(vector<int> tgtVector) {
	// Prints vector in reverse so it's in correct binary format
	for (int i = tgtVector.size() - 1; i >= 0; i--) {
		cout << tgtVector.at(i) << " ";
	}

	cout << endl;
}
