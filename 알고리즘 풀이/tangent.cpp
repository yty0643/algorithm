#include<iostream>
#include<fstream>
#include<stack>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

ifstream in("tangent.inp");
ofstream out("tangent.out");

typedef struct point {
   long long int x;
   long long int y;
   int AB; // A:1 B:2
   int idx;
} point;


vector<point> v2; //B
vector<point> v1; //A
vector<point> v; //A+B 
vector<point> convexAB; // convex(A+B)
vector<point> lineCoor; // lineCoor
vector<point> retv; // 최종 다각형

void init() {
   v1.clear(); //A
   v2.clear(); //B
   v.clear(); //A+B 
   convexAB.clear(); // convex(A+B)
   lineCoor.clear(); // lineCoor
   retv.clear();
}

long double ccw(point a, point b, point c) {
   return a.x * b.y + b.x * c.y + c.x * a.y - (a.y * b.x + b.y * c.x + c.y * a.x);
}

bool cmp1(point a, point b) {
   if (a.x < b.x)
      return true;
   else if (a.x == b.x)
      if (a.y < b.y)
         return true;
   return false;
}

bool cmp2(point a, point b) {
   if (ccw(v[0], a, b) > 0)return true;
   else if (ccw(v[0], a, b) == 0)
      if (a.x + a.y < b.x + b.y)return true;
   return false;
}

