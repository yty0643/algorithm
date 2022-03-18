#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
ifstream in("point.inp");
ofstream out("point.out");

int n, m;
vector<pair<int, int>> v;
pair<int, int> p, origin;

int ccw2(pair<int, int> a, pair<int, int> b) {
	return a.first * b.second - a.second * b.first;

}

int ccw(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
	pair<int, int> x, y;
	x.first = b.first - a.first; // b-a
	x.second = b.second - a.second;

	y.first = c.first - a.first; // b-a
	y.second = c.second - a.second;
	return ccw2(x, y);
}

bool leftTurn(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
	if( ccw(a, b, c) > 0) return true;
	return false;
}
bool collinear(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
	if (ccw(a, b, c) == 0) return true;
	return false;
}

bool between(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
	if (collinear(a, b, c) == false)return false;
	if (a.first != b.first) {
		if (a.first <= c.first && c.first <= b.first || b.first <= c.first && c.first <= a.first) return true;
	}
	else {
		if (a.second <= c.second && c.second <= b.second || b.second <= c.second && c.second <= a.second) return true;
	}
	return false;
}

bool prob() {
	int cnt = 0;
	for (int i = 0; i < v.size(); i++) { // 원점 이동 -p(x.y) 해주면 됨
		v[i].first -= p.first;
		v[i].second -= p.second;
	}
	for (int i = 0; i < v.size(); i++) {
		int iPlus = (i+1) % v.size();
		if (between(v[i], v[iPlus], origin)) return true;
		if ((v[i].second < 0 && v[iPlus].second >= 0 && leftTurn(v[i], v[iPlus], origin)) ||
			(v[iPlus].second < 0 && v[i].second >= 0 && leftTurn(v[iPlus], v[i], origin))) cnt++;
	}
	if (cnt % 2 == 1) return true;
	
	return false;
	// 원점 기준 p[i], p[iPuls] 각각 음수 양수일 때만 좌회전 판단.
	// 도형q의 선분 위에 p가 존재하는지 판단 true -> return ( 안에 있다. : 0 / false )
}
int main() {

	in >> n;
	while (n--) {
		in >> p.first >> p.second;
		v.push_back(p);
	}

	in >> m;
	while (m--) {
		in >> p.first >> p.second;
		out << prob() << "\n";
		for (int i = 0; i < v.size(); i++) { // 원점 이동 -p(x.y) 해주면 됨
			v[i].first += p.first;
			v[i].second += p.second;
		}
	}




	return 0;
}