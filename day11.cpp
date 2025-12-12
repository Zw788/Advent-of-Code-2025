#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <map>
#include <set>


using namespace std;

//for (auto i=0; i < N ; ++i) {// cout << V[i] << "\n";}
// 35736 too high
// 3127 too high

long long findpath(const string& s="", const string& e="", map<string,vector<string>> r={}, set<string> visited={}) {
  if (s == e) {return 1;}
  if (visited.find(s) != visited.end()) {return 0;}
  long long res=0;
  visited.insert(s);
  for(auto i:r[s]) { res+=findpath(i,e,r,visited);}

  return res;
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
  int N = 574;
  string line;
  map<string,vector<string>> server={};
  vector<string> next_q={};
  map<string,set<string>> reference={};
  for (auto i=0; i < N ; ++i) {
    getline(myfile,line);
    string x=line.substr(0,3);
    uint k=1;
    while ( (k+=4) <= line.length() ) {
      server[x].push_back(line.substr(k,3));
      reference[line.substr(k,3)].insert(x);
    }
    // for (auto [x,y]:server) { cout << x << ", " << y[0] << "\n";}
  }

  map<string,long long> paths={};
  string starts="you";
  string ends="out";
  vector<string> que=server[starts];
  
  while (que.size()) {
    for (auto i:que) {
      paths[i]+=1;
      if (i != ends /*&& hist.find(i) == hist.end()*/ ) {next_q.insert(next_q.end(),server[i].begin(),server[i].end());}
    }
    // for (auto j:next_q) { cout << j << ", ";}
    // cout << "\n";
    que=next_q;
    next_q={};
  }
  cout << paths[ends] << "\n";
  // for (auto [x,y] :server) { cout << x << ": " << y[0]  << "\n";}


  starts="svr";
  ends="fft";
  // paths={};
  // next_q={};
  set<string> hist={};
  // que=server[starts];
  // while (que.size()) {
  //   for (auto i:que) {
  //     paths[i]+=1;
  //     if (i != ends ) {next_q.insert(next_q.end(),server[i].begin(),server[i].end());}
  //   }
  //   // for (auto j:next_q) { cout << j << ", ";}
  //   // cout << "\n";
  //   que=next_q;
  //   next_q={};
  // }
  // cout << paths[ends] << "\n";

  
  cout << 0 << "\n";
  
  
  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";
	
	return 0;
}