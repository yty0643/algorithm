#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#define MAX 10000

using namespace std;

ifstream in("rectangles.inp");
ofstream out("rectangles.out");

int n, max_y, min_y = 30000, ret;

struct rt {
	int x;
	int y_row;
	int y_high;
	int state;
};
struct Tree {
	int sum;
	int cnt;
};

vector<rt> arr;
Tree tree[800000];

void prob(int row, int high, int state, int start, int end, int node) {
	if (row > end || start > high)return;
	if (row <= start && high >= end) {
		if (state == 1) tree[node].cnt++;
		else tree[node].cnt--;
	}
	else {
		int mid = (start + end) / 2;
		prob(row, high, state, start, mid, node * 2);
		prob(row, high, state, mid+1, end, node * 2+1);
	}
	if (tree[node].cnt > 0) {
		tree[node].sum = end - start + 1;
	}
	else {
		tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
	}
}

bool asc(rt a, rt b) {
	if (a.x < b.x)
		return true;
	return false;
}

int main() {


	in >> n;

	for (int i = 0; i < n; i++) {

		int a, b, c, d;
		in >> a >> b >> c >> d;
		arr.push_back({ a + MAX, b + MAX, d + MAX - 1,1 });
		arr.push_back({ c + MAX, b + MAX, d + MAX - 1,2 });

		min_y = min(min_y, b + MAX);
		max_y = max(max_y, d + MAX);
	}

	sort(arr.begin(), arr.end(), asc);

	for (int i = 0; i < arr.size(); i++) {
		if (i) {
			int xx = arr[i].x - arr[i - 1].x;
			ret += xx * tree[1].sum;
		}
		prob(arr[i].y_row, arr[i].y_high, arr[i].state, min_y, max_y, 1);
	}

	out << ret << "\n";

	return 0;
}