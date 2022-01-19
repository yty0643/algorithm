#include <iostream>
#include <fstream>
#include<algorithm>
using namespace std;

int num1, num2;

ifstream in("p100.inp");
ofstream out("p100.out");

int prob() {
	
	if (num2 < num1) swap(num1, num2);

	int rr = 0;

	for (int i = num1; i <= num2; i++) {
		int a = i;
		int ct = 1;
		while (a != 1) {
			if (a % 2 == 0) {
				a = a / 2;	
			}
			else {
				a = a * 3 + 1;
			}
			ct++;
		}
		
		rr = max(rr, ct);

	}

	return rr;
}

int main() {
	
	while (in >> num1) {
			in >> num2;
			out << num1 << " ";
			out << num2 << " ";
			int ret = prob();
			out << ret << "\n";
	}

	return 0;
}
