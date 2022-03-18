#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

ifstream in("rmq.inp");
ofstream out("rmq.out");

int n, leaf;
long long ret;

int arr[1000001];
int tree[4000000];

int main() {
	in >> n;
	arr[1000000] = 10000000;

	for (int i = 0; i < n; i++) { //input value
		int val; in >> val;
		arr[i] = val;
	}

	for (leaf = 1; leaf < n; leaf *= 2); // leaf node[0]'s idx
	for (int i = 0; i < n; i++) tree[leaf + i] = i; // leaf node
	for (int i = leaf - 1; i > 0; i--) tree[i] = arr[tree[i * 2]] <= arr[tree[i * 2 + 1]] ? tree[i * 2] : tree[i * 2 + 1]; // internal node

	while (1) {
		char op; in >> op;

		if (op == 'q') { //minimum idx in range(l~r)
			int l, r; in >> l >> r;
			l += leaf;
			r += leaf;
			int val = 1000000;

			while (l <= r) {
				if (l % 2) {
					if (arr[tree[l]] < arr[val])
						val = tree[l];
					else if (arr[tree[l]] == arr[val])
						val = min(tree[l], val);
					l++;
				}
				if (r % 2 == 0) {
					if (arr[tree[r]] < arr[val])
						val = tree[r];
					else if (arr[tree[r]] == arr[val])
						val = min(tree[r], val);
					r--;
				}
				l /= 2;
				r /= 2;
			}
			ret += val;
		}
		else if (op == 'c') { //update arr[idx] = val
			int idx, val; in >> idx >> val;
			arr[idx] = val;
			idx += leaf;
			for (idx /= 2; idx; idx /= 2) tree[idx] = arr[tree[idx * 2]] <= arr[tree[idx * 2 + 1]] ? tree[idx * 2] : tree[idx * 2 + 1];
		}
		else break;
	}

	ret %= 100000;
	out << ret;
	return 0;
}