#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int count_ocurrences(string line, string character) {
	auto num = 0;
	auto pos = 0;
	while(1) {
		pos = line.find(character, pos);
		if(pos != string::npos) {
			num++;
			pos++;
		}
		else break;
	}
	return num;
}

int main() {
	ifstream file("inputs/day_2");
	auto valid = 0;
	for(string line; getline(file, line);) {
		auto pos1 = line.find("-");
		auto pos2 = line.find(":");

		auto min = stoi(line.substr(0,pos1));
		auto max = stoi(line.substr(pos1+1, pos2-2));
		auto character = line.substr(pos2-1,1);
		auto sequence = line.substr(pos2+2);
		
		auto ocurr = count_ocurrences(sequence, character);
		
		//cout << character << ": " << sequence << " : " << ocurr << endl; 
		if(ocurr >= min and ocurr <= max) valid++;
	}
	cout << valid << endl;
	return 0;
}


