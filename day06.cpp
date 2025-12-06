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

  string line;
  vector<vector<string>> nums={};
  vector<char> prod={};
  string entry="";
  getline(myfile,line);
  int k=0;
  for (int i=0; i<int(line.length()); i++) {
    if (line[i]!=' ') {
      entry+=string(1,line[i]);
      continue;
    }
    else {
      k+=1;
      if (int(nums.size()) < k) {nums.push_back({entry});}
      else {nums[k-1].push_back(entry);}
      entry="";
      while (i<(int(line.length()))){
        if (line[i+1]=' ') {i+=1;}
        else {break;}
      }
    }
  }

  for (auto i:nums) {cout << i[0] << "\n";}
  
  
  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";
	/////Execution time: 1.56448 ms
	return 0;
}