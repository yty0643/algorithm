#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

ifstream in("subrange.inp");
ofstream out("subrange.out");
int n;
pair<int, int>min1 = { -1,2000001 };
pair<int, int>max1 = { -1,-2000001 };

typedef struct node {
	int idx;
	int val;
}node;
vector<int> arr;
vector<int> segTree;

void update(int start, int end, int val, int left, int right, int idx) { //�ٲ� ����s~e Ʈ�� ���� l~r , tree node��ȣ
	int mid = (left + right) / 2;
	if (start > right || end < left)
		return; // �������϶�
	else if (start <= left && end >= right) { // �ٲ� �����ȿ� ��������� �ִ�
		segTree[idx] += val;
		return;
	}
	else { // �ٲ� ������ ������� �ȿ��ִ�
		update(start, end, val, left, mid, idx * 2); // �����ڽ� ������Ʈ
		update(start, end, val, mid + 1, right, idx * 2 + 1); // �������ڽ� ������Ʈ
		return;
	}
	return;
}

void sum(int start, int end, int idx) { //segTree�� ������ �迭�� �����ֱ�.
	if (idx > segTree.size() - 1) return; //�����Ѿ�� ����
	int mid = (start + end) / 2;
	if (segTree[idx] != 0) { // ���� �����Ѵٸ� �ش��尡 ����Ű�� �迭�� ������ �� ����
		for (int i = start; i <= end; i++) {
			arr[i] += segTree[idx];
		}
	}
	// ���� ������ϸ� �ڽĳ��� �̵�
	sum(start, mid, idx * 2); //���� �ڽ�
	sum(mid + 1, end, idx * 2 + 1); // ������ �ڽ�

}

void F() {
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] > max1.second) {
			max1.first = i;
			max1.second = arr[i];
		}
		if (arr[i] < min1.second) {
			min1.first = i;
			min1.second = arr[i];
		}
	}
	return;
}

int main() {

	in >> n;
	arr.resize(n);
	int h = ceil(log2(n));
	int tree_size = 1 << (h + 1);
	segTree.resize(tree_size);


	while (1) {
		int a, b, c; in >> a >> b >> c;
		if (a == -1)break;
		update(a, b, c, 0, (n - 1), 1); // a���� b���� c�� ���ϰ� tree������ 0~size-1����, ����idx�� 1
	}

	sum(0, n - 1, 1);
	F();
	out << min1.second << " " << min1.first << " " << max1.second << " " << max1.first;
	return 0;
}