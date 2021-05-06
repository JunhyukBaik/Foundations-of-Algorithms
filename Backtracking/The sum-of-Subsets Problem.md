### Description
```
Algorithm 5.4 (Sum-of-Subsets) 를 참조하여

n, W, w가 주어졌을 때, 합이 W가 되는 w의 부분집합의 개수를 출력하는 알고리즘을 구현하시오.

이때, w는 정렬되지 않은 숫자의 리스트일 수 있음에 유의하시오.
```

### Input
```
첫 줄에 숫자의 개수 n과 합 W가 주어진다.

둘째 줄에 정렬되지 않은 n개의 숫자 리스트 w가 주어진다. (0 <= w[i] <= 1,000)
```

### Output
```
합이 W가 되는 w의 부분집합의 개수를 출력한다.
```

### Sample Input 1 
```
3 6
2 4 5
```
### Sample Output 1
```
1
```

### Sample Input 2 
```
5 21
5 6 10 11 16
```
### Sample Output 2
```
3
```

### Code
```
#include <iostream>
#include <vector>
using namespace std;
#define MAX 1002
bool inc[MAX];
int w[MAX];
int cnt = 0;

bool promissing(int i, int W, int weight, int total)
{
	return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}

void sum_of_subsets(int i, int W, int weight, int total)
{
	if (promissing(i, W, weight, total)) {
		if (weight == W)
			cnt++;
		else {
			inc[i + 1] = true;
			sum_of_subsets(i + 1, W, weight + w[i + 1], total - w[i + 1]);
			inc[i + 1] = false;
			sum_of_subsets(i + 1, W, weight, total - w[i + 1]);
		}
	}
}


int main()
{
	int n, W;
	int weight = 0;
	int total = 0;
	cin >> n >> W;
	for (int i = 1; i <= n; i++) {
		cin >> w[i];
		total += w[i];
	}
	sum_of_subsets(0, W, weight, total);
	cout << cnt << endl;

	return 0;
}
```
