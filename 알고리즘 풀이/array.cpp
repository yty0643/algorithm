//<c k v> :  ��, �迭�� Ư�� ��ġ�� ���� ������ ������ �ٲ۴�.�� ���� �Ŀ��� �迭 �� ����� ���� ���� �ٸ��ٴ� ���� ����ȴ�.
//<w k> : �迭 a�� ����� �� �߿��� k >=1��° ���� ���� ����� ���� ��ġ�� ã�� �� �ε����� ����Ѵ�.
//<a v> : �迭 a�� ����� �� �߿���  v���� ���� ���� �� ������ ã��, �� ������ ����Ѵ�.
//<f v> : �� v�� ����� ���� ��ġ�� ã�� �� �ε����� ����Ѵ�.�� ��, �� �迭�� �ݵ�� �ִ� ������ ����ȴ�.
//�迭ũ�� 10~10��, ����Ƚ�� 10~50�� �� ũ�� -10 9�� +10 �� 9�� -1��~1��

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define MAX 1000000007
using namespace std;

ifstream in("array.inp");
ofstream out("array.out");

typedef struct node {
	int idx; // �迭�ε���
	int val; // ��
	int LCN; // �����ڽ� ����
	int RCN; // �������ڽ� ����
	int rank; // ��ŷ 
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
	if (root->val > tree[idx].val) { //����
		root->LCN++;
		if (root->LC == NULL) { //�������
			root->LC = &tree[idx];
			tree[idx].P = root;
		}
		else { //�ڽ�����
			tree_connect(root->LC, idx);
		}
	}
	else if (root->val < tree[idx].val) { //����
		root->RCN++;
		if (root->RC == NULL) { //�������
			root->RC = &tree[idx];
			tree[idx].P = root;
		}
		else { //�ڽ�����
			tree_connect(root->RC, idx);
		}
	}
}

node* find_posi(node* root) {//�������ֿ���
	if (root->LC == NULL)
		return root;
	else
		root->LCN--;
	find_posi(root->LC);
}

void del(node* root, int idx, int val) {  // �����ֿ���
	node* a = root;

	if (root->RC != NULL) { //����o
		if (root->RC->LC != NULL) { //����o ����o
			root->RCN--;
			a = find_posi(root->RC); //����-�ֿ���
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

			if (temp.RC != NULL) { //a �ܸ�x
				temp.P->LC = temp.RC;
				temp.RC->P = temp.P;
			}
			else {
				temp.P->LC = NULL;
			}
		}
		else { //����o ����x
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
			//if (temp.RC != NULL) { //a �ܸ�x
			//	temp.P->RC = temp.RC;
			//	temp.RC->P = temp.P;
			//}
		}
		if (root->P != NULL) {//�θ�o
			if (root->P->LC == root)
				root->P->LC = a;
			else if (root->P->RC == root)
				root->P->RC = a;
		}
	}
	else { //����x �������ڽ��� ���»��¿��� �����ڽ��� �ְ����� �ܸ����ox��
		if (root->LC != NULL) { //����x ����o
			root->LCN--;
			a = root->LC;
			root->LC->P = root->P;
			if (root->P != NULL) {//�θ�o
				if (root->P->LC == root)
					root->P->LC = root->LC;
				else if (root->P->RC == root)
					root->P->RC = root->LC;
			}
		}
		else {//����x ����x
			//��� �� ���� ������ �θ��ִ�
			if (root->P != NULL) {//�θ�o
				if (root->P->LC == root)
					root->P->LC = root->LC;
				else if (root->P->RC == root)
					root->P->RC = root->LC;
			}
		}
	}
	if (root->idx == root_idx)
		root_idx = a->idx;
	tree[idx] = make_node(val, idx); //��� ����� ���ο�val������
	tree_connect(&tree[root_idx], idx); //��� �翬��
}

void op_c(node* root, int idx, int val) { // tree[idx] = val; //idx ���� -> idx val ���� -> idx ����

	if (root->val > tree[idx].val) { //���� Ž��
		root->LCN--; // ���ʿ� �ִ� �ڽ��� �������� ����ϱ⶧���� �ڱ��ڽ��� �ڽİ������� ������
		op_c(root->LC, idx, val);
	}
	else if (root->val < tree[idx].val) { //���� Ž��
		root->RCN--;// �����ʿ� �ִ� �ڽ��� �������� ����ϱ⶧���� �ڱ��ڽ��� �ڽİ������� ������
		op_c(root->RC, idx, val);
	}
	else { //ã�� -> �������� 

		del(root, idx, val);
		return;
	}

}

int op_w(node* root, int rank) { //rank��° �������� idx���
	if (root->P == NULL) { //�θ� ����
		root->rank = root->LCN + 1;
	}
	else {//�θ� �ִٸ� ���� ���� �����ڽ�or�������ڽĿ� ���� �ٸ�
		if (root->P->LC == root) { //���� �ڽ��̴�.
			root->rank = root->P->rank - (root->RCN + 1);
		}
		else if (root->P->RC == root) { //������ �ڽ��̴�.
			root->rank = root->P->rank + root->LCN + 1;
		}
	}

	if (root->rank > rank) { // ��Ʈ���� �� ���� ����
		op_w(root->LC, rank);
	}
	else if (root->rank < rank) { // ��Ʈ���� ū ����
		op_w(root->RC, rank);
	}
	else { // ã��
		return root->idx;
	}
}

int op_a(node* root, int val) { // val���� �������� ���� �ڽ��� ���±������� ã�Ƴ���������

	if (root->P == NULL) { //�θ� ����
		root->rank = root->LCN + 1;
	}
	else {//�θ� �ִٸ� ���� ���� �����ڽ�or�������ڽĿ� ���� �ٸ�
		if (root->P->LC == root) { //���� �ڽ��̴�.
			root->rank = root->P->rank - (root->RCN + 1);
		}
		else if (root->P->RC == root) { //������ �ڽ��̴�.
			root->rank = root->P->rank + root->LCN + 1;
		}
	}

	if (root->val > val) { //���� Ž��
		if (root->LC == NULL) { //�����ڽ��� ����
			return root->rank - 1;
		}
		else {
			op_a(root->LC, val);
		}
	}
	else if (root->val < val) { //������ Ž��
		if (root->RC == NULL) { //������ �ڽ��� ����.
			return root->rank ;
		}
		else {
			op_a(root->RC, val);
		}
	}
	else { //�������
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
	for (int i = 0; i < n; i++) { // �迭����
		int val; in >> val;
		v.push_back(val);
		tree[i] = make_node(val, i);
	}

	for (int i = 1; i < n; i++) { // Ʈ������ (tree[0]�� ��Ʈ���)
		tree_connect(&tree[root_idx], i);
	}

	for (int i = 0; i < m; i++) { // ��ɽ���
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