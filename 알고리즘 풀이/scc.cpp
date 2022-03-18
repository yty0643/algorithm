#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stack>

using namespace std;

ifstream in("scc.inp");
ofstream out("scc.out");
int n, m, ret;
vector<vector<int>> v(10000);
vector<vector<int>> v2(10000);
stack<int> s;
vector<int>visit;
vector<int>scc;

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
		F3(idx);
		ret++;
		s.pop();
	}

}


int main() {
	in >> n >> m;
	visit.resize(n);
	scc.resize(n);
	for (int i = 0; i < m; i++) {
		int val, val2; in >> val >> val2;
		v[val].push_back(val2);
		v2[val2].push_back(val);
	}
	for (int i = 0; i < n; i++) {
		F(i);
	}
	for (int i = 0; i < n; i++) {
		F2();
	}

	out << ret;
	return 0;
}