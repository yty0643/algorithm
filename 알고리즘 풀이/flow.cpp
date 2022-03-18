#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

ifstream in("flow.inp");
ofstream out("flow.out");

int n, ret; // 노드개수, 결과
int maxlv; // 최종레벨

typedef struct levelinfo {
	int start;
	int next;
}levelinfo;
typedef struct nodeinfo {
	int num;
	int level;
}nodeinfo;

vector<vector<int>> arr;
vector<vector<int>> edge;
vector<vector<levelinfo>> lv;


int F_path(int st, int level, int aug) {

	if (level == maxlv+1)
		return aug;

	for (int i = 0; i < lv[level].size(); i++) {
		int a = lv[level][i].start;
		if (a != st)continue;
		int b = lv[level][i].next;
		int c = edge[a][b];
		c = F_path(b,level + 1, min( aug, c));
		if (c == 0)continue;
		edge[a][b] -= c;
		edge[b][a] += c;
		return c;
	}
	return 0;
}

bool level() {
	vector<levelinfo> v;
	vector<int> visit(n);
	lv.clear();
	queue<nodeinfo> q;
	q.push({ 0,0 });
	visit[0] = 1;

	while (!q.empty()) {
		int node = q.front().num;
		int level = q.front().level;
		q.pop();

		for (int i = 0; i < arr[node].size(); i++) {
			int temp = arr[node][i];
			if (edge[node][temp] > 0 && visit[temp] == 0) {
				if (lv.size() == level)
					lv.push_back(v);

				q.push({ temp,level + 1 });
				lv[level].push_back({ node,temp });
				visit[temp] = 1;
				if (temp == n - 1) {
					lv[level].clear();
					lv[level].push_back({ node,temp });
					maxlv = level;
					return true;
				}
			}
		}
	}
	return false;
}

int main() {

	in >> n;
	edge.resize(n);
	arr.resize(n);
	for (int i = 0; i < n; i++) {
		edge[i].resize(n);
	}

	while (1) {
		int a, b, c; in >> a >> b >> c;
		if (a == -1) break;
		edge[a][b] = c;
		edge[b][a] = c;
		arr[a].push_back(b);
		arr[b].push_back(a);
	}

	while (level()) {
		while (1) {
			int p = F_path(0,0, 1000000);
			if (!p)break;
			ret += p;
		}
	}
	out << ret;

	return 0;
}