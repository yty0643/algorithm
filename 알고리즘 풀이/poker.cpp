#include<iostream>
#include<fstream>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

ifstream in("poker.inp");
ofstream out("poker.out");

bool cmp(pair<int, int> a, pair<int, int> b) {
   if (a.second < b.second)return true;
   else return false;
}
bool cmp2(pair<int, int> a, pair<int, int> b) {
   if (a.first < b.first)return true;
   else if (a.first == b.first)
      if (a.second < b.second)return true;
   return false;
}

int change(char val) {
   int x = -1;
   if (val - 48 > 0 && val - 48 < 10) x = val - 48;
   if (val == 'S') x = 1;
   if (val == 'D') x = 2;
   if (val == 'H') x = 3;
   if (val == 'C') x = 4;
   if (val == 'A') x = 14;
   if (val == 'T') x = 10;
   if (val == 'J') x = 11;
   if (val == 'Q') x = 12;
   if (val == 'K') x = 13;
   return x;
}

bool F_sf(vector<pair<int, int>> v, int start) {
   int cnt = 0;
   int x = 0;
   for (int i = 0; i < 4; i++) {
      if (v[start + i].first == v[start + i + 1].first) cnt++;
      if (v[start + i].second == 1)x++;
      if (v[start + i + 1].second == 14)
         if (x > 0) {
            cnt--;
            x--;
         }
   }
   if (cnt == 4)return true;
   return false;
}

bool F_s(vector<pair<int, int>> v, int start) {
   for (int i = 0; i < 4; i++) {
      if (v[start + i].second - v[start + i + 1].second != -1) return false;
   }
   return true;
}

string F_num(vector<pair<int, int>> v) {
   sort(v.begin(), v.end(), cmp); // 숫자 크기 정렬

   int pp = 0;
   int sp = 0;

   int pair = 0;
   int triple = 0;
   int straight = 0; //연속
   int flush = 0; // 같은 무늬 4
   int fullhouse = 0;
   int fourcard = 0;
   int straightFlush = 0;
   for (int i = 0; i < v.size() - 1; i++) {
      if (v[i].second - v[i + 1].second == 0) { // 같은숫자 
         if (v[i].second != 14)pp++;
      }
      else if ((v[i].second - v[i + 1].second == -1)) { // 연속된 숫자
         sp++;
         if (pp >= 1) pair++;
         if (pp == 2) triple = 1;
         if (pp == 3) fourcard = 1;
         if (sp >= 4) straight = 1;
         pp = 0;
      }
      else {//아무것도아님
         if (pp >= 1) pair++;
         if (pp == 2) triple = 1;
         if (pp == 3) fourcard = 1;
         if (sp >= 4) straight = 1;
         pp = 0;
         sp = 0;
      }
   }
   if (sp >= 4) straight = 1;
   if (pp) pair++;
   if (pp == 2) triple = 1;
   if (pp == 3) fourcard = 1;
   if (pair >= 2 && triple == 1) fullhouse = 1;

   sort(v.begin(), v.end(), cmp2); // 무늬 정렬

   for (int i = 0; i < v.size() - 4; i++) {
      if (F_sf(v, i)) {
         flush = 1;
         if (F_s(v, i)) straightFlush = 1;
      }
   }

   if (straightFlush) return "Straight Flush";
   if (fourcard) return "Four Card";
   if (fullhouse) return "Full House";
   if (flush) return "Flush";
   if (straight) return "Straight";
   if (triple) return "Triple";
   if (pair > 1) return "Two Pair";
   if (pair == 1) return "One Pair";
   return "Top";
}

int main() {
   int n; in >> n;
   char val;
   vector< vector< pair< int, int > > > v; //원본
   v.resize(n);

   for (int i = 0; i < n; i++) {
      for (int j = 0; j < 7; j++) {
         in >> val;
         int x = change(val);
         in >> val;
         int y = change(val);

         v[i].push_back({ x,y });
         if (y == 14)v[i].push_back({ x,1 });
         if (y == 1)v[i].push_back({ x,14 });
      }
      out << F_num(v[i]) << "\n";
   }
   return 0;
}