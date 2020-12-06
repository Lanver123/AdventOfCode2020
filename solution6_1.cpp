#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

int main() {
	ifstream file("inputs/day_6");

	unordered_set<char> grupo = {};
	auto total = 0;
	for(string line; getline(file, line);) {
		if(line == "") {
			total += grupo.size();
			grupo.clear();	
		}
		for(auto &carac : line) {
			grupo.insert(carac);
		}
	}
	cout << total << endl;

	return 0;
}


