#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

//
//{row,column}
pair<unsigned int, unsigned int> get_seat(string pass) {
	auto ptr = pass.c_str();
	auto end = ptr + pass.length();
	unsigned int row = 0, col = 0;

	while(ptr < end-3) { //row
		row = row << 1;
		if(*ptr == 'B') row += 1;
		++ptr;
	}

	while(ptr < end) { //column
		col = col << 1;	
		if(*ptr == 'R') col += 1;
		++ptr;
	}

	return pair<unsigned int, unsigned int>{row,col};
}

int main() {
	ifstream file("inputs/day_5");

	unsigned int max_id = 0;
	for(string line; getline(file, line);) {
		auto seat = get_seat(line);
		auto pass_id = seat.first*8 + seat.second;
		if(pass_id > max_id) max_id = pass_id;
	}

	cout << max_id << endl;

	return 0;
}


