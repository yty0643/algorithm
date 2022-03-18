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

void update(int start, int end, int val, int left, int right, int idx) { //바꿀 범위s~e 트리 범위 l~r , tree node번호
	int mid = (left + right) / 2;
	if (start > right || end < left)
		return; // 범위밖일때
	else if (start <= left && end >= right) { // 바꿀 범위안에 현재범위가 있다
		segTree[idx] += val;
		return;
	}
	else { // 바꿀 범위가 현재범위 안에있다
		update(start, end, val, left, mid, idx * 2); // 왼쪽자식 업데이트
		update(start, end, val, mid + 1, right, idx * 2 + 1); // 오른쪽자식 업데이트
		return;
	}
	return;
}

void sum(int start, int end, int idx) { //segTree의 값들을 배열에 더해주기.
	if (idx > segTree.size() - 1) return; //범위넘어서면 리턴
	int mid = (start + end) / 2;
	if (segTree[idx] != 0) { // 값이 존재한다면 해당노드가 가르키는 배열의 범위의 값 수정
		for (int i = start; i <= end; i++) {
			arr[i] += segTree[idx];
		}
	}
	// 값이 존재안하면 자식노드로 이동
	sum(start, mid, idx * 2); //왼쪽 자식
	sum(mid + 1, end, idx * 2 + 1); // 오른쪽 자식

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
		update(a, b, c, 0, (n - 1), 1); // a부터 b까지 c를 더하고 tree범위는 0~size-1까지, 시작idx는 1
	}

	sum(0, n - 1, 1);
	F();
	out << min1.second << " " << min1.first << " " << max1.second << " " << max1.first;
	return 0;
}