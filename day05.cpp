#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <map>



using namespace std;

//548 too low


int bin_search(const long long& x, const vector<vector<long long>>& sortlist) {
	if (x > (*(sortlist.end()-1))[0] ) { return sortlist.size();	}
	else {
		int res = 0;
		int inval = sortlist.size() - 1;
		while (inval) {
			int rem = inval % 2;
			inval >>= 1;
			if (x > sortlist[res + inval][0]) { res += inval + rem; }
		}
		return res;
	}
}

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

  // 178 ranges, 1000 ids

  vector<vector<long long>> ranges={};
  vector<long long> v;
  string line;
  getline(myfile,line);
  v.push_back( stoll( line.substr(0,line.find('-') ) ) );
  v.push_back( stoll( line.substr(line.find('-') +1) ) );
  ranges.push_back(v);

  while (getline(myfile,line) && line.length()) {
    v={};
    v.push_back( stoll( line.substr(0,line.find('-') ) ) );
    v.push_back( stoll( line.substr(line.find('-') +1) ) );
    ranges.insert(ranges.begin()+ bin_search(v[0],ranges) ,v );
  }

  vector<int> cull(int(ranges.size()),0);
  for (int i=0; i<int(ranges.size())-1;i++) {
    if (cull[i]) {continue;}
    int j=1;
    while ( ranges[i][1] >= ranges[i+j][0]) {
      ranges[i][1] = (ranges[i][1] >= ranges[i+j][1])? ranges[i][1] : ranges[i+j][1]; 
      cull[i+j] =1;
      if (i+j <int(ranges.size())-1) {j+=1;}
      else {break;}
    }
  }

  for (int i =ranges.size(); i !=0; --i) {
    if (cull[i]) {ranges.erase(ranges.begin()+i);}
  }

  int part1=0;
  while (getline(myfile,line)) {
    long long x=stoll(line);
    int i = bin_search(x,ranges);
    cout << "x: " << x << "\n";
    cout << ranges[max(i-1,0)][0] << ": " << ranges[max(i-1,0)][1] << "\n";
    if (i) {part1 += bool( x >= ranges[i][0] && x <= ranges[max(i-1,0)][1]  );}
    cout << part1 << "\n";
  }


  


  
  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";
	/////Execution time: 281.713 ms
	return 0;
}