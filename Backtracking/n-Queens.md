### Description
```
Algorithm 5.1 (n-Queens) 를 참조하여
주어진 n에 대하여 가능한 모든 경우의 수를 탐색하는 알고리즘을 구현하시오.
이때, n-Queens 문제의 모든 솔루션을 정수로 변환하여 리스트에 저장해야 한다.
정수로 변환하는 규칙은 col 배열의 인덱스 값을 그대로 십진수로 변환하도록 한다.
예를 들어, n=4인 경우에는 두 가지 경우의 솔루션이 있고,
이때 col 배열의 인덱스 값은 각각 [2, 4, 1, 3], [3, 1, 4 2] 이므로,
솔루션의 리스트는 [2413, 3142]가 된다.
```

### Input
```
첫째 줄에 n-Queens 문제의 n이 주어진다. (1 <= n <= 9)
둘째 줄에 테스트 케이스의 수 T가 주어진다.
셋째 줄부터 T개의 임의의 정수 m이 주어진다.
```

### Output
```
각 테스트 케이스별로 한 줄에 하나씩 주어진 m이 솔루션 리스트에 포함되는 지를 출력한다.
즉, m이 솔루션 집합에 포함되면 YES를, 포함되지 않으면 NO를 출력한다.
(YES와 NO는 반드시 대문자로 출력한다.)
```
### Sample Input 1 
```
4
5
1234
2413
3124
3142
4132
```
### Sample Output 1
```
NO
YES
NO
YES
NO
```
### Code
```
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
```
