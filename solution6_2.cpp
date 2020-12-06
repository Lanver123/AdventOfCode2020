#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

int num_consensos(unordered_map<char,int> votos, int num_pers) {
	int res = 0;
	for(auto &pair : votos) {
		if(pair.second == num_pers) ++res;
	}
	return res;
}
int main() {
	ifstream file("inputs/day_6");

	unordered_map<char, int> grupo = {};
	auto total = 0;
	auto num_pers = 0;
	for(string line; getline(file, line);) {
		if(line == "") {
			total += num_consensos(grupo, num_pers);
			num_pers = 0;
			grupo.clear();	
		}
		else {
			num_pers++;
			for(auto &carac : line) {
				auto obt = grupo.find(carac);
				if(obt != grupo.end()) {
					obt->second += 1;
				}
				else {
					grupo.insert({carac,1});
				}
			}
		}
	}
	cout << total << endl;

	return 0;
}


