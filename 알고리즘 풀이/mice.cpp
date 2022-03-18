#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stack>

using namespace std;

ifstream in("mice.inp");
ofstream out("mice.out");

int t, k, h, n, m; //testcase, 벽,유량,집,쥐
int e;
bool ret;
vector<pair<long long int, long long int>> wall, hole, mouse; //벽,집,쥐 //s-쥐-집-e    =>    1->2->2
vector<vector<int>> v;
vector<int>visit;
stack<int> s;
stack<int> s1;

int ccw(pair<long long int, long long int> a, pair<long long int, long long int> b, pair<long long int, long long int> c) {
	long long int op = a.first * b.second + b.first * c.second + c.first * a.second;
	op -= (a.second * b.first + b.second * c.first + c.second * a.first);
	if (op > 0)return 1;
	else if (op == 0)return 0;
	else return -1;
}

int isIntersect(pair<long long int, long long int> a, pair<long long int, long long int> b, pair<long long int, long long int> c, pair<long long int, long long int> d) {
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
	
	for (int i = 1; i <= m; i++) {
		v[0][i] = 1;
	}
	for (int i = m + 1; i <= n + m; i++) {
		v[i][e] = h;
	}

	for (int i = 0; i < m; i++) { // 0:s   n+m+1: e        1~m쥐             m+1~ n+m쥐구멍
		for (int j = 0; j < n; j++) {
			int cnt = 0; // 쥐-집, 벽 의 충돌여부 카운트 2이상이면 못감
			v[i + 1][j + 1 + m] = h;
			for (int z = 0; z < k; z++) {
				if (isIntersect(mouse[i], hole[j], wall[z], wall[(z + 1) % wall.size()])) { //교차하면 카운트++
					if (hole[j] == wall[z])
						continue;
					cnt++;
				}
				if (cnt > 1) { // 카운트2이상 못감.
					v[i + 1][j + 1 + m] = 0;
					break;
				}
			}
		}
	}
}

bool F2(int idx) {
	
	
	visit[idx] = 1;
	if (idx == e) 
		return ret = true;

	for (int i = 0; i < v.size(); i++) {
		if (visit[i] == 1 || idx == i || v[idx][i] == 0) continue;
		s.push(i);
		
		if(F2(i)) {
			int temp = s.top();
			s.pop();
			v[idx][temp]--;
			v[temp][idx]++;
			return ret;
		}
	}
	s.pop();
	return ret;
}

int main() {
	in >> t;
	while (t--) {
		in >> k >> h >> n >> m;
		v.clear();
		v.resize(2 + n + m, vector<int>(2 + n + m));
		wall.clear();
		hole.clear();
		mouse.clear();

		for (int i = 0; i < k; i++) {
			int val, val2; in >> val >> val2;
			wall.push_back({ val,val2 });
		}
		for (int i = 0; i < n; i++) {
			int val, val2; in >> val >> val2;
			hole.push_back({ val,val2 });
		}
		for (int i = 0; i < m; i++) {
			int val, val2; in >> val >> val2;
			mouse.push_back({ val,val2 });
		}
		e = v.size() - 1;
		F(); //그래프


		
		while (1) {
			ret = false;
			visit.clear();
			visit.resize(n + m + 2);
			s = s1;
			s.push(0);
			if (!F2(0))break;
		}

		int ret2 = 0;
		for (int i = 0; i < v.size(); i++) {
			ret2 += v[v.size() - 1][i];
		}
		if (ret2 == m) out << "Possible\n";
		else out << "Impossible\n";
	}


	return 0;
}