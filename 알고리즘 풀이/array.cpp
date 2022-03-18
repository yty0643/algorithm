//<c k v> :  즉, 배열의 특정 위치의 값을 지정한 것으로 바꾼다.이 연산 후에도 배열 에 저장된 값은 서로 다르다는 것이 보장된다.
//<w k> : 배열 a에 저장된 것 중에서 k >=1번째 작은 값이 저장된 곳의 위치를 찾아 그 인덱스를 출력한다.
//<a v> : 배열 a에 저장된 것 중에서  v보다 작은 값이 몇 개인지 찾아, 그 개수를 출력한다.
//<f v> : 값 v가 저장된 곳의 위치를 찾아 그 인덱스를 출력한다.이 때, 는 배열에 반드시 있는 수임이 보장된다.
//배열크기 10~10만, 연산횟수 10~50만 값 크기 -10 9승 +10 의 9승 -1억~1억

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAX 1000000007
using namespace std;

ifstream in("array.inp");
ofstream out("array.out");

typedef struct node {
	int idx; // 배열인덱스
	int val; // 값
	int LCN; // 왼쪽자식 개수
	int RCN; // 오른쪽자식 개수
	int rank; // 랭킹 
	node* LC, * RC, * P;
}node;
long long ret;
int n, m, root_idx;
vector<node> tree;

node make_node(int val, int idx) { //insert
	node newnode;
	newnode.val = val;
	newnode.idx = idx;
	newnode.LCN = 0;
	newnode.RCN = 0;
	newnode.rank = 0;
	newnode.LC = NULL;
	newnode.RC = NULL;
	newnode.P = NULL;
	return newnode;
}

void tree_connect(node* root, int idx) {
	if (root->val > tree[idx].val) { //왼자
		root->LCN++;
		if (root->LC == NULL) { //비어있음
			root->LC = &tree[idx];
			tree[idx].P = root;
		}
		else { //자식있음
			tree_connect(root->LC, idx);
		}
	}
	else if (root->val < tree[idx].val) { //오자
		root->RCN++;
		if (root->RC == NULL) { //비어있음
			root->RC = &tree[idx];
			tree[idx].P = root;
		}
		else { //자식있음
			tree_connect(root->RC, idx);
		}
	}
}

node* find_posi(node* root) {//오른쪽최왼자
	if (root->LC == NULL)
		return root;
	else
		root->LCN--;
	find_posi(root->LC);
}

void del(node* root, int idx, int val) {  // 오자최왼자
	node* a = root;

	if (root->RC != NULL) { //오자o
		if (root->RC->LC != NULL) { //오자o 왼자o
			root->RCN--;
			a = find_posi(root->RC); //오자-최왼자
			node temp = *a;
			a->LCN = root->LCN;
			a->RCN = root->RCN;
			a->LC = root->LC;
			a->RC = root->RC;
			a->P = root->P;
			if (a->LC != NULL)
				a->LC->P = a;
			if (a->RC != NULL)
				a->RC->P = a;

			if (temp.RC != NULL) { //a 단말x
				temp.P->LC = temp.RC;
				temp.RC->P = temp.P;
			}
			else {
				temp.P->LC = NULL;
			}
		}
		else { //오자o 왼자x
			root->RCN--;
			a = root->RC;
			//node temp = *a;
			a->LCN = root->LCN;
			a->RCN = root->RCN;
			a->LC = root->LC;
			a->P = root->P;
			if (a->LC != NULL)
				a->LC->P = a;
			if (a->RC != NULL)
				a->RC->P = a;
			//a->RC = root;
			//if (temp.RC != NULL) { //a 단말x
			//	temp.P->RC = temp.RC;
			//	temp.RC->P = temp.P;
			//}
		}
		if (root->P != NULL) {//부모o
			if (root->P->LC == root)
				root->P->LC = a;
			else if (root->P->RC == root)
				root->P->RC = a;
		}
	}
	else { //오자x 오른쪽자식이 없는상태에서 왼쪽자식이 있고없고는 단말노드ox임
		if (root->LC != NULL) { //오자x 왼자o
			root->LCN--;
			a = root->LC;
			root->LC->P = root->P;
			if (root->P != NULL) {//부모o
				if (root->P->LC == root)
					root->P->LC = root->LC;
				else if (root->P->RC == root)
					root->P->RC = root->LC;
			}
		}
		else {//오자x 왼자x
			//사실 이 경우는 무조건 부모가있다
			if (root->P != NULL) {//부모o
				if (root->P->LC == root)
					root->P->LC = root->LC;
				else if (root->P->RC == root)
					root->P->RC = root->LC;
			}
		}
	}
	if (root->idx == root_idx)
		root_idx = a->idx;
	tree[idx] = make_node(val, idx); //노드 재생성 새로운val값으로
	tree_connect(&tree[root_idx], idx); //노드 재연결
}

