#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <regex>

using namespace std;

unordered_map<string, vector<pair<string,int>>> transiciones = {};
unordered_map<string, int> cache = {};

int measure_depth(string node) {
	if(node == "end") return 0;
	auto branches = transiciones.find(node);
	auto cache_item = cache.find(node);	
	if(cache_item->second != -1) {
		return cache_item->second;
	}

	auto res = 1;
	for(auto &branch : branches->second) {
		res += measure_depth(branch.first)*branch.second;
	}	
	cache_item->second = res;

	return res;
}

pair<string, vector<pair<string,int>>> parse_line(string line) {
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

	vector<pair<string,int>> requisitos = {};
	while (finder!=end) {
		int num = 0;
		string text = "";
		auto temp = (*finder).str();
		if(temp == "no other bag") {num = 0; text = "end";}
		else {
			num = stoi(temp.substr(0,1));
			text = temp.substr(2,temp.length()-6);
		}
		requisitos.push_back({text,num});
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
	transiciones.insert({"end", {{}}});
	cache.insert({"end",0});

	cout << measure_depth("shiny gold")-1 << endl;
	return 0;
}


