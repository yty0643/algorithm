#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream in("rectangles.inp");
ofstream out("rectangles.out");

int n, maxV;
vector<long long int> v;
vector<int> arr;

int gcd(int a, int b) {
	if (b == 0)
		return a;
	gcd(b, a % b);
}

int main() {
	in >> n;

	for (int i = 0; i < n; i++) {
		int val; in >> val;
		maxV = max(maxV, val);
		arr.push_back(val);
	}
	maxV *= 100;
	for (int i = 0; i < n; i++) {
		int ret = 0;
		int a = 1;
		while (a++) {
			for (int b = 0; b < a; b++) {
				if ((a + b) % 2 == 0)
					continue;
				if (gcd(a, b) > 1)
					continue;

				if (v.size() == ret) {
					int w = (a * a) - (b * b);
					int h = 2 * a * b;
					v.push_back(2 * (w + h));
					maxV -= v[ret];
					if (maxV <= 0)
						break;
					ret++;
				}
				else {
					maxV -= v[ret];
					if (maxV <= 0)
						break;
					ret++;
				}
			}
			if (maxV <= 0)
				break;
		}
	}
	sort(v.begin(), v.end());

	for (int i = 0; i < n; i++) {
		int ret = 0;
		int a = 1;
		while (a++) {
			for (int b = 0; b < a; b++) {
				if ((a + b) % 2 == 0)
					continue;
				if (gcd(a, b) > 1)
					continue;

				arr[i] -= v[ret];
				if (arr[i] < 0)
					break;
				ret++;

			}
			if (arr[i] <= 0)
				break;
		}
		out << ret << "\n";
	}
	return 0;
}