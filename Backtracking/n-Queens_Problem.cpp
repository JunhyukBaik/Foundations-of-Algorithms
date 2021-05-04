#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 10

using namespace std;
int col[MAX];
vector<int> sol;

bool promissing(int i)
{
	int k = 1;
	bool flag = true;

	while (k < i && flag) {
		if ((col[i] == col[k]) || (abs(col[i] - col[k]) == i - k))
			flag = false;
		k++;
	}
	return flag;
}

void queens(int n, int i)
{
	int j;
	int mult_ten = 1;
	int rst = 0;

	if (promissing(i)) {
		if (i == n) {
			for (int a = n; a >= 1; a--) {	
				rst += (col[a] * mult_ten);
				mult_ten *= 10;
				//cout << col[a] << ' ';
			}
			sol.push_back(rst);
		}
		else
			for (j = 1; j <= n; j++) {
				col[i + 1] = j;
				queens(n, i + 1);
			}
	}
}

int main()
{
	int n, t;
	cin >> n;
	cin >> t;
	queens(n, 0);
	//cout << sol[0] << ' ' << sol[1] << endl;
	for (int i = 0; i < t; i++) {
		int m;
		cin >> m;
		if (find(sol.begin(), sol.end(), m) != sol.end())
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}

	return 0;
}