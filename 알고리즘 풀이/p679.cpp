#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include<memory.h>
using namespace std;

ifstream in("p679.inp");
ofstream out("p679.out");
int ret , n;

bool v[1100000]; // false;


int main() {
	
		
		in >> n;
		while (n--) {

			ret = 0;

			memset(v, false, sizeof(v)); // -1

				int depth, drop; in >> depth >> drop;
				int reaf_range1 = (1 << (depth - 1));
			
				for (int i = 0; i < drop; i++) {

					int start = 1;

					while (reaf_range1 > start) {
						if (v[start] == false) {
							v[start] = true;
							start *= 2;
						}
						else {
							v[start] = false;
							start = start * 2 + 1;
						}
						ret = start;
					}
				}
				out << ret << "\n";
		}
		in >> n;
	return 0;
}