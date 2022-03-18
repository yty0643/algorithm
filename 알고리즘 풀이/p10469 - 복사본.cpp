#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream in("p10469.inp");
ofstream out("p10469.out");

long long int n, m;
vector<int> arr1,arr2;
int idx;

int main() {

	while (in >> n >> m) {
		arr1.clear();
		arr2.clear();
		idx = 30;

		while (n>0) {
			if (n % 2 == 1) {
				arr1[idx--] = 1;
			}
			else {
				arr1[idx--] = 0;
			}
			n /= 2;
		}
		

		while (m > 0) {
			if (m % 2 == 1) {
				arr2[idx--] = 1;
			}
			else {
				arr2[idx--] = 0;
			}
			m /= 2;
		}

		for (int i = 0; i < 30; i++) {
			cout << arr1[i];
		}
		cout << " ";
		for (int i = 0; i < 30; i++) {
			cout << arr2[i];
		}
		cout << "\n";
	}

	


	return 0;
}