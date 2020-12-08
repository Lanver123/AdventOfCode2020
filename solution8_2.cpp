#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

class Program {
	public:
		bool infinite_loop = false;
		bool end_flag = false;

		void set_change_inst(int pos) {
			auto elem = text[pos];	
			if(elem.first == "nop") {
				text[pos].first = "jmp";
			}
			else if(elem.first == "jmp") {
				text[pos].first = "nop";
			}
		}

		void next_inst() {
			check_infloop();
			end_program();
			if(infinite_loop || end_flag) return;

			auto inst = text[ip];
			if(inst.first == "nop") nop();	
			else if(inst.first == "acc") acc(inst.second);
			else if(inst.first == "jmp") jmp(inst.second);
		}

		int acc_value() {
			return accumulator;
		}

		Program(vector<pair<string,int>> &orig_text) {
			text = orig_text;
			accumulator = 0;
			ip = 0;
			prog_size = text.size();
			ip_repes = (int*) malloc(sizeof(int) *prog_size);
			for(int i = 0; i < prog_size; i++) ip_repes[i] = 0;
		}

	private:
		size_t prog_size;	
		unsigned int ip;
		int* ip_repes;
		int accumulator;
		vector<pair<string,int>> text;

		void end_program() {
			if(ip >= prog_size) end_flag = true;
		}

		void check_infloop() {
			if(ip_repes[ip] != 0) infinite_loop = true;
			ip_repes[ip] = 1;
		}

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
	vector<pair<string,int>> origin_text;
	ifstream file("inputs/day_8");
	for(string line; getline(file, line);) {
		auto pos = line.find(" ");
		auto inst = line.substr(0,pos);
		auto num  = stoi(line.substr(pos+1));
		origin_text.push_back({inst,num});	
	}

	//Cambiar una por una todas las instrucciones
	for(int i = 0; i < origin_text.size(); i++) {
		Program prog(origin_text);
		prog.set_change_inst(i);

		while(!(prog.infinite_loop || prog.end_flag)){
			prog.next_inst();
		}

		if(prog.end_flag) {
			cout << prog.acc_value() << endl;
		}
	}


	return 0;
}

