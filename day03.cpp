#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <set>
#include <cmath>


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

	long long res=0;
	vector<int> jolt;

	int n= 12-1; /// part1 n=2-1, part2 n=12-1

	string line;
	while (getline(myfile,line)){
		jolt={};
		for (auto i=line.end()-(n+1); i!=line.end(); ++i) {
			jolt.push_back(*i - '0');
		}

		for (auto i= line.rbegin()+(n+1); i!=line.rend(); ++i) {
			if ((*i - '0') >= jolt[0]) {
				int t=0;
				while (jolt[t] >= jolt[t+1] && t <= n) {++t;}		
				jolt.erase(jolt.begin()+t);
				jolt.insert(jolt.begin(),(*i - '0'));
			} 
		}
		for (auto i=n;i>=0;--i) {
			res+=jolt[n-i]*pow(10,i);
		}

	}

	cout << res << "\n";

	myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << endl;

	return 0;
}