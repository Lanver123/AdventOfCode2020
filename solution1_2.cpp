#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

int main() {
	unordered_map<int, int> numbers_map;
	ifstream file("inputs/day_1");
	for(string line; getline(file, line);) {
		auto number = stoi(line);
		numbers_map.insert(pair<int,int>(number,0));
	}

	for(auto& number_pair : numbers_map) {
		for(auto &number_pair2 : numbers_map) {
			auto num1 = number_pair.first;
			auto num2 = number_pair2.first;
			auto num3 = 2020 - num1 - num2;
			if(numbers_map.find(num3) != numbers_map.end()) {
				cout << num1*num2*num3 << endl;
				exit(0);
			}
		}
	}
	return 0;
}


