#include <iostream>
using namespace std;

int main() {
	unsigned int num = 0;

	for(int i = 0; i <8 ; i++) {
		if(i%2==0) num += 1;
		num = num << 1;
	}

	cout << num << endl;

	return 0;
}
