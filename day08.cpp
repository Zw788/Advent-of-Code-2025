#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <map>
#include <cmath>


using namespace std;

float dist(const vector<float>& x,const vector<float>& y ) {
	return ( pow(x[0]-y[0],2) + pow(x[1]-y[1],2) + pow(x[2]-y[2],2) );
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

  // number of boxes =1000

  string line;
	vector<float> a={};
  vector<vector<float>> box={1000,a};
  for (unsigned int i=0; i < 1000; ++i) {
		getline(myfile,line);
    for (auto _: {0,1}) {
			box[i].push_back( stof(line.substr(0,line.find(',')))/10000  );
			line=line.substr(line.find(',')+1);
		}
		box[i].push_back( stof(line.substr(0,line.find(',')))/10000 );
  }

	float x;
	vector<vector<int>> dist_order={};
	for (int i=0; i < 1000-1;++i) {
		for (int j=i+1; j < 1000; ++j) {
			x=dist(box[i],box[j]);
			
	}



  
  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";
	/////Execution time: 5.32446 ms
	return 0;
}