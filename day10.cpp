#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <map>
#include <sstream>


using namespace std;

//[.#..] (0,2) (0,1,3) (0) (2,3) (0,3) {34,12,30,33}


int toggle(const int& t, const vector<int>& b) {
  int presses=1;
  vector<int> p_combo = b;
  vector<int> n_combo;
  while (true) {
    for (auto i: p_combo) {
      if (i==t) {return presses;}
      for (auto j:b) {n_combo.push_back( j^i );}
    }
    p_combo=n_combo;
    n_combo={};
    presses+=1;
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
  
  // number of lines
  int N = 189;
  string line;

  vector<int> target(N,0);
  vector<int> a={};
  vector<vector<int>> buttons(N,a);
  vector<int> digit={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536};
  size_t p=0;
  int x=0;
  for (auto k=0; k< N; ++k){
    getline(myfile,line);
    p=line.find(']');
    string s=line.substr(1,p-1);
    for (auto i=0; i < s.length(); ++i) {
      target[k]+=digit[i]*(s[i] == '#');
    }

    line=line.substr(p+1);
    while ((p=line.find(')')) != string::npos) {
      stringstream ss(line.substr(2,p-1));
      x=0;
      while (getline(ss,s,',')) { x+= digit[stoi(s)]; }
      buttons[k].push_back(x);

			line=line.substr(p+1);
		}
  }
  // for (auto i=0; i< N; ++i) {
  //   cout << target[i] << ": ";
  //   for (auto j:buttons[i]) {cout << j << ", ";}
  //   cout << "\n";
  // }

  int part1=0;
  for (auto t=0; t < target.size(); ++t) {
    part1+=toggle(target[t],buttons[t]);
  }
  cout << part1 <<"\n";

  
  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";
	
	return 0;
}