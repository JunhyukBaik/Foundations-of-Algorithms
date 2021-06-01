/*
* [2018117635] [백준혁] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct item {
	int index;
	int value;
} item_type;
typedef vector<item_type> item_list;

item_type tournament(int low, int high, item_list S, item_list L[])
{
	int mid;
	item_type left, right;
	item_type winner, loser;
	if (low == high)
		return S[low];
	else {
		mid = (low + high) / 2;
		left = tournament(low, mid, S, L);
		right = tournament(mid + 1, high, S, L);
		winner = left; loser = right;
		if (winner.value < loser.value)
			swap(winner, loser);
		L[winner.index].push_back(loser);
		//cout << winner.index << ' ';
		return winner;
	}
}

void find_largest(int n, item_list S, int& large)
{
	int i;
	large = S[0].value;

	for (i = 1; i < n; i++) {
		if (S[i].value > large)
			large = S[i].value;
	}
}

int main()
{
	int n;
	cin >> n;
	item_list S(n);
	item_list L[S.size()];
	for (int i = 0; i < n; i++) {
		S[i].index = i;
		cin >> S[i].value;
	}
	item_type a = tournament(0, n - 1, S, L);
	//cout << ' ' << a.index << ' ' << a.value;
	for (int i = 0; i < L[a.index].size(); i++) {
		cout << L[a.index][i].value;
		if (i != L[a.index].size() - 1)
			cout << ' ';
	}
	printf("\n");
	int large;
	find_largest(L[a.index].size(), L[a.index], large);
	cout << large << endl;

	return 0;
}

