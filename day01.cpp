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

	int current = 50;
	int part1 = 0;
	int part2 = 0;
	string line;
	while (getline(myfile, line)) { 
		if ((line[0] == 'R') ^ (current >= 0)) {current=(current + (2*(current < 0)-1)*100)%100;}
		current += stoi(line.substr(1)) ;
		part2 += abs(current / 100);
		current = current%100 ;
		part1 += (current == 0);
	}

	cout << part1 << endl;
	cout << part2 << endl;


	myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << endl;

	return 0;
}

