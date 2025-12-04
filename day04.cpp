#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>


using namespace std;


int main()
{
	auto start = chrono::steady_clock::now();
	/////////////////////////////////////////////////////////
	ifstream myfile;
	myfile.open("../aoc2025_input.txt");
	if (!myfile.is_open()) {
		cerr << "Error opening file" << endl;
		return 1;
	}

	

	myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << endl;

	return 0;
}