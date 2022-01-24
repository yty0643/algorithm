#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream in("p384.inp");
ofstream out("p384.out");

int n, m;

bool slumps(string word, int start, int end) {
	if (!(word[start] == 'D' || word[start] == 'E')) return false;
	if (word[start + 1] != 'F')return false;
	
	for (int i = start + 2; i <= end; i++) {
		if (word[i] != 'F') { // 3번째부터 F가 아니면 G && i==end 또는 슬럼프가 와야함.
			if (i == end && word[i] == 'G') return true;
			if (slumps(word, i, end)) return true;
			else return false;
		}
	}
	return false;
}
bool slimps(string word, int start, int end) {
	if (word[start] != 'A') return false;
	if (end - 1 == start && word[end] == 'H') return true;
	if (word[end] != 'C') return false;
	if (word[start + 1] == 'B')
		if (slimps(word, start + 2, end - 1)) return true;
	if (word[start + 1] == 'D' || word[start + 1] == 'E') {
		if (slumps(word, start + 1, end - 1)) return true;
	}
	return false;
}
bool prob(string word) {
	if (word[0] != 'A' || word[word.length() - 1] != 'G') return false; // "A ~~~ G" 

	if (word[1] == 'H') // "AHD~~G or  AHE~~G"
		if (word[2] == 'D' || word[2] == 'E')
			if (slumps(word, 2, word.length() - 1)) return true;
			else return false;

	for (int i = 0; i < word.length(); i++) {
		if (word[i] == 'C') {
			if (word[i + 1] == 'C') continue;
			if (word[i + 1] == 'D' || word[i + 1] == 'E') {//0~i까지가 스림프, i+1 ~ length()-1 까지가 스럼프 를 만족하면 됨. 
				if (slimps(word, 0, i))
					if (slumps(word, i + 1, word.length() - 1)) return true;
					else return false;
			}
		}
	}
	//스러피 테스트 총 세가지 함수를 만족해야함
	//스럼프 = D or E + (F >= 1) + 스럼프 or G
	//스림프 = "AH" or 'A' + 'B' + 스림프 + 'C' or 'A'+'스럼프'+'C'
	//스러피 = 스림프 + 스럼프
	//입력되면 결국 A로시작 D로 구분 G로 끝남.
	return false;
}

int main() {
	string word;
	in >> n;
	out << "SLURPYS OUTPUT\n";
	while (n--) {
		in >> word;
		if (prob(word)) out << "YES\n";
		else out << "NO\n";
	}
	out << "END OF OUTPUT\n";
	return 0;
}