#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>


using namespace std;

ifstream in("triangle.inp");
ofstream out("triangle.out");

int n;

typedef long long ll;
pair<ll, ll>val;
vector<pair<ll, ll>> v;
vector<vector<int>> A;
vector<vector<int>> B;

int between(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c) {
	if (a.first != b.first) {
		if (a.first <= c.first && c.first <= b.first || b.first <= c.first && c.first <= a.first)
			return 0;
		else
			return 4;
	}
	else {
		if (a.second <= c.second && c.second <= b.second || b.second <= c.second && c.second <= a.second)
			return 0;
		else
			return 4;
	}
}

int ccw(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c) {
	ll op = a.first * b.second + b.first * c.second + c.first * a.second;
	op -= (a.second * b.first + b.second * c.first + c.second * a.first);
	if (op > 0)return 1;
	else if (op == 0)return between(a, b, c);
	else return -1;
}

int isIntersect(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c, pair<ll, ll> d) {
	int ab = ccw(a, b, c) * ccw(a, b, d);
	int cd = ccw(c, d, a) * ccw(c, d, b);
	if (ab == 0 && cd == 0) {
		if (a > b)swap(a, b);
		if (c > d)swap(c, d);
		return c <= b && a <= d;
	}
	return ab <= 0 && cd <= 0;
}
void F() {
	for (int i = 0; i < 3; i++) {
		for (int j = 3; j < 6; j++) {
			int k = i % 3 ? i + 3 : 3;
			int l = (k + 1) % 6 ? k + 1 : 3;
			A[i].push_back(ccw(v[i], v[(i + 1) % 3], v[j]));
			B[i].push_back(ccw(v[k], v[l], v[j - 3]));
		}
	}
}

int F2() {
	int jup = 0;
	if ((A[0][0] < 0 && A[1][0] < 0 && A[2][0] < 0 )|| (A[0][0] > 0 && A[1][0] > 0 && A[2][0] > 0)) //내부 점 겹침
		return 2;
	if ((A[0][1] < 0 && A[1][1] < 0 && A[2][1] < 0 )|| (A[0][1] > 0 && A[1][1] > 0 && A[2][1] > 0))
		return 2;
	if ((A[0][2] < 0 && A[1][2] < 0 && A[2][2] < 0 )|| (A[0][2] > 0 && A[1][2] > 0 && A[2][2] > 0))
		return 2;

	if ((B[0][0] < 0 && B[1][0] < 0 && B[2][0] < 0) || (B[0][0] > 0 && B[1][0] > 0 && B[2][0] > 0))
		return 2;
	if ((B[0][1] < 0 && B[1][1] < 0 && B[2][1] < 0) || (B[0][1] > 0 && B[1][1] > 0 && B[2][1] > 0))
		return 2;
	if ((B[0][2] < 0 && B[1][2] < 0 && B[2][2] < 0) || (B[0][2] > 0 && B[1][2] > 0 && B[2][2] > 0))
		return 2;

	if (A[0][0] <= 0 && A[0][1] <= 0 && A[0][2] <= 0) //세선분 겹침  또는 안에 존재함 우선순위를 저 아래로 둬야할듯 내용이 너무 길어서
		if (A[1][0] <= 0 && A[1][1] <= 0 && A[1][2] <= 0)
			if (A[2][0] <= 0 && A[2][1] <= 0 && A[2][2] <= 0)
				return 2;
	if (B[0][0] <= 0 && B[0][1] <= 0 && B[0][2] <= 0)
		if (B[1][0] <= 0 && B[1][1] <= 0 && B[1][2] <= 0)
			if (B[2][0] <= 0 && B[2][1] <= 0 && B[2][2] <= 0)
				return 2;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (A[i][j] * A[i][(j + 1) % 3] < 0) // 교차 겹침
				if (B[j][i] * B[j][(i + 1) % 3] < 0)
					return 2;
			if (i < 2 && A[i][j] == 0) //두점과 두 선분 접함=>겹침
				for (int k = 1; k < 3; k++) {
					if (A[i + 1][(i + k) % 3] == 0)
						return 2;
					if (i == 0) {
						if (A[i + 2][(i + k) % 3] == 0)
							return 2;
					}
				}
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (A[i][j] == 0 || B[i][j] == 0) return 3;
		}
	}

	return 1;
}

int main() {
	in >> n;
	while (n--) {
		v.clear();
		A.clear();
		B.clear();
		A.resize(3);
		B.resize(3);
		for (int i = 0; i < 6; i++) {
			in >> val.first >> val.second;
			v.push_back(val);
		}
		F();
		out << F2() << "\n";
	}


	return 0;
}