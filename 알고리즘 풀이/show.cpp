#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;
ifstream in("show.inp");
ofstream out("show.out");
vector<vector<int>> v;
vector<vector<int>> v2;
stack<int> s;
vector<int>visit;
vector<int>scc;
vector<int> test, test2;
int t, n, m;
bool ret;
void addEdge(int a, int b) {
	v[a].push_back(b);
	v2[b].push_back(a);
}

int inv(int x) {
	if (x > n) return x - n;
	return x + n;
}

void addCNF(int s, int e) {
	if (s < 0) s = inv(-s);
	if (e < 0) e = inv(-e);
	addEdge(inv(s), e);
	addEdge(inv(e), s);
}


void F(int idx) {
	if (visit[idx] == 1) return;
	visit[idx] = 1;
	for (int i = 0; i < v[idx].size(); i++) {
		F(v[idx][i]);
	}
	s.push(idx);
}

void F3(int idx) {
	if (scc[idx] == 1) return;
	scc[idx] = 1;
	for (int i = 0; i < v2[idx].size(); i++) {
		test[idx] = 1;
		test2.push_back(idx);
		F3(v2[idx][i]);
	}
}

void F2() {
	while (!s.empty()) {
		if (scc[s.top()] == 1) {
			s.pop();
			continue;
		}
		int idx = s.top();
		test.clear();
		test.resize(n * 2 + 1);
		test2.clear();
		F3(idx);
		for (int i = 0; i < test2.size(); i++) {
			int x = test2[i];
			if (x > n) {
				if (test[x - n] == 1) {
					ret = false;
					return;
				}
			}
			else {
				if (test[x + n] == 1) {
					ret = false;
					return;
				}
			}
		}
		s.pop();
	}
}



int main() {
	in >> t;
	while (t--) {
		ret = true;
		in >> n >> m;
		while (!s.empty())s.pop();
		v.clear();
		v2.clear();
		visit.clear();
		scc.clear();
		v.resize(n * 2 + 1);
		v2.resize(n * 2 + 1);
		visit.resize(n * 2 + 1);
		scc.resize(n * 2 + 1);

		for (int i = 0; i < m; i++) {
			int a[4]; char b[4];
			for (int j = 0; j < 3; j++) in >> a[j] >> b[j];
			a[3] = a[0], b[3] = b[0];
			for (int j = 0; j < 4; j++)
				if (b[j] == 'B') a[j] *= -1;
			for (int j = 0; j < 3; j++) {
				addCNF(a[j], a[j + 1]);
			}
		}

		for (int i = 1; i < n * 2 + 1; i++) {
			F(i);

		}
		for (int i = 1; i < n * 2 + 1; i++) {
			F2();
			if (!ret) {
				out << -1 << "\n";
				break;
			}
		}
		if (ret)out << 1 << "\n";
	}
}