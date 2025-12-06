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

  string l;
  vector<string> lines={};
  for (auto _=0; _<5;++_) {
    getline(myfile,l);
    lines.push_back(l);
  }

  int N=l.length();
  vector<vector<string>> nums(N,{"","","","",""});
  int k=0;
  string entry;

  for (int i=0; i < N; ++i) {
    entry="";
    for (int j=0; j<5; ++j){entry+=lines[j][i];}

    if (entry=="     ") {k+=1;continue;}
    else {
      for (int j=0; j<4; ++j) {nums[k][j]+=entry[j];}
      if (entry[4] != ' ') {nums[k][4]+=entry[4];}
    }
  }

  nums={nums.begin(),nums.begin()+k+1};

  long long part1=0;
  long long res;

  for (vector<string> n:nums) {
    if (n[4] == "+") {
      res=0;
      for (auto i=0; i<4;++i) {res+=stoi(n[i]);}
      part1+= res;
    }
    else {
      res=1;
      for (auto i=0; i<4;++i) {res*=stoi(n[i]);}
      part1+= res;
    }
  }

  long long part2=0;
  string temp;

  for (vector<string> n:nums) {
    res=(n[4] == "+")? 0:1;

    for (int i=0; i < int(n[0].length()); ++i) {
      temp="";
      for (auto j=0; j<4;++j) { temp+=n[j][i]; }
      if (n[4] == "+") {res+=stoi(temp);}
      else {res*=stoi(temp);}
    }

    part2 +=res;
  }

  cout << part1 << "\n";
  cout << part2 << "\n";
  
  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";
	/////Execution time: 4.28 ms
	return 0;
}