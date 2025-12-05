#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include <map>


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

  map<string,bool> grid={}; // input dimension is a square, index range from 63 to (63+137=200)
  string line;
	char i=63;

	while (getline(myfile,line)) { 
    for (int j=0; j < int(line.length()); ++j) {
			char b = j+63;
			if (line[j] == '@') {
				grid[string(1,i)+b]=1;
			}
		}
		i+=1;
	}

	int part1=0;
	int part2=0;
	vector<string> cut_roll;
	string key;
	map<string,bool> boundary;
	map<string,bool> rolls=grid;

	do {
		cut_roll={};
		boundary={};
		
		for (const auto& [x,y] : rolls) {
			int neighbor = 0;
			vector<string> temp={};

			for (vector<char> j : vector<vector<char>>{{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}}) {
				key=string(1,char(x[0]+j[0]))+ char(x[1]+j[1]);
				if (grid[key]){
					neighbor += 1;
					temp.push_back(key);
				}
			}

			if (neighbor < 4) {
				cut_roll.push_back(x);
				for (string k:temp) {boundary[k]=1;}
			}
		}

		part2 += int(cut_roll.size());
		if (part1 ==0) {part1=int(cut_roll.size());}

		for (string i:cut_roll) {
			grid.erase(i);
			boundary.erase(i);
		}
		
		rolls=boundary;
	} while ( cut_roll.size() );

	cout << part1 << "\n";
	cout << part2 << "\n";


  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";
	/////Execution time: 281.713 ms
	return 0;
}