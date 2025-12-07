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

  int l=0;
  string line;
  map<int,long long> beams;

  getline(myfile,line);
  l+=1;
  int mid=line.find('S');
  beams[mid]+=1;

  int part1=0;
  while (getline(myfile,line)) {
    if (!(l%2)) {
      for (int i=mid-l; i <= mid +l; ++i) {
        if (line[i] == '^') {
          part1+=bool(beams[i]);
          beams[i-1]+=beams[i];
          beams[i+1]+=beams[i];
          beams.erase(i);
        }
      }
    }

    l+=1;
  }
  long long part2=0;
  for (auto [x,y]:beams) {
    part2+=y;
  }

  cout << part1 << "\n";
  cout << part2 << "\n"; 

  
  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";
	/////Execution time: 5.32446 ms
	return 0;
}