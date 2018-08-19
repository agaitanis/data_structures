#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

class Rope {
	string s;
	public:
	Rope(const string &s) : s(s) { 
	}

	void process( int i, int j, int k ) {
		// Replace this code with a faster implementation
		string t = s.substr(0, i) + s.substr(j + 1);
		s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
	}

	string result() {
		return s;
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	string s;
	cin >> s;
	Rope rope(s);
	int actions;
	cin >> actions;
	for (int action_index = 0; action_index < actions; ++action_index) {
		int i, j, k;
		cin >> i >> j >> k;
		rope.process(i, j, k);
	}
	cout << rope.result() << endl;
}
