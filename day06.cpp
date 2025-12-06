#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>


using namespace std;

//  11157319961271 too low



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
  for (auto _=0; _<5;++_) {
    getline(myfile,line);
    string entry="";
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
      }
      else {continue;}
    }
    if (_==0) {nums.push_back({ entry });}
    else {nums[k].push_back(entry);}
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

  long long part2=0;
  string res;
  long long temp;
  for (vector<string> n:nums) {
    temp=(n[4] == "+")? 0:1;

    do {
      res="";
      for (int i=0; i<4; ++i) {
        if (n[i].length()) {
          res+=*(n[i].end()-1);
          n[i].erase(n[i].end()-1);
        }
      }
      if (res.length()) {
        if (n[4] == "+") {temp+=stoi(res);}
        else {temp*=stoi(res);}
      }
    } while (res.length());

    part2 +=temp;
  }

  cout << part1 << "\n";
  cout << part2 << "\n";

  

  
  
  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";
	/////Execution time: 1.56448 ms
	return 0;
}