

#include "pch.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <mutex>
#include <random>
using namespace std;

class Gisto {
	int *Digits;
	int	**resultGisto;
	int *index;
	string P;
	ifstream fin;
	int numberDistr;
	int numberElemGist;
	int prom;

public:
	Gisto(string path, int numberOfDigits,int numberOfDistributions, int numberElemetsGistogram) {
		
		numberElemGist = numberElemetsGistogram;
		numberDistr = numberOfDistributions;
		Digits = new int[numberOfDigits];
		resultGisto = new int* [numberOfDistributions];
		index = new int[numberDistr+1];
		prom = numberOfDigits / numberOfDistributions;
		for (int i = 0; i < numberOfDistributions; i++) {
			resultGisto[i] = new int[numberElemetsGistogram];
			}
		for (int i = 0; i < numberOfDistributions; i++) {
			for (int j = 0; j < numberElemetsGistogram; j++) {
				resultGisto[i][j] = 0;
			}
		}

		for (int i = 0; i < numberDistr+1; i++) {
			index[i] = prom * i ;
		}
		



		fin.open(path);

		for (int i = 0; i < numberOfDigits; i++) {
			fin >> Digits[i];
		}
	}


	~Gisto() {
		delete[] Digits;
		delete[] index;
		for (int i = 0; i < numberDistr; i++) {
			delete[] resultGisto[i];
		}
		delete[] resultGisto;
	}

	void counting(int numberArray) {
		
			for (int j = index[numberArray]; j < index[numberArray+1]; j++) {
				resultGisto[numberArray][Digits[j] / 50]++;
			}
		
	}

	void ShowResult() {
		for (int i = 1; i < numberDistr; i++) {
			for (int j = 0; j < numberElemGist; j++)
				resultGisto[0][j] += resultGisto[i][j];
		}
		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < numberElemGist; j++) {
				cout << resultGisto[i][j] << endl;
			}
		}
	}
	
};

class GistoVolatile {
	int *Digits;
	volatile int *resultGisto;
	int *index;
	string P;
	ifstream fin;
	int numberDistr;
	int numberElemGist;
	int prom;

public:
	GistoVolatile(string path, int numberOfDigits, int numberOfDistributions, int numberElemetsGistogram) {

		numberElemGist = numberElemetsGistogram;
		numberDistr = numberOfDistributions;
		Digits = new int[numberOfDigits];
		resultGisto = new int [numberElemetsGistogram];
		index = new int[numberDistr + 1];
		prom = numberOfDigits / numberOfDistributions;
		
		
		for (int j = 0; j < numberElemetsGistogram; j++) {
			resultGisto[j] = 0;
		}

		for (int i = 0; i < numberDistr + 1; i++) {
			index[i] = prom * i;
		}



		fin.open(path);

		for (int i = 0; i < numberOfDigits; i++) {
			fin >> Digits[i];
		}
	}


	~GistoVolatile() {
		delete[] Digits;
		delete[] index;
		
		delete[] resultGisto;
	}

	void counting(int numberArray) {

		for (int j = index[numberArray]; j < index[numberArray + 1]; j++) {
			resultGisto[Digits[j] / 50]++;
		}

	}

	void ShowResult() {
		
		for (int j = 0; j < numberElemGist; j++) {
			cout << resultGisto[j] << endl;
		}
	}


};

class GistoMutex {
	int *Digits;
	int	*resultGisto;
	int *index;
	string P;
	ifstream fin;
	int numberDistr;
	int numberElemGist;
	int prom;
	mutex MutexGisto;

public:
	GistoMutex(string path, int numberOfDigits, int numberOfDistributions, int numberElemetsGistogram) {

		numberElemGist = numberElemetsGistogram;
		numberDistr = numberOfDistributions;
		Digits = new int[numberOfDigits];
		resultGisto = new int[numberElemGist];
		index = new int[numberDistr + 1];
		prom = numberOfDigits / numberOfDistributions;
		
		for (int i = 0; i < numberElemGist; i++) {
			resultGisto[i] = 0;
		}

		for (int i = 0; i < numberDistr + 1; i++) {
			index[i] = prom * i;
		}




		fin.open(path);

		for (int i = 0; i < numberOfDigits; i++) {
			fin >> Digits[i];
		}
	}


	~GistoMutex() {
		delete[] Digits;
		delete[] index;
		
		delete[] resultGisto;
	}

	void counting(int numberArray) {

		MutexGisto.lock();
		for (int j = index[numberArray]; j < index[numberArray + 1]; j++) {
			resultGisto[Digits[j] / 50]++;
		}
		MutexGisto.unlock();

	}

