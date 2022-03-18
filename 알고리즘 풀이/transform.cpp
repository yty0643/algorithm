#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

ifstream in("transform.inp");
ofstream out("transform.out");

int t, n, m;

int main() {
    in >> t;
    while (t--) {
        in >> n >> m;
        out << n << " ";
        int ret = 0;
        if (m) { //괄호입력
            stack<int> s;
            for (int i = 0; i < n*2; i++) {
                char val; in >> val;
                if (val == '(') {
                    ret++;
                    s.push(ret);
                }
                else {
                    int tmep = s.top();
                    s.pop();
                    out << tmep << " ";
                }
            }
        }
        else { //숫자입력
            for (int i = 0; i < n; i++) {
                int val; in >> val;
                if (val > ret) {
                    for (int i = ret; i < val; i++) out << "(";
                    out << ")";
                    ret = val;
                }
                else out << ")";
            }
        }
        out << "\n";
    }
    return 0;
}