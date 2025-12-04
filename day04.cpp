#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include <map>


using namespace std;

// 1766 too high


// bool freepaper( const string& s, map<string,bool> g) {
// 	int res = 0;
// 	for (auto i : vector<vector<char>>{{-1,-1},{-1,0},{-1,1},{0,-1},{1,-1},{1,-1},{1,0},{1,1}}) {
// 		res += bool(g[string(1,char(s[0]+i[0]))+ char(s[1]+i[1])]);
// 	}
// 	return bool(res < 4);
// }


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

	int part1=0;
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

	///// Padding
	int N=line.length();
	for (int i=0;i<N+2;++i) {
		char x =62;
		grid[string(1,x)+char(x+i)]=0;
		grid[string(1,char(x+N+1))+char(x+i)]=0;
		grid[string(1,char(x+i))+x]=0;
		grid[string(1,char(x+i))+char(x+N+1)]=0;
	}

	for (auto i:rolls) {
		int res = 0;
		for (auto j : vector<vector<char>>{{-1,-1},{-1,0},{-1,1},{0,-1},{1,-1},{1,-1},{1,0},{1,1}}) {
			res += bool(grid[string(1,char(i[0]+j[0]))+ char(i[1]+j[1])]);
		}
		part1+= bool(res < 4);
	}

	cout << part1;

  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";

	return 0;
}