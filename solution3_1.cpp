#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream file("inputs/day_3");

	string map[323];	
	int i = 0;
	for(string line; getline(file, line);) {
		map[i] = line;
		++i;	
	}
	
	int x = 0 , y = 0, trees = 0; 
	int map_length = map[0].length();
	for(int y = 0; y < 323; y++) {
		if(map[y][x] == '#') {
			++trees;
		map[y][x] = 'X';
		}
		else map[y][x] = 'O';
		cout << map[y] << endl;
		x = (x+3)%map_length;
	}
	 
	cout << trees << endl;	

	return 0;
}


