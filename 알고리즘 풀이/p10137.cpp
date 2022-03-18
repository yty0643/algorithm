#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

ifstream in("p10137.inp");
ofstream out("p10137.out");

int num;
double re;
vector<double> v;

void prob() {
	int avg = 0, mox = 0, na = 0;
	double hap = 0; // Æò±Õ, ¸ò, ³ª¸ÓÁö, ÃÑÇÕ

	for (int i = 0; i < v.size(); i++) {
		hap += v[i] * 100; // ¿©Çà°æºñ ÃÑ ÇÕ
	}
	int hap2 = hap;

	mox = hap2 / num;
	na = hap2 % num;

	cout << hap << " " << hap2 << " " << num << " " << mox << " " << na << "\n";

	double mox2 = mox / 100.0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] > mox2) {
			re = re + (v[i] - mox2);
			if (na != 0) {
				re -= 0.01;
				na--;
			}
		}
	}
	out << fixed;
	out.precision(2);
	out << "$" << re << "\n";

	re = 0;
	v.clear();
}

int main() {
	in >> fixed;
	while (1) {
		in >> num;
		if (num == 0) break;

		for (int i = 0; i < num; i++) {
			double p; // °³ÀÎÀÌ ÁöºÒÇÑ µ·
			in >> p;
			v.push_back(p);
		}
		prob();
		//cout << re;
	}



	return 0;
}