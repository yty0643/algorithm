#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <string>

using namespace std;

//ifstream in("dp.inp");
typedef long long int ll ;
ll n, k;
string num2[15];
ll num[15];
ll numPosi2[15];
ll numPosi[50];
ll dp[1 << 15][100];

ll gcd(ll a, ll b) {

	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}

int main() {
	cin >> n;
	for (ll i = 0; i < n; i++) {
		cin >> num2[i];
		numPosi2[i] = num2[i].length();
	}
	cin >> k;

	for (ll i = 0; i < n; i++) {
		ll temp = 0;
		for (ll j = 0; j < num2[i].length(); j++) {
			temp = temp * 10 + (num2[i][j] - '0');
			if (temp >= k) temp %= k;
		}
		num[i] = temp;
	}

	numPosi[0] = 1 % k;
	for (ll i = 1; i <= 50; i++) {
		numPosi[i] = (numPosi[i - 1] * 10) % k;
	}

	dp[0][0] = 1;
	for (ll i = 0; i < (1 << n); i++) {
		for (ll j = 0; j < k; j++) {
			if (!dp[i][j]) continue;
			for (ll x = 0; x < n; ++x) {
				if (!(i & (1 << x))) {
					dp[i | (1 << x)][(j * numPosi[numPosi2[x]] + num[x]) % k] += dp[i][j];
				}
			}
		}
	}
	if (dp[(1 << n) - 1][0] == 0) {
		cout << "0/1";
	}
	else {
		ll cnt = 1;
		for (ll i = 1; i <= n; i++) {
			cnt *= i;
		}
		ll gc = gcd(dp[(1 << n) - 1][0], cnt);
		cout << dp[(1 << n) - 1][0] / gc << "/" << cnt / gc;
	}
	return 0;
}