#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <utility>

using namespace std;

vector<pair<string,string>> get_entries(string line) {
	vector<pair<string,string>> res;
	auto start = line.c_str();
	auto end = start + line.length() -1;
	auto size = count(start,end,' ');
	auto pos = 0;
	for(int i = 0; i < size+1; i++) {
		string entry, value;
		auto dotdot = line.find(':',pos);
		auto blank = line.find(' ',dotdot);
		if(blank == -1) blank = line.length()+1;
		entry = line.substr(pos,dotdot-pos);
		value = line.substr(dotdot+1, blank-dotdot-1);
		res.push_back({entry,value});
		pos = blank+1;
	}

	return res;
}
class InfoPasajero {
	private:
		unordered_map<string, pair<bool,string>> map_fields = {
			{"byr",{0,""}},
			{"iyr",{0,""}},
			{"eyr",{0,""}},
			{"hgt",{0,""}},
			{"hcl",{0,""}},
			{"ecl",{0,""}},	
			{"pid",{0,""}},
			{"cid",{1,""}} //OPTIONAL AT THE TIME
		};

	public:
		void insert_entry(string segment, string value);
		bool check_validity();
		InfoPasajero() {};

};

void InfoPasajero::insert_entry(string field, string value) {
	auto entry = map_fields.find(field);
	entry->second.first = 1;
	entry->second.second = value;
}

bool InfoPasajero::check_validity() {
	for (auto it : map_fields) {
		string entry = it.first;
		string value = it.second.second;
		if(!it.second.first) return false;
		if(entry.compare("byr")==0) {
			if(value.length() != 4) return false;
			auto num = stoi(value);
			if(num < 1920 or num > 2002) return false;
		}
		if(entry.compare("iyr")==0) {
			if(value.length() != 4) return false;
			auto num = stoi(value);
			if(num < 2010 or num > 2020) return false;
		}
		if(entry.compare("eyr")==0) {
			if(value.length() != 4) return false;
			auto num = stoi(value);
			if(num < 2020 or num > 2030) return false;
		}
		if(entry.compare("hgt")==0) {
			if(value.length() < 3) return false;
			string measure = value.substr(value.length()-2,2);
			auto num = stoi(value.substr(0,value.length()-2));
			if(measure.compare("cm")==0) {
				if(num<150 or num>193) return false;	
			}
			else if(measure.compare("in")==0) {
				if(num<59 or num>76) return false;	
			}
			else return false;
		}
		if(entry.compare("hcl")==0) {
			auto ptr = value.c_str();
			for(int i = 0; i < value.length(); i++) {
				if(i == 0) {if(*ptr!='#') return false;}
				else {
					if(*ptr<48 or *ptr>122) return false;
					if(*ptr>57 and *ptr<97) return false;
				}
				++ptr;
			}
		}
		if(entry.compare("ecl")==0) {
			string comp[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
			bool is_inside = false;
			for(auto &elem : comp) {
				is_inside |= value.compare(elem) == 0;
			}

			if(!is_inside) return false;
		}

		if(entry.compare("pid")==0) {
			if(value.length() != 9) return false;
			auto ptr = value.c_str();
			for(int i = 0; i < 9; i++) {
				if(*ptr < 48 or *ptr > 122) return false;
				++ptr;
			}
		}

		if(entry.compare("cid")==0) {}
	
			
	}
	return true;
}

int main() {
	ifstream file("inputs/day_4");
	int total_correct = 0;

	while(!file.eof()) {
		InfoPasajero pasajero;
		string line;
		while(1) {
			getline(file,line);
			if(line == "") break;
			auto entries = get_entries(line);
			for(auto &pair : entries) {
				pasajero.insert_entry(pair.first, pair.second);
			}
		}
		if(pasajero.check_validity()) ++total_correct;
	}

	cout << total_correct << endl;
	return 0;
}


