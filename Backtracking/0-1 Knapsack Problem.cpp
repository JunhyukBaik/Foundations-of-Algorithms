/*
* [2018117635] [백준혁] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define MAX 257
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
using namespace std;
int w[MAX];
int p[MAX];
int n, W;
int maxprofit = 0;
bool include[MAX];
bool bestset[MAX];
int wt, bd;

void cal_bound(int& a, int b)
{
	a += b;
}

bool promissing(int i, int profit, int weight, int& b)
{
	int j, k, totweight;
	int bound;
	if (weight >= W)
		return false;
	else {
		j = i + 1;
		bound = profit;
		totweight = weight;
		while (j <= n && totweight + w[j] <= W) {
			totweight += w[j];
			bound += p[j];
			j++;
		}
		k = j;
		if (k <= n) {
			bound += (W - totweight) * (p[k] / w[k]);
		}
		b = bound;
		return bound > maxprofit;
	}
}

void knapsack4(int i, int profit, int weight, int& b)
{
	if (weight <= W && profit > maxprofit) {
		maxprofit = profit;
		wt = weight;
		bd = b;
		memcpy(include, bestset, sizeof(include));
	}

	if (promissing(i, profit, weight, b)) {
		include[i + 1] = true;
		knapsack4(i + 1, profit + p[i + 1], weight + w[i + 1],b);
		include[i + 1] = false;
		knapsack4(i + 1, profit, weight,b);
	}
}

void srt(int m, int w[], int p[])
{
	int max, tmp;
	for (int i = 1; i < m - 1; i++) {
		max = i;
		for (int j = i + 1; j < m; j++) {
			if (p[j] / w[j] > p[max] / w[max])
				max = j;
		}
		SWAP(w[i], w[max], tmp);
		SWAP(p[i], p[max], tmp);
	}
}

int main()
{
	int T;
	cin >> n;
	int bound;
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
	}
	
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
	}
	srt(n+1, w, p);
	//for (int i = 1; i <= n; i++)
		//cout << w[i] << ' ';
	//for (int i = 1; i <= n; i++)
		//cout << p[i] << ' ';
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> W;
		knapsack4(0, 0, 0, bound);
		cout << maxprofit << ' ' << wt << ' ' << bd << endl;
		maxprofit = 0;
	}
}