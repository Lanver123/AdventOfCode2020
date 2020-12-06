#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

//
unsigned int get_seat(string pass) {
	auto ptr = pass.c_str();
	auto end = ptr + pass.length();
	unsigned int seat = 0;

	while(ptr < end-3) { //row
		seat = seat << 1;
		if(*ptr == 'B') seat += 1;
		++ptr;
	}

	while(ptr < end) { //column
		seat = seat << 1;	
		if(*ptr == 'R') seat += 1;
		++ptr;
	}

	return seat;
}

int main() {
	ifstream file("inputs/day_5");

	int seats[1024];

	//Just in case que me la ha liado alguna vez
	for(int i = 0; i < 1024; i++) seats[i] = 0;

	for(string line; getline(file, line);) {
		auto seat = get_seat(line);
		seats[seat] = 1;
	}

	
	for(unsigned int i = 1; i < 1024-1; i++) {
		if(seats[i] == 0 && seats[i-1] == 1 && seats[i+1] == 1) {
			cout << i << endl;
			break;
		}
	}




	return 0;
}


