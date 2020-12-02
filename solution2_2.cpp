#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream file("inputs/day_2");
	auto valid = 0;
	for(string line; getline(file, line);) {
		auto pos1 = line.find("-");
		auto pos2 = line.find(":");

		auto min = stoi(line.substr(0,pos1));
		auto max = stoi(line.substr(pos1+1, pos2-2));
		auto character = line.at(pos2-1);
		auto sequence = line.substr(pos2+2);

		auto cond1 = (sequence.at(min-1) == character);
		auto cond2 = (sequence.at(max-1) == character);
		if(cond1+cond2 == 1) valid++;
	}
	cout << valid;

	return 0;
}


