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
		cout << number << endl;
		numbers_map.insert(pair<int,int>(number,2020-number));
	}

	for(auto& number_pair : numbers_map) {
		auto got = numbers_map.find(number_pair.second);
		if(got != numbers_map.end()) {
			cout << "Num1: " << number_pair.first << endl;
			cout << "Num2: " << number_pair.second << endl;
			cout << "Result: " << number_pair.first * number_pair.second << endl;
			break;	
		}
	}
	return 0;
}


