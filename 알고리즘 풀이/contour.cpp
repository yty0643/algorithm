#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;

ifstream in("contour.inp");
ofstream out("contour.out");

typedef struct point {
	ll x;
	ll y;
	ll s; //1:시작 0:끝
}point;

vector<point> v;
priority_queue<point> q;
priority_queue<point> q2;

bool operator<(point a, point b) {
	if (a.y < b.y) 
		return true;
	return false;
}

bool cmp(point a, point b) {
	if (a.x < b.x)
		return true;
	else if (a.x == b.x)
		if (a.y < b.y)
			return true;
	return false;
}

void solution() {
	ll area = 0;
	for (int i = 0; i < v.size(); i++) {
		if (q.empty()) {
			q.push(v[i]);
			continue;
		}
		if (v[i].s) { // 시작 점
			area += (v[i].x - v[i - 1].x) * q.top().y;
			q.push(v[i]);
		}
		else { // 끝 점
			area += (v[i].x - v[i - 1].x) * q.top().y;
			q2.push(v[i]);
			while (q.top().y == q2.top().y) {
				q.pop();
				q2.pop();
				if (q.empty()) break;
				if (q2.empty()) break;
			}
		}
		if (q.empty()) {
			out << " " << area;
			area = 0;
		}
	}
}

int main() {
	ll s, h, e;
	int n = 1;
	while (in >> s) {
		in >> h >> e;
		if (!(s == 0 && h == 0)) {
			v.push_back({ s,h,1 });
			v.push_back({ e,h,0 });
		}
		else {
			out << "Test Case #" << n++ << " :";
			sort(v.begin(), v.end(), cmp);
			solution();
			out << "\n";
			v.clear();
		}
	}
	return 0;
}