void F_convex() {
   stack<point> s;
   s.push(v[0]);
   s.push(v[1]);

   point a, b;

   for (int i = 2; i < v.size(); i++) {
      while (s.size() >= 2) {
         b = s.top();
         s.pop();
         a = s.top();

         if (ccw(a, b, v[i]) > 0) {
            s.push(b);
            break;
         }
      }
      s.push(v[i]);

   }
   while (!s.empty()) {
      convexAB.push_back(s.top());
      s.pop();
   }
}
long long distance(point a, point b) {
   return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void F_line2() {
   if (lineCoor[0].AB == 1) { //A시작
      for (int i = 0; i < v2.size(); i++) {// idx 0과 가까운 1찾기 
         if (ccw(lineCoor[0], lineCoor[1], v2[i]) == 0) // 기존의 0 -> 1과 일직선인 좌표로 후보선정
            if (distance(lineCoor[0], lineCoor[1]) > distance(lineCoor[0], v2[i]))
               lineCoor[1] = v2[i];
      }
      for (int i = 0; i < v2.size(); i++) {// idx 3과 가까운 2찾기
         if (ccw(lineCoor[3], lineCoor[2], v2[i]) == 0) // 기존의 1->0과 일직선인 좌표로 후보선정
            if (distance(lineCoor[3], lineCoor[2]) > distance(lineCoor[3], v2[i]))
               lineCoor[2] = v2[i];
      }
      //A에서 B찾기

      for (int i = 0; i < v1.size(); i++) {// idx 1과 가까운 0찾기
         if (ccw(lineCoor[1], lineCoor[0], v1[i]) == 0) // 기존의 1->0과 일직선인 좌표로 후보선정
            if (distance(lineCoor[1], lineCoor[0]) > distance(lineCoor[1], v1[i]))
               lineCoor[0] = v1[i];
      }
      for (int i = 0; i < v1.size(); i++) {// idx 2과 가까운 3찾기 
         if (ccw(lineCoor[2], lineCoor[3], v1[i]) == 0) // 기존의 2 -> 3과 일직선인 좌표로 후보선정
            if (distance(lineCoor[2], lineCoor[3]) > distance(lineCoor[2], v1[i]))
               lineCoor[3] = v1[i];
      }
      //B에서 A찾기

   }
   else { //B시작
      for (int i = 0; i < v1.size(); i++) {// idx 0과 가까운 1찾기 
         if (ccw(lineCoor[0], lineCoor[1], v1[i]) == 0) // 기존의 0 -> 1과 일직선인 좌표로 후보선정
            if (distance(lineCoor[0], lineCoor[1]) > distance(lineCoor[0], v1[i]))
               lineCoor[1] = v1[i];
      }
      for (int i = 0; i < v1.size(); i++) {// idx 3과 가까운 2찾기
         if (ccw(lineCoor[3], lineCoor[2], v1[i]) == 0) // 기존의 1->0과 일직선인 좌표로 후보선정
            if (distance(lineCoor[3], lineCoor[2]) > distance(lineCoor[3], v1[i]))
               lineCoor[2] = v1[i];
      }
      //B에서 A찾기

      for (int i = 0; i < v2.size(); i++) {// idx 1과 가까운 0찾기
         if (ccw(lineCoor[1], lineCoor[0], v2[i]) == 0) // 기존의 1->0과 일직선인 좌표로 후보선정
            if (distance(lineCoor[1], lineCoor[0]) > distance(lineCoor[1], v2[i]))
               lineCoor[0] = v2[i];
      }
      for (int i = 0; i < v2.size(); i++) {// idx 2과 가까운 3찾기 
         if (ccw(lineCoor[2], lineCoor[3], v2[i]) == 0) // 기존의 2 -> 3과 일직선인 좌표로 후보선정
            if (distance(lineCoor[2], lineCoor[3]) > distance(lineCoor[2], v2[i]))
               lineCoor[3] = v2[i];
      }
      //A에서 B찾기
   }

}



void F_line() {
   int n = convexAB.size();
   for (int i = 0; i < n; i++) {
      if (convexAB[i].AB != convexAB[(i + 1) % n].AB) {
         lineCoor.push_back(convexAB[i]);
         lineCoor.push_back(convexAB[(i + 1) % n]);
      }
   }
}



void F_coordinates2(int start, int end, int AB) {// lineCoor 1, 2 idx가 같은좌표일때 (v2에서 idx도 같음 한 좌표를 두번씀)
   if (AB == 1) { //A다각형 안의 좌표
      int n = v1.size();
      if (start == end) {
         retv.push_back(v1[start]);
         start--;
      }
      while (start != end) {
         retv.push_back(v1[start]);
         start--;
         if (start < 0) start = n - 1;
      }
      retv.push_back(v1[end]);
   }
   else // B다각형
   {

      int n = v2.size();
      if (start == end) {
         retv.push_back(v2[start]);
         start--;
      }
      while (start != end) {
         retv.push_back(v2[start]);
         start--;
         if (start < 0)start = n - 1;
      }
      retv.push_back(v2[end]);
   }
}

void F_coordinates() {
   F_coordinates2(lineCoor[1].idx, lineCoor[2].idx, lineCoor[1].AB);
   F_coordinates2(lineCoor[3].idx, lineCoor[0].idx, lineCoor[3].AB);

}

long double area() {
   long long ret = 0;
   int n = retv.size();

   for (int i = 0; i < n; i++) {
      int j = (i + 1) % n;
      ret = ret + (retv[i].x * retv[j].y - retv[i].y * retv[j].x);
   }
   return abs(ret) / 2.0;
}

int main() {
   cout << fixed;
   cout.precision(1);

   int n; in >> n;

   while (n--) {
      init();
      int m; in >> m;

      for (int i = 0; i < m; i++) { // polygonA
         long long int x, y; in >> x >> y;
         v1.push_back({ x, y, 1, i });
         v.push_back({ x, y, 1, i });
      }
      in >> m;
      for (int i = 0; i < m; i++) { // polygonB
         long long int x, y; in >> x >> y;
         v2.push_back({ x, y, 2, i });
         v.push_back({ x, y, 2, i });
      }

      //v.insert(v.end(), v1.begin(), v1.end());
      //v.insert(v.end(), v2.begin(), v2.end());

      sort(v.begin(), v.end(), cmp1);
      sort(v.begin() + 1, v.end(), cmp2);

      F_convex();
      reverse(convexAB.begin(), convexAB.end());
      F_line();
      F_line2();
      F_coordinates();

      long double ret = area();
      out << fixed;
      out.precision(1);
      out << ret << "\n";
   }
   return 0;
}