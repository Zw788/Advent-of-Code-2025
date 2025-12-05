#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include <map>


using namespace std;

// can optimize further by using another map() to just consider the boundary rolls

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

  map<string,bool> grid={}; // input dimension is a square, index range from 63 to (63+137=200)
  vector<string> rolls={}; // list of rolls of paper key

  string line;
	char i=63;
	while (getline(myfile,line)) { 
    for (int j=0; j < int(line.length()); ++j) {
			char b = j+63;
			if (line[j] == '@') {rolls.push_back(string(1,i)+b);}
			grid[string(1,i)+b]=bool(line[j] == '@');
			}
		i+=1;
	}


	// int part1=0;
	// for (string i:rolls) {
	// 	int res = 0;
	// 	for (vector<char> j : vector<vector<char>>{{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}}) {
	// 		res += grid[string(1,char(i[0]+j[0]))+ char(i[1]+j[1])];
	// 	}
	// 	part1+= bool(res < 4);
	// }
	// cout << part1 << "\n";

	int part2=0;
	vector<int> cut_roll={};
	do {
		cut_roll={};
		for (int i=0; i < int(rolls.size()); ++i) {
			int res = 0;
			for (vector<char> j : vector<vector<char>>{{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}}) {
				res += grid[string(1,char(rolls[i][0]+j[0]))+ char(rolls[i][1]+j[1])];
			}
			if (res < 4) {
				cut_roll.push_back(i);
			}
		}
		part2 += int(cut_roll.size());
		for (auto i=cut_roll.rbegin(); i!=cut_roll.rend(); ++i) {
			grid[rolls[*i]]=0;
			rolls.erase(rolls.begin()+*i);
		}

	} while (cut_roll.size());

	cout << part2 << "\n";


	

  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";

	return 0;
}