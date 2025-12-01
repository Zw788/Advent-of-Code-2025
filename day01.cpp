#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
int main()
{
	auto start = chrono::steady_clock::now();
	string line;
	ifstream myfile;
	myfile.open("../aoc2025/inputs/aoc2025_input.txt");

	int current = 50;
	int part1 = 0;
	int part2 = 0;
	while (getline(myfile, line)) { 
		if ((line[0] == 'R') ^ (current >= 0)) {current=(current + (2*(current < 0)-1)*100)%100;}
		int clicks = current + (2 * (line[0] == 'R') - 1) * stoi(line.substr(1)) ;
		current = clicks %100 ;
		part1 += (current == 0);
		part2 += abs(clicks / 100);
	}

	cout << part1 << endl;
	cout << part2 << endl;


	auto end = chrono::steady_clock::now();
	cout << duration_cast<std::chrono::milliseconds>(end - start) << endl;

	return 0;
}