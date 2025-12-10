#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <map>
#include <set>


using namespace std;

void merge(vector<int>& arr, vector<vector<long long>>& vec, int lo, int mid, int hi, int n) {

  vector<int> arr1 = vector<int>(arr.begin()+lo, arr.begin()+mid+1);
  vector<int> arr2 = vector<int>(arr.begin()+mid+1, arr.begin()+hi+1);

  
	vector<vector<long long>> vec1 = vector<vector<long long>>(vec.begin()+lo, vec.begin()+mid+1);
	vector<vector<long long>> vec2 = vector<vector<long long>>(vec.begin()+mid+1, vec.begin()+hi+1);

	unsigned int i = 0, j = 0, k = lo;
	while (i < vec1.size() && j < vec2.size()) {
		if (vec1[i][n] <= vec2[j][n]) {
			vec[k] = vec1[i];
      arr[k] = arr1[i];
      k+=1,i+=1;
		} else {
			vec[k] = vec2[j];
      arr[k] = arr2[j];
      k+=1,j+=1;
		}
	}
	while (i < vec1.size()) {
		vec[k] = vec1[i];
    arr[k] = arr1[i];
    k+=1,i+=1;
	}
	while (j < vec2.size()) {
		vec[k] = vec2[j];
    arr[k] = arr2[j];
    k+=1,j+=1;
	}
}

void mergeSort (vector<int>& arr,vector<vector<long long>>& vec, int lo, int hi, int n=0) // mergeSort(vec,0,vec.size()-1);
{
	if (lo >= hi) return;
	int mid = lo + (hi - lo) / 2;
	mergeSort(arr,vec, lo, mid,n);
	mergeSort(arr,vec, mid + 1, hi,n);
	merge(arr,vec, lo, mid, hi, n);
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
  
  // number of lines = 496
  int N=496;

  string line;
  vector<long long> a={};
  vector<vector<long long>> tiles(N,a);
  for (auto i=0; i<N; ++i) {
    getline(myfile,line);
    auto p=line.find(',');
    tiles[i].push_back(stoll(line.substr(0,p)) );
    tiles[i].push_back(stoll(line.substr(p+1)) );
  }

  long long part1=0;
  for (int i=0; i < N-1;++i) {
		for (int j=i+1; j < N; ++j) {
      long long x = (abs(tiles[i][0]-tiles[j][0])+1)*(abs(tiles[i][1]-tiles[j][1])+1);
			if ( x > part1  ) {part1 = x;}
		}
	}
  
  cout << part1 << "\n";

  vector<int> range={};
  for (int i=0; i < N; ++i) {
    range.push_back(i);
  }
  cout << range.size() << ", " << tiles.size()  << "\n";

  mergeSort(range,tiles,0,tiles.size()-1);
  long long x=range.back();
  map<long long, set<int>> xrange={};
  for (auto i = N-1; i < 0; --i) {
    
  }

  
  


  // condition for part2 
  // no red tile inside rectangle (range check)
  // inside of the rectangle 

  long long part2=0;





  
  myfile.close();
	/////////////////////////////////////////////////////////
	auto end = chrono::steady_clock::now();
	auto diff = end - start;
  cout << "\n";
	cout << "Execution time: " << chrono::duration<double, milli>(diff).count() << " ms" << "\n";
	
	return 0;
}