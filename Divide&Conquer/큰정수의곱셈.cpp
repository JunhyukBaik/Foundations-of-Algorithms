/*
* [2018117635] [백준혁] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#include <iostream>
#include <string.h>
#define MAX 256
#define BASE 10
using namespace std;

int cnt = 0;
const int threshold = 1;

typedef struct large_integer {
	int sign;
	int len;
	int digits[MAX]; // stored in reverse order
}large_integer;

void create_largeint(large_integer &u, char* str);
int compare_by_abs(large_integer u, large_integer v);
void lsum(large_integer u, large_integer v, large_integer& r);
void ldiff(large_integer u, large_integer v, large_integer& r);
void ladd (large_integer& u, large_integer& v, large_integer& r);
void lsub(large_integer u, large_integer v, large_integer& r);
void pow_by_exp(large_integer u, int m, large_integer& v);
void div_by_exp(large_integer u, int m, large_integer& v);
void rem_by_exp(large_integer u, int m, large_integer& v);
void lmult(large_integer u, large_integer v, large_integer& r);
void prod2(large_integer u, large_integer v, large_integer& r);

int main()
{
	int T;
	cin >> T;
	for (int aaaa = 0; aaaa < T; aaaa++) {
		char A[MAX], B[MAX];
		cin >> A >> B;
		large_integer la, lb, result;
		create_largeint(la, A);
		create_largeint(lb, B);
		//for (int i = 0; i < la.len; i++)
			//printf("%d", la.digits[i]);
		//rem_by_exp(la, 3, result);
		//for (int i = 0; i < result.len; i++)
			//printf("%d", result.digits[i]);

		prod2(la, lb, result);
		printf("%d ", cnt);
		for (int i = result.len - 1; i >= 0; i--)
			printf("%d", result.digits[i]);
		printf("\n");
		cnt = 0;
		
	}
	return 0;
}

void create_largeint(large_integer& u, char* str)
{
	if (str[0] == '-') {
		u.sign = 1;
		u.len = strlen(str) - 1;
		int idx = strlen(str) - 1;
		for (int i = 0; i < strlen(str) - 1; i++) {
			u.digits[i] = str[idx - i] - '0';
		}
	}
	else {
		u.sign = 0;
		u.len = strlen(str);
		int idx = strlen(str) - 1;
		for (int i = 0; i < strlen(str); i++) {
			u.digits[i] = str[idx - i] - '0';
		}
	}
}

int compare_by_abs(large_integer u, large_integer v)
{
	if (u.len > v.len)
		return 1;
	else if (u.len < v.len)
		return -1;
	else {
		for (int i = u.len - 1; i >= 0; i--) {
			if (u.digits[i] == v.digits[i])
				continue;
			else if (u.digits[i] > v.digits[i])
				return 1;
			else if (v.digits[i] > u.digits[i])
				return -1;
		}
		return 0;
	}
}

void lsum(large_integer u, large_integer v, large_integer& r)
{
	int k = 0;
	while (k < u.len && k < v.len) {
		r.digits[k] = u.digits[k] + v.digits[k];
		k++;
	}
	for (; k < u.len; k++)
		r.digits[k] = u.digits[k];
	for (; k < v.len; k++)
		r.digits[k] = v.digits[k];
	int carry = 0, i = 0;
	for (; i < k; i++) {
		int d = r.digits[i] + carry;
		r.digits[i] = d % BASE;
		carry = d / BASE;
	}
	if (carry > 0)
		r.digits[i++] = carry;
	r.len = i;
}

void ldiff(large_integer u, large_integer v, large_integer& r)
{
	int k = 0;
	while (k < u.len && k < v.len) {
		r.digits[k] = u.digits[k] - v.digits[k];
		k++;
	}
	for (; k < u.len; k++)
		r.digits[k] = u.digits[k];
	int borrow = 0, i = 0;
	for (; i < k; i++) {
		int d = r.digits[i] - borrow;
		r.digits[i] = (d >= 0) ? d: d + BASE;
		borrow = (d >= 0) ? 0 : 1;
	}
	while (i > 0 && r.digits[i - 1] == 0)
		i--;
	r.len = i;
}

void ladd(large_integer& u, large_integer& v, large_integer& r)
{
	if (u.sign == v.sign) {
		lsum(u, v, r);
		r.sign = u.sign;
	}
	else {
		switch (compare_by_abs(u, v)) {
		case 1:
			ldiff(u, v, r);
			r.sign = u.sign;
			break;
		case -1:
			ldiff(v, u, r);
			r.sign = v.sign;
			break;
		case 0:
			r.sign = r.len = 0;
			break;
		}
	}
}

void lsub(large_integer u, large_integer v, large_integer& r)
{
	if (u.sign == v.sign) {
		if (u.sign == 0) {		// 둘 다 부호가 +
			switch (compare_by_abs(u, v)) {
			case 1: // u가 더큰경우
				ldiff(u, v, r);
				r.sign = u.sign;
				break;
			case -1: // v가 더큰경우
				ldiff(v, u, r);
				r.sign = 1;
				break;
			case 0: // 값이 같음
				r.sign = r.len = 0;
				break;
			}
		}
		else {				// 둘 다 부호가 -
			switch (compare_by_abs(u, v)) {
			case 1:
				ldiff(u, v, r);
				r.sign = u.sign;
				break;
			case -1:
				ldiff(v, u, r);
				r.sign = 0;
				break;
			case 0:
				r.sign = r.len = 0;
				break;
			}
		}
	}
	else {				// 부호가 다를 때
		lsum(u, v, r);
		r.sign = u.sign;	// 값을 더하고 부호는 앞에꺼 따라감..
	}
}

void pow_by_exp(large_integer u, int m, large_integer& v)
{
	v.sign = u.sign;
	v.len = u.len + m;
	for (int i = 0; i < m; i++)
		v.digits[i] = 0;
	for (int i = 0; i < u.len; i++)
		v.digits[m + i] = u.digits[i];
}

void div_by_exp(large_integer u, int m, large_integer& v)
{
	v.sign = u.sign;
	v.len = u.len - m;
	for (int i = 0; i < v.len; i++)		// i < u.len -> i < v.len으로 수정
		v.digits[i] = u.digits[m + i];
}

void rem_by_exp(large_integer u, int m, large_integer& v)
{
	int dgts[MAX];
	v.sign = u.sign;
	for (int i = 0; i < m; i++)
		dgts[i] = u.digits[i];
	int i = m - 1;
	for (; i >= 0; i--) {
		if (dgts[i] != 0) {
			break;
		}
	}
	i++;
	for (int j = 0; j < i; j++){
		v.digits[j] = dgts[j];
	}
	v.len = i;
}

void lmult(large_integer u, large_integer v, large_integer& r)
{
	r.sign = (u.sign == v.sign) ? 0 : 1;
	r.len = u.len + v.len - 1;
	for (int i = 0; i < r.len; i++)
		r.digits[i] = 0;
	for (int i = 0; i < v.len; i++)
		for (int j = 0; j < i + u.len; j++)
			r.digits[j] += v.digits[i] * u.digits[j];
	int carry = 0, i = 0;
	for (; i < r.len; i++) {
		int d = r.digits[i] + carry;
		r.digits[i] = d % BASE;
		carry = d / BASE;
	}
	if (carry > 0)
		r.digits[i++] = carry;
	r.len = i;
}

void prod2(large_integer u, large_integer v, large_integer &jh)
{
	cnt++;
	large_integer x, y, w, z, r, p, q, t1, t2, t3, t4, t5, t6, t7;
	int n, m;
	n = (u.len > v.len) ? u.len : v.len;
	if (u.len == 0 || v.len == 0)
		jh.sign = jh.len = 0;
	else if (n <= threshold)
		lmult(u, v, jh);
	else {
		int m = n / 2;
		div_by_exp(u, m, x); rem_by_exp(u, m, y);
		div_by_exp(v, m, w); rem_by_exp(v, m, z);
		ladd(x, y, t1);	ladd(w, z, t2);
		prod2(t1, t2, r);
		prod2(x, w, p);
		prod2(y, z, q);
		pow_by_exp(p, 2 * m, t3); // p x 10^2m
		lsub(r, p, t4); lsub(t4, q, t5); pow_by_exp(t5, m, t6); // (r - p -q)x10^m
		ladd(t3, t6, t7);
		ladd(t7, q, jh);
	}
}