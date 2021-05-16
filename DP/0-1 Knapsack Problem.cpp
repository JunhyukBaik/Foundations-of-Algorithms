/*
* [2018117635] [백준혁] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define MAX 257
using namespace std;
int w[MAX];
int p[MAX];
int lv, rv;
int knapsack3(int n, int W, int w[], int p[], map<pair<int, int>, int>& P)
{
	if (n == 0 || W <= 0)
		return 0;

	int lvalue = (P.find(make_pair(n - 1, W)) != P.end()) ? P[make_pair(n - 1, W)] : knapsack3(n - 1, W, w, p, P);
	int rvalue = (P.find(make_pair(n - 1, W - w[n])) != P.end()) ? P[make_pair(n - 1, W - w[n])] : knapsack3(n - 1, W - w[n], w, p, P);
	P[make_pair(n, W)] = (w[n] > W) ? lvalue : max(lvalue, p[n] + rvalue);

	lv = P[make_pair(n - 1, W)];
	rv = P[make_pair(n - 1, W - w[n])];
	return P[make_pair(n, W)];
}

int main()
{
	int n, T;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
	}
	cin >> T;
	for (int i = 0; i < T; i++) {
		map<pair<int, int>, int> P;
		int W;
		cin >> W;
		cout << knapsack3(n, W, w, p, P) << ' ' << lv << ' ' << rv << endl; //<< ' ' << P[make_pair(n - 1, W)] << ' ' << P[make_pair(n - 1, W - w[n])] << endl;
	}
}