	void ShowResult() {
		
		 
			for (int j = 0; j < numberElemGist; j++) {
				cout << resultGisto[j] << endl;
			}
		
	}

};

class GistoNormalDistribution {
	int *Digits;
	int	**resultGisto;
	int *index;
	string P;
	ifstream fin;
	ofstream fon;
	int numberDistr;
	int numberElemGist;
	int prom;

public:
	GistoNormalDistribution(string path, int numberOfDigits, int numberOfDistributions, int numberElemetsGistogram) {

		numberElemGist = numberElemetsGistogram;
		numberDistr = numberOfDistributions;
		Digits = new int[numberOfDigits];
		resultGisto = new int*[numberOfDistributions];
		index = new int[numberDistr + 1];
		prom = numberOfDigits / numberOfDistributions;
		for (int i = 0; i < numberOfDistributions; i++) {
			resultGisto[i] = new int[numberElemetsGistogram];
		}
		for (int i = 0; i < numberOfDistributions; i++) {
			for (int j = 0; j < numberElemetsGistogram; j++) {
				resultGisto[i][j] = 0;
			}
		}

		for (int i = 0; i < numberDistr + 1; i++) {
			index[i] = prom * i;
		}
		for (int i = 0; i < numberDistr + 1; i++) {
			Digits[i] = 0;
		}


		std::default_random_engine generator;
		std::binomial_distribution<int> distribution(350, 0.5);

		
/*
		for (int i = 0; i < numberOfDigits; ++i) {
			int number = distribution(generator);
			Digits[i] = number;

		}
		
		fon.open(path);

		for (int i = 0; i < numberOfDigits; i++) {
			
			fon << Digits[i] << endl;
		}
*/		fin.open(path);
		for (int i = 0; i < numberOfDigits; i++) {

			fin >> Digits[i];
		}
	}


	~GistoNormalDistribution() {
		delete[] Digits;
		delete[] index;
		for (int i = 0; i < numberDistr; i++) {
			delete[] resultGisto[i];
		}
		delete[] resultGisto;
	}

	void counting(int numberArray) {

		for (int j = index[numberArray]; j < index[numberArray + 1]; j++) {
			resultGisto[numberArray][Digits[j] / 50]++;
		}

	}

	void ShowResult() {
		for (int i = 1; i < numberDistr; i++) {
			for (int j = 0; j < numberElemGist; j++)
				resultGisto[0][j] += resultGisto[i][j];
		}
		for (int i = 0; i < 1; i++) {
			for (int j = 0; j < numberElemGist; j++) {
				cout << resultGisto[i][j] << endl;
			}
		}
	}

};




int main()
{
/*	string b = "OneMillion.txt";
	Gisto g(b,1000000,2,7);
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	thread tr1([&g]() { g.counting(0); });
	thread tr2([&g]() { g.counting(1); });
	//thread tr3([&g]() { g.counting(2); });
	//thread tr4([&g]() { g.counting(3); });
	tr1.join();
	tr2.join();
	//tr3.join();
	//tr4.join();
	g.ShowResult();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::microseconds>(t2 - t1).count(); 
	*/
	/*string b = "OneMillion.txt";
	GistoVolatile g(b, 1000000, 2, 7);
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	thread tr1([&g]() { g.counting(0); });
	thread tr2([&g]() { g.counting(1); });
	//thread tr3([&g]() { g.counting(2); });
	//thread tr4([&g]() { g.counting(3); });
	tr1.join();
	tr2.join();
	//tr3.join();
	//tr4.join();
	g.ShowResult();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::microseconds>(t2 - t1).count(); 
	*/

	/*string b = "OneMillion.txt";
	GistoMutex g(b, 1000000, 2, 7);
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	thread tr1([&g]() { g.counting(0); });
	thread tr2([&g]() { g.counting(1); });
	//thread tr3([&g]() { g.counting(2); });
	//thread tr4([&g]() { g.counting(3); });
	tr1.join();
	tr2.join();
	//tr3.join();
	//tr4.join();
	g.ShowResult();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::microseconds>(t2 - t1).count(); 
	*/

	string b = "OneMillionNormal.txt";
	GistoNormalDistribution g(b, 1000000, 2, 7);
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
	thread tr1([&g]() { g.counting(0); });
	thread tr2([&g]() { g.counting(1); });
	//thread tr3([&g]() { g.counting(2); });
	//thread tr4([&g]() { g.counting(3); });
	tr1.join();
	tr2.join();
	//tr3.join();
	//tr4.join();
	g.ShowResult();
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
}



