#include <string>
#include <iostream>
#include <fstream>
using namespace std;

string map[323];	
unsigned int count_trees(int x_delta, int y_delta) {
	int x = 0 , y = 0;
	unsigned int trees = 0; 
	int map_length = map[0].length();
	for(int y = 0; y < 323; y+=y_delta) {
		if(map[y][x] == '#') ++trees;
		x = (x+x_delta)%map_length;
	}
	return trees;
}

int main() {
	ifstream file("inputs/day_3");
	int i = 0;
	for(string line; getline(file, line);) {
		map[i] = line;
		++i;	
	}

	long unsigned int total_trees = 1;
	total_trees *= count_trees(1,1);
	total_trees *= count_trees(3,1);
	total_trees *= count_trees(5,1);
	total_trees *= count_trees(7,1);
	total_trees *= count_trees(1,2);

	cout << total_trees << endl;

	return 0;
}


