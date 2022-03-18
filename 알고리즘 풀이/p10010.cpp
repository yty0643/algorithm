#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)

using namespace std;

ifstream in("p10010.inp");
ofstream out("p10010.out");

vector<string> arr;
vector<string> v;
int total;
int n, m;
int z;
bool isFound;


void prob(int x, int y, int z, string data, int index) { // 보드x,y좌표 ,z방향, 찾는 단어, 단어의 인덱스
	if (isFound) return;
	if (x < 0 || y < 0 || x >= n || y >=m ) return;

	if (arr[x][y] != data.at(index)) return;


	if (index == data.size() - 1) {
		isFound = true;
		return;
	}

	switch (z)// 8가지 방향
	{
	case 1:
		prob(x, y + 1, 1, data, index + 1);
		break;
	case 2:
		prob(x + 1, y + 1, 2, data, index + 1);
		break;
	case 3:
		prob(x + 1, y, 3, data, index + 1);
		break;
	case 4:
		prob(x + 1, y - 1, 4, data, index + 1);
		break;
	case 5:
		prob(x, y - 1, 5, data, index + 1);
		break;
	case 6:
		prob(x - 1, y - 1, 6, data, index + 1);
		break;
	case 7:
		prob(x - 1, y, 7, data, index + 1);
		break;
	case 8:
		prob(x - 1, y + 1, 8, data, index + 1);
		break;
	default:
		break;

	}
}


int main() {
	in >> total;
	while (total--) {
		v.clear();
		arr.clear();



		in >> n >> m;
		for (int i = 0; i < n; i++) { // 보드 입력

			string board; in >> board;
			arr.push_back(board);
		}

		for (int i = 0; i < arr.size(); i++) {
			for (int j = 0; j < arr[i].size(); j++) {
				if (arr[i][j] >= 'A' && arr[i][j] <= 'Z') {
					arr[i][j] = arr[i][j] - 'A' + 'a';
				}
			}
		}

		in >> z;
		for (int i = 0; i < z; i++) {
			string word;  in >> word;
			v.push_back(word);
		}


		for (int i = 0; i < v.size(); i++) {
			for (int j = 0; j < v[i].size(); j++) {
				if (v[i][j] >= 'A' && v[i][j] <= 'Z') {
					v[i][j] = v[i][j] - 'A' + 'a';
				}
			}
		}


		for (int cnt = 0; cnt < z; cnt++) {


			for (int i = 0; i < n; i++) {

				for (int j = 0; j < m; j++) {


					if (arr[i][j] == v[cnt].at(0)) {
						for (int q = 1; q <= 8; q++) { // 8가지방향에대해서찾기
							prob(i, j, q, v[cnt], 0);
							if (isFound) {
								out << i + 1 << " " << j + 1 << "\n";
								break;
							}
						}
					}

					if (isFound) break;
				}
				if (isFound) break;
			}
			isFound = false;
		}
		out << "\n";
	}
	return 0;
}