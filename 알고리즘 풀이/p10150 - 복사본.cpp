
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include<queue>
#include<memory.h>

using namespace std;

ifstream in("p10150.inp");
ofstream out("p10150.out");

vector<string> v;
string arr[2];
string n, m;

int visit[30000];
int pre[30000]; // idx 가 어디서 왔냐


// 라는 벡터가 있고 각 인덱스있지


bool search(string a, string b) {

	if (a.size() != b.size()) return false;

	int cnt = 0;
	for (int i = 0; i < a.size(); i++) {

		if (a[i] != b[i]) cnt++;
	}

	if (cnt == 1) return true;

	return false;


}


void prob(int idx) {

	queue < pair<string, int> > q;


	q.push({ v[idx] , idx }); //  {boa  1 }


	while (!q.empty()) {


		string a = q.front().first; // boa
		int idxx = q.front().second; // 1

		q.pop();

		for (int i = 0; i < v.size(); i++) {
			if (visit[i] == -1) {
				if (search(a, v[i])) {

					visit[i] = visit[idxx] + 1;
					pre[i] = idxx;

					q.push({ v[i] , i });
				}
			}
		}
	}

}

int main() {

	while (getline(in, n)) {
		if (n == "")break;
		v.push_back(n);
	}

	while (in >> n >> m) {

		int idx1 = -1, idx2 = -1;
		for (int i = 0; i < v.size(); i++) {

			if (v[i] == n) {
				idx1 = i;
			}
			if (v[i] == m) {
				idx2 = i;
			}
		}

		memset(visit, -1, sizeof(visit));
		memset(pre, -1, sizeof(pre));
		visit[idx1] = 0;

		prob(idx1);


		if (pre[idx2] == -1) {
			out << "No solution.\n\n";
			continue;
		}
		vector<string> ret;

		ret.push_back(v[idx2]);

		while (pre[idx2] != -1) {

			idx2 = pre[idx2];

			ret.push_back(v[idx2]);
		}


		reverse(ret.begin(), ret.end());

		for (int i = 0; i < ret.size(); i++) {
			out << ret[i] << "\n";
		}
		out << "\n";
	}

	return 0;
}