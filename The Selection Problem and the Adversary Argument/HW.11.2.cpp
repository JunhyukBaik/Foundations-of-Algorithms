/*
* [2018117635] [������] ���� �� �ҽ� �ڵ带 �ٸ� �ҽ� �ڵ带 �������� �ʰ� ���� �ۼ��Ͽ����ϴ�.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> S;
int cnt = 0;
void partition(int low, int high, int& pivotpoint)
{
	cnt++;
	int i, j, pivotitem;

	pivotitem = S[low];
	j = low;
	for (i = low + 1; i <= high; i++) {
		if (S[i] < pivotitem) {
			j++;
			swap(S[i], S[j]);
		}
	}
	pivotpoint = j;
	swap(S[low], S[pivotpoint]);
}

int selection(int low, int high, int k)
{
	int pivotpoint;

	if (low == high)
		return S[low];

	else {
		partition(low, high, pivotpoint);
		if (k == pivotpoint)
			return S[pivotpoint];
		else if (k < pivotpoint)
			return selection(low, pivotpoint - 1, k);
		else
			return selection(pivotpoint + 1, high, k);
	}
}

int main()
{
	int n;
	cin >> n;
	S.resize(n);
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		S[i] = t;
	}
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		cnt = 0;
		vector<int> T = S;
		int k;
		cin >> k;
		int rst = selection(0, n - 1, k - 1);
		cout << rst << ' ' << cnt << endl;
		S = T;
		T.clear();
	}

	return 0;
}