#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

class Program {
	public:
		size_t prog_size;	
		unsigned int ip;
		void next_inst() {
			auto inst = text[ip];
			if(inst.first == "nop") nop();	
			else if(inst.first == "acc") acc(inst.second);
			else if(inst.first == "jmp") jmp(inst.second);
		}
		
		int acc_value() {
			return accumulator;
		}

		Program(ifstream &file) {
			text = {};
			for(string line; getline(file, line);) {
				auto pos = line.find(" ");
				auto inst = line.substr(0,pos);
				auto num  = stoi(line.substr(pos+1));
				text.push_back({inst,num});	
			}

			accumulator = 0;
			ip = 0;
			prog_size = text.size();
		}

	private:
		int accumulator;
		vector<pair<string,int>> text;

		void acc(int value) {
			accumulator += value;
			++ip;
		}

		void nop() {
			++ip;	
		}

		void jmp(int distance) {
			ip += distance;	
		}	
};

int main() {
	ifstream file("inputs/day_8");

	Program prog(file);
	int ip_repes[prog.prog_size];
	for(int i = 0; i < prog.prog_size; i++) ip_repes[i] = 0; 
	while(1) {
		if(ip_repes[prog.ip] != 0) break;
		ip_repes[prog.ip] = 1;
		prog.next_inst();
	}

	cout << prog.acc_value() << endl;

	return 0;
}


