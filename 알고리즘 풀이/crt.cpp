#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAX 1000000007
using namespace std;

ifstream in("crt.inp");
ofstream out("crt.out");

typedef long long int ll;

ll n, m, ret;
ll a = -1, b, c, d; // a,b는 최초입력시 값을 입력받고 이후부터는 함수리턴값을 유지


ll gcd(ll a, ll b) {//a,b,c최대공
	if (b == 0)return a;
	gcd(b, a % b);
}
ll gcd2(ll a, ll b) {
	ll r1 = a;
	ll r2 = b;
	ll s1 = 1;
	ll s2 = 0;
	ll t1 = 0;
	ll t2 = 1;
	ll q = 0;
	ll r = 0;
	ll s = 0;
	ll t = 0;
	while (r2 > 0) {
		q = r1 / r2;
		r = r1 - r2 * q;
		r1 = r2;
		r2 = r;
		s = s1 - s2 * q;
		s1 = s2;
		s2 = s;
		t = t1 - t2 * q;
		t1 = t2;
		t2 = t;
	}


	return s1;
}

void F_1() {
	if (d < 0) { // d 양수화
		ll x = ceil(abs(d) / (double)c);
		ll x1 = x ? x : 1;
		d += c * x1;
	}
	if (d >= c) { //나머지가 c보다 크면 빼줌
		ll x = floor(abs(d) / c);
		d -= c * x;
	}
	ll g = gcd(gcd(a, d), c);
	if (g > 1) { //a,d,c 최대공약수 1보다 크면 나누어줌
		a /= g;
		c /= g;
		d /= g;
	}
}

bool F() { // ax + b = d(mod c)

	ll e = a;
	d -= b;// ax = d-b(mod c)
	F_1();
	//이까지가 4a = d(mod c)
	if (gcd(a, c) > 1) return false;
	ll g2 = gcd2(a, c);
	d *= g2;

	F_1();

	a = e * c;
	b = e * d + b;
	return true;

}

int main() {
	in >> n;
	while (n--) {

		in >> m;
		a = -1;
		while (m--) {
			ll val1, val2; in >> val1 >> val2;
			if (a == -1) {
				b = val1;
				a = val2;
				continue;
			}
			else {
				d = val1;
				c = val2;
				if (ret)continue;
				if (!F()) {
					out << -1 << "\n";
					ret = 1;
				}
			}

		}
		if (!ret) {
			out << b << "\n";
		}
		else {
			ret = 0;
		}
	}



	return 0;
}