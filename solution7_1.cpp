#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <regex>

using namespace std;

unordered_map<string, vector<string>> transiciones = {};
unordered_map<string, int> cache = {};

bool find_shiny_gold(string origin) {
	auto cache_elem = cache.find(origin);
	if(cache_elem == cache.end()) return 0;
	switch(cache_elem->second) {
		case 1: return true;
		case 0: return false;
		case -1: 
			if(origin == "shiny gold") return true;
			bool correct = false;
			auto branches = transiciones.find(origin);
			for(auto &branch : branches->second) {
				correct |= find_shiny_gold(branch);
			}
			if(correct) {
				cache_elem->second = 1;
				return true;
			}
			else {
				cache_elem->second = 0;
				return false;
			}
	}
	cout << "Something wrong..." << endl;
	return 0;
}

pair<string, vector<string>> parse_line(string line) {
	// 1 divide line between header and list
	auto pos = line.find("contain");
	auto header = line.substr(0,pos-2);
	auto list = line.substr(pos+7);

	// 2 parse header
	regex rgx1("^([\\w ]+) bag.?$");
	std::smatch matches1;
	regex_search(header, matches1, rgx1);
	auto primero = matches1[1];

	// 3 parse list
	regex rgx2("(\\w+ [\\w ]+) bag");
	sregex_token_iterator end;
	sregex_token_iterator finder(list.begin(), list.end(), rgx2);

	vector<string> requisitos;
	while (finder!=end) {
		auto temp = (*finder).str();
		if(temp == "no other bag") {
			requisitos.push_back(temp.substr(0,temp.length()-4));
		}
		requisitos.push_back(temp.substr(2,temp.length()-6));
		finder++;
	}

	return {primero, requisitos};
}

int main() {
	ifstream file("inputs/day_7");

	// 1 obtener información
	for(string line; getline(file, line);) {
		auto info = parse_line(line);
		transiciones.insert({info.first, info.second});
		cache.insert({info.first, -1});
	}
	cout << "total captured: " << transiciones.size() << endl;

	auto total_result = 0;
	for(auto &key : transiciones) {
		if(find_shiny_gold(key.first)) {
			cout << key.first << endl;
			total_result++;
		}
	}

	cout << total_result << endl;
	return 0;
}


