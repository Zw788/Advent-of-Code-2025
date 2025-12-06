#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>


using namespace std;

//  2413585 too low


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

  string line;
  vector<vector<string>> nums={};
  string entry="";
  for (auto _=0; _<5;++_) {
    getline(myfile,line);
    int k=0;
    for (int i=0; i<int(line.length()); ++i) {
      if (line[i]!=' ') {
        entry+= line[i];
        continue;
      }
      else if (entry.size()) {
        k+=1;
        if (int(nums.size()) < k) {nums.push_back(vector<string> {entry});}
        else {nums[k-1].push_back(entry);}
        entry="";
        while (i<(int(line.length()))){
          if (line[i+1]==' ') {i+=1;}
          else {break;}
        }
      }
      else {continue;}
    }
    if (_==0) {nums.push_back({ entry });}
    else {nums[k].push_back(entry);}
    entry="";
  }

  long long part1=0;
  for (vector<string> n:nums) {
    if (n[4] == "+") {
      long long res=0;
      for (auto i=0; i<4;++i) {res+=stoi(n[i]);}
      part1+= res;
    }
    else {
      long long res=1;
      for (auto i=0; i<4;++i) {res*=stoi(n[i]);}
      part1+= res;
    }
  }

  cout << part1;

  

  
  
  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";
	/////Execution time: 1.56448 ms
	return 0;
}