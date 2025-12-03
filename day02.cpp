#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <set>

using namespace std;

long long repeat(const int& x, const int& n) {
	string res = to_string(x);
	for (int i = 1; i < n; ++i) {
		res += to_string(x);
	}
	return stoll(res);
}

set<long long> errcheck(const string& l, const vector<int>& v, string f ) {
	if (l.length() < 2) { return {}; }

	set<long long> res = {};
	long long lnum = stoll(l);
	long long fnum = stoll(f);

	for (auto n : v) {
		int i = stoi(l.substr(0, n));
		int r = repeat(i, l.length() / n);

		while (repeated <= lnum && repeated >= fnum) {
			res.insert(repeated);
			--i;
			r = repeat(i, l.length() / n);
		}
	}

	return res;
}

int main()
{
	auto start = chrono::steady_clock::now();

	ifstream myfile;
	myfile.open("../aoc2025/inputs/aoc2025_input.txt");

	vector<vector<int>> factors = { {1},{1},{2},{1},{2,3},{1},{4},{3},{2,5},{1},{4,6},{1} };
	string first;
	string last;
	bool _ = 1;
	set<long long> part1 = {};
	set<long long> part2 = {};


	char ch;
	while (myfile.get(ch)) {
		if (ch == ',') {
			//cout << "First: " << first << " Last: " << last << endl;
			for (int d = last.length(); d >= first.length(); --d) {
				string l = (d == last.length())? last : to_string(int(pow(10,d)-1)) ;
				string f = (first.length() == d ) ? first : to_string(int(pow(10, d-1)));

				if (d % 2 == 0) { 
					auto s = errcheck(l, { d / 2 }, f); 
					part1.insert(s.begin(), s.end()); 
				}

				auto s = errcheck(l, factors[l.length() - 2], f);
				part2.insert(s.begin(), s.end());
			}
			first = "";
			last = "";
			_ = 1;
		}
		else if (ch == '-') {_ = 0;	}
		else if (_) {first +=ch;}
		else {last +=ch;}
	}

	////// add the last one
	for (int d = last.length(); d >= first.length(); --d) {
		string l = (d == last.length()) ? last : to_string(int(pow(10, d) - 1));
		string f = (first.length() == d) ? first : to_string(int(pow(10, d - 1)));

		if (d % 2 == 0) {
			auto s = errcheck(l, { d / 2 }, f);
			part1.insert(s.begin(), s.end());
		}

		auto s = errcheck(l, factors[l.length() - 2], f);
		part2.insert(s.begin(), s.end());
	}
	///////////////

	long long res1 = 0;
	long long res2 = 0;
	for (auto i : part1) { res1 += i; }
	for (auto i : part2) { res2 += i; }
	cout << res1 << endl;
	cout << res2 << endl;



	auto end = chrono::steady_clock::now();
	cout << duration_cast<std::chrono::milliseconds>(end - start) << endl;

	return 0;
}