/*
* [2018117635] [백준혁] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#define MAX 257
using namespace std;
int w[MAX];
int p[MAX];

typedef struct item* item_pointer;
typedef struct item {
	int id;
	int weight;
	int profit;
	int unit_profit;
}itemtype;

struct compare {
	bool operator()(const item_pointer& i1, const item_pointer& i2) {
		return i1->unit_profit < i2->unit_profit;
	}
};

void initalize(priority_queue<item_pointer, vector<item_pointer>, compare>& PQ, int n, int w[], int p[])
{
	for (int i = 1; i <= n; i++) {
		item_pointer item = (item_pointer)malloc(sizeof(itemtype));
		item->id = i;
		item->weight = w[i];
		item->profit = p[i];
		item->unit_profit = p[i] / w[i];
		PQ.push(item);
	}
}

void knapsack1(int n, int W, int w[], int p[])
{
	priority_queue<item_pointer, vector<item_pointer>, compare> PQ;
	initalize(PQ, n, w, p);
	int total_weight = 0;
	int total_profit = 0;
	while (!PQ.empty()){
		item_pointer i = PQ.top();
		PQ.pop();
		total_weight += i->weight;
		if (total_weight > W) {
			int diff = i->weight - (total_weight - W);
			total_weight -= i->weight; 
			total_weight += diff;
			int profit = diff * i->unit_profit;
			total_profit += profit;
			//cout << i->id << ' ' << diff << ' ' << profit << endl;
			break;
		}
		total_profit += i->profit;
		//cout << i->id << ' ' << i->weight << ' ' << i->profit << endl;
	}
	cout << total_weight << ' ' << total_profit << endl;
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
		int W;
		cin >> W;
		knapsack1(n, W, w, p);
	}
	return 0;
}