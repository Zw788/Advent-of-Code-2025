#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <map>
#include <cmath>


using namespace std;


//3528 too low
// 28288 too high
// 7128 too low

double dist(const vector<double>& x,const vector<double>& y ) {
	return ( pow(x[0]-y[0],2) + pow(x[1]-y[1],2) + pow(x[2]-y[2],2) );
}

// merge sort implementation
void merge(vector<vector<double>>& vec, int lo, int mid, int hi) {
	vector<vector<double>> vec1 = vector<vector<double>>(vec.begin()+lo, vec.begin()+mid+1);
	vector<vector<double>> vec2 = vector<vector<double>>(vec.begin()+mid+1, vec.begin()+hi+1);

	unsigned int i = 0, j = 0, k = lo;
	while (i < vec1.size() && j < vec2.size()) {
		if (vec1[i][0] <= vec2[j][0]) {
			vec[k++] = vec1[i++];
		} else {
			vec[k++] = vec2[j++];
		}
	}
	while (i < vec1.size()) {
		vec[k++] = vec1[i++];
	}
	while (j < vec2.size()) {
		vec[k++] = vec2[j++];
	}
}

void mergeSort (vector<vector<double>>& vec, int lo, int hi)
{
	if (lo >= hi) return;
	int mid = lo + (hi - lo) / 2;
	mergeSort(vec, lo, mid);
	mergeSort(vec, mid + 1, hi);
	merge(vec, lo, mid, hi);
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
	int N=1000;

  string line;
	vector<double> a={};
  vector<vector<double>> box(N,a);
  for (unsigned int i=0; i < N; ++i) {
		getline(myfile,line);
    for (auto _: {0,1}) {
			box[i].push_back( stof(line.substr(0,line.find(',')))/1000  );
			line=line.substr(line.find(',')+1);
		}
		box[i].push_back( stof(line.substr(0,line.find(',')))/1000 );
  }

	vector<vector<double>> dist_order={};
	for (int i=0; i < N-1;++i) {
		for (int j=i+1; j < N; ++j) {
			dist_order.push_back( { dist(box[i],box[j]) , i, j} );
		}
	}
	mergeSort(dist_order,0,dist_order.size()-1);
	// for (auto i: dist_order) {cout << i[0] << " " << i[1] << " "<< i[2] << "\n";}

	// {box# : circuit# }

	// Find/Parent {box# : root box# }
	// Union {root box#:set( ...elements )}

	map<int,int> circuits={};
	vector<int> Rootof(N+2,N+1);


	for (int i=0; i< N; ++i) {
		int a =dist_order[i][1];
		int b =dist_order[i][2];

		// cout << "a: " << a << " root of a: " << Rootof[a] << " b: " << b << " root of b: " << Rootof[b] << "\n";

		if (Rootof[a]==N+1 && Rootof[b]==N+1 ) { 
			int c=min(a,b);
			Rootof[a]=c, Rootof[b]=c;
			circuits[c] = 2;
		 }
		else {
			while(Rootof[a] != Rootof[Rootof[a]]  ) {Rootof[a] = Rootof[Rootof[a]];}
			while(Rootof[b] != Rootof[Rootof[b]]  ) {Rootof[b] = Rootof[Rootof[b]];}
			if (Rootof[a]== Rootof[b]) {continue;}
			int c=min(Rootof[a],Rootof[b]);
			int d=max(Rootof[a],Rootof[b]);
			circuits[c]+=max(1,circuits[d]);
			Rootof[a]=c, Rootof[b]=c;
			circuits.erase(d);
		}
	}

	vector<int> part1={};
	int check=0;
	for (auto [x,y]:circuits) {
		check+= int(y);
		// cout << y << "\n";
		part1.push_back(y);
		if (part1.size()<4){continue;}

		int m=0;
		for (auto i=1; i < 4; ++i){m=(part1[m]<=part1[i])? m: i;}
		part1.erase(part1.begin()+m);

	}

	// cout << "============" << "\n";
	// cout << check << "\n";

	for (auto i : part1) {cout << i << "\n";}

	cout << part1[0]*part1[1]*part1[2] << "\n";

  
  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";
	/////Execution time: 5.32446 ms
	return 0;
}