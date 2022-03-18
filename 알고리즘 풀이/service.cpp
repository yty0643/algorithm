#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stack>
#include <queue>
#include <memory.h>
using namespace std;

ifstream in("service.inp");
ofstream out("service.out");

int t, team_num, term_num, service_num; //�� ����, ���� �Ⱓ ����, ���� ���� ����
int v[11000][11000];
int v_size;
vector<int>v1, v2; // ����Ⱓ, �������� ���� index ����� ����
int level[11000];
int work[11000];
vector<vector<int>> arr;


bool F(int start) {
	if (start == v_size - 1)
		return true;

	for (int& x = work[start]; x < arr[start].size(); x++) {
		int i = arr[start][x];
		if (level[start] + 1 == level[i] && v[start][i] > 0) {
			if (F(i)) {
				v[start][i] --;
				v[i][start] ++;
				arr[i].push_back(start);
				return true;
			}
		}
	}
	return false;
}

bool F_level() {
	memset(level, -1, v_size * 4);
	level[0] = 0;
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int start = q.front();
		q.pop();
		for (int i = 0; i < arr[start].size(); i++) {
			int next = arr[start][i];
			if (start == next || level[next] != -1 || v[start][next] == 0) continue;
			level[next] = level[start] + 1;
			q.push(next);
		}
	}
	if (level[v_size - 1] == -1)return false;
	return true;
}


int main() {
	in >> t;
	while (t--) {
		v_size = 0; //��� ����
		int ret = 0; //tink���� ���
		int total_num = 0; //�� �������� ��
		in >> team_num >> term_num >> service_num;
		//v.clear();
		arr.clear();
		arr.resize(11000);
		v1.clear();
		v2.clear();
		v1.push_back(0);
		v2.push_back(0);

		for (int i = 1; i <= team_num; i++) {
			if (i == 1) {
				v1.push_back(team_num);
				continue;
			}
			v1.push_back(v1[i - 1] + term_num); //����Ⱓ ����idx
		}

		for (int i = 1; i <= term_num; i++) { // ����Ⱓ ���� ��ŭ
			if (i == 1) {
				v2.push_back(team_num + team_num * term_num);
				continue;
			}
			int val; in >> val; // i ����Ⱓ�� ���� ����
			total_num += val; // �� �������� ����
			v2.push_back(v2[i - 1] + val); //�������� ����idx
		}
		int val; in >> val; //�ѹ� �� �Է�( ���� for���� i=1�� �Է¾ȹް�Ѿ�⶧��
		total_num += val;

		v_size = team_num + team_num * term_num + total_num + 2; // ��� ����
		//v.resize(v_size, vector<int>(v_size)); // ��Ʈ��ũ ũ�� ����
		memset(v, 0, sizeof(v));

		for (int i = 1; i <= team_num; i++) {
			int val; in >> val;
			for (int j = 0; j < val; j++) {
				int val1, val2; in >> val1 >> val2;
				int a = v1[i] + val1;
				int b = v2[val1] + val2;
				v[i][a] = 1;
				v[a][b] = 1;
				arr[i].push_back(a);
				arr[a].push_back(b);
			}
		}

		for (int i = 1; i <= team_num; i++) {
			v[0][i] = service_num;
			arr[0].push_back(i);
			for (int j = 1; j <= term_num; j++) {
				v[i][v1[i] + j] = 1;
				arr[i].push_back(v1[i] + j);
			}
		}

		for (int i = 1; i <= total_num; i++) {
			v[v_size - 1 - i][v_size - 1] = 1;
			arr[v_size - 1 - i].push_back(v_size - 1);
		}

		int z = 0;
		while (F_level()) {
			memset(work, 0, v_size * 4);
			while (1) {
				if (!F(0))break;
				//else cout << z++ << "\n";
			}
		}
		for (int i = 1; i <= total_num; i++) {
			ret += v[v_size - 1][v_size - 1 - i];
		}
		if (total_num == ret)
			out << 1 << "\n";
		else
			out << 0 << "\n";
	}

	return 0;
}