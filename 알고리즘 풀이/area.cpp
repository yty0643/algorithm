#include<iostream>
#include<fstream>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

ifstream in("area.inp");
ofstream out("area.out");

struct circle {
   double x;
   double y;
   double r;
};

vector<circle> v;
vector<pair<double, double>> coor;
vector<pair<double, double>> retv;

int n;

void F_c(circle a, circle b) {

   //(x+1)^2 + (y+127)^2 = 362^2
   //(x+594)^2 + (y+275)^2 = 332^2
   //(x-232)2+(y+1354)^2 = 1236^2
   //근=(-b+-ㄹ(b^2-4ac))/2a
   //넓이 = 루트(s(s-a)(s-b)(s-c) 삼각abc
   //s = (a+b+c)/2

   double r = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
   double cos_ = ((a.r * a.r + r * r) - (b.r * b.r)) / (2 * a.r * r);
   double sin_ = sqrt(1 - ((((a.r * a.r + r * r) - (b.r * b.r)) / (2 * a.r * r)) * (((a.r * a.r + r * r) - (b.r * b.r)) / (2 * a.r * r))));

   double x1 = b.x - a.x;
   double y1 = b.y - a.y;

   double xa = (x1 * cos_ - y1 * sin_) * a.r / r + a.x;
   double ya = (x1 * sin_ + y1 * cos_) * a.r / r + a.y;

   double xb = (x1 * cos_ + y1 * sin_) * a.r / r + a.x;
   double yb = (-1 * x1 * sin_ + y1 * cos_) * a.r / r + a.y;

   coor.push_back({ xa , ya });
   coor.push_back({ xb , yb });

   return;
}

double ccw(pair<double, double> a, pair<double, double> b, pair<double, double >c) {
   return b.first * c.second + a.first * b.second + a.second * c.first
      - (b.first * a.second + c.first * b.second + a.first * c.second);
}

double F_a() {

   pair<double, double > one = { -3001.0 , -3001.0 };

   double sum = 0;

   for (int i = 0; i < retv.size(); i++) {
      int k = (i + 1) % retv.size();
      sum += ccw(one, retv[i], retv[k]);
   }
   return abs(sum);
}

bool cmp(pair<double, double > a, pair<double, double> b) {

   if (a.first < b.first)
      return true;
   else if (a.first == b.first)
      if (a.second < b.second)
         return true;
   return false;
}

int main() {
   ios_base::sync_with_stdio(false);
   //cin.tie(false);
   //cout.tie(false);

   out << fixed;
   out.precision(2);

   in >> n;
   while (n--) {
      coor.clear();
      retv.clear();
      v.clear();

      for (int i = 0; i < 3; i++) {
         circle a;
         in >> a.x >> a.y >> a.r;
         v.push_back(a);
      }

      for (int i = 0; i < 3; i++) {
         int j = (i + 1) % 3;
         F_c(v[i], v[j]);
      }

      for (int i = 0; i < 3; i++) {
         double x = v[i].x;
         double y = v[i].y;
         double r = v[i].r;

         for (int j = 0; j < coor.size(); j++) {
            double rr = r * r;
            double temp = ((coor[j].first - x) * (coor[j].first - x) + (coor[j].second - y) * (coor[j].second - y));

            if (rr > fabsf(temp))
               retv.push_back(coor[j]);
         }
      }

      sort(retv.begin(), retv.end(), cmp);
      if (ccw(retv[0], retv[1], retv[2]) < 0) {
         swap(retv[1], retv[2]);
      }

      double ret = fabs(ccw(retv[0], retv[1], retv[2])) / 2.0;
      out << ret << "\n";
   }

   return 0;
}