void op_c(node* root, int idx, int val) { // tree[idx] = val; //idx 삭제 -> idx val 변경 -> idx 삽입

	if (root->val > tree[idx].val) { //왼자 탐색
		root->LCN--; // 왼쪽에 있는 자식이 내역할을 대신하기때문에 자기자신은 자식개수에서 빼야함
		op_c(root->LC, idx, val);
	}
	else if (root->val < tree[idx].val) { //오자 탐색
		root->RCN--;// 오른쪽에 있는 자식이 내역할을 대신하기때문에 자기자신은 자식개수에서 빼야함
		op_c(root->RC, idx, val);
	}
	else { //찾음 -> 삭제수행 

		del(root, idx, val);
		return;
	}

}

int op_w(node* root, int rank) { //rank번째 작은값의 idx출력
	if (root->P == NULL) { //부모가 없다
		root->rank = root->LCN + 1;
	}
	else {//부모가 있다면 순위 수정 왼쪽자식or오른쪽자식에 따라 다름
		if (root->P->LC == root) { //왼쪽 자식이다.
			root->rank = root->P->rank - (root->RCN + 1);
		}
		else if (root->P->RC == root) { //오른쪽 자식이다.
			root->rank = root->P->rank + root->LCN + 1;
		}
	}

	if (root->rank > rank) { // 루트보다 더 작은 순위
		op_w(root->LC, rank);
	}
	else if (root->rank < rank) { // 루트보다 큰 순위
		op_w(root->RC, rank);
	}
	else { // 찾음
		return root->idx;
	}
}

int op_a(node* root, int val) { // val보다 작은값의 개수 자식이 없는구간까지 찾아내려가야함

	if (root->P == NULL) { //부모가 없다
		root->rank = root->LCN + 1;
	}
	else {//부모가 있다면 순위 수정 왼쪽자식or오른쪽자식에 따라 다름
		if (root->P->LC == root) { //왼쪽 자식이다.
			root->rank = root->P->rank - (root->RCN + 1);
		}
		else if (root->P->RC == root) { //오른쪽 자식이다.
			root->rank = root->P->rank + root->LCN + 1;
		}
	}

	if (root->val > val) { //왼쪽 탐색
		if (root->LC == NULL) { //왼쪽자식이 없다
			return root->rank - 1;
		}
		else {
			op_a(root->LC, val);
		}
	}
	else if (root->val < val) { //오른쪽 탐색
		if (root->RC == NULL) { //오른쪽 자식이 없다.
			return root->rank ;
		}
		else {
			op_a(root->RC, val);
		}
	}
	else { //같은경우
		return root->rank - 1;
	}
}

int op_f(node* root, int val) {
	if (root->val > val) {
		op_f(root->LC, val);
	}
	else if (root->val < val) {
		op_f(root->RC, val);
	}
	else {
		return root->idx;
	}
}

int main() {
	in >> n >> m;
	tree.resize(n);
	vector<int> v;
	for (int i = 0; i < n; i++) { // 배열생성
		int val; in >> val;
		v.push_back(val);
		tree[i] = make_node(val, i);
	}

	for (int i = 1; i < n; i++) { // 트리연결 (tree[0]이 루트노드)
		tree_connect(&tree[root_idx], i);
	}

	for (int i = 0; i < m; i++) { // 명령실행
		char op; in >> op;
		int val;
		switch (op) {
		case 'c':
			int val2;
			in >> val >> val2;
			op_c(&tree[root_idx], val, val2);
			break;
		case 'w':
			in >> val;
			ret += op_w(&tree[root_idx], val);
			break;
		case 'a':
			in >> val;
			ret += op_a(&tree[root_idx], val);
			break;
		case 'f':
			in >> val;
			ret += op_f(&tree[root_idx], val);
			break;
		}
	}

	out << ret % MAX;
		
	return 0;
}