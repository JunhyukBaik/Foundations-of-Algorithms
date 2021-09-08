/*
* [2018117635] [백준혁] 저는 이 소스 코드를 다른 소스 코드를 복사하지 않고 직접 작성하였습니다.
*/
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
int cnt = 0;
using namespace std;

void partition(int n, int **a, int **a11, int **a12, int **a21, int **a22);
void madd(int n, int **a, int **b, int **c);
void msub(int n, int **a, int** b, int** c);
void mmult(int n, int** a, int** b, int** c);
void combine(int n, int** a, int** a11, int** a12, int** a21, int** a22);
void strassen(int n, int** a, int** b, int** c);

int main()
{
	int n, m;
	int idx;
	cin >> n;

	if ((n & (n - 1)) == 0)
	{
		m = n;
	}
	else
	{
		string s = bitset<8>(n).to_string();
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == '1')
			{
				idx = 8 - i;
				m = 1 << idx;
				break;
			}
		}
	}

	int** A = new int* [m];
	for (int i = 0; i < m; i++)
		A[i] = new int[m];
	int** B = new int* [m];
	for (int i = 0; i < m; i++)
		B[i] = new int[m];
	int** C = new int* [m];
	for (int i = 0; i < m; i++)
		C[i] = new int[m];;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
		{
			A[i][j] = 0; B[i][j] = 0; C[i][j] = 0;
		}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> A[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> B[i][j];

	strassen(m, A, B, C);

	printf("%d\n", cnt);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", C[i][j]);
		printf("\n");
	}

	return 0;
}

void madd(int n, int** a, int** b, int** c)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			c[i][j] = a[i][j] + b[i][j];
}

void msub(int n, int** a, int** b, int** c)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			c[i][j] = a[i][j] - b[i][j];
}

void mmult(int n, int** a, int** b, int** c)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < n; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
}

void combine(int n, int** a, int** a11, int** a12, int** a21, int** a22)
{
	int m = n / 2;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
		{
			a[i][j] = a11[i][j];
			a[i][j + m] = a12[i][j];
			a[i + m][j] = a21[i][j];
			a[i + m][j + m] = a22[i][j];
		}
}

void partition(int n, int** a, int** a11, int** a12, int** a21, int** a22)
{
	int m = n / 2;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
		{
			a11[i][j] = a[i][j];
			a12[i][j] = a[i][j + m];
			a21[i][j] = a[i + m][j];
			a22[i][j] = a[i + m][j + m];
		}
}

void strassen(int n, int** a, int** b, int** c)
{
	cnt++;
	int** a11, **a12, **a21, **a22;
	int** b11, **b12, **b21, **b22;
	int** c11, **c12, **c21, **c22;
	int** m1, **m2, **m3, **m4, **m5, **m6, **m7;
	int** L, **R;

	if (n <= 2)
	{
		mmult(n, a, b, c);
	}
	else
	{
		int m = n / 2;

		a11 = new int* [m]; a12 = new int* [m]; a21 = new int* [m]; a22 = new int* [m];
		b11 = new int* [m]; b12 = new int* [m]; b21 = new int* [m]; b22 = new int* [m];
		c11 = new int* [m]; c12 = new int* [m]; c21 = new int* [m]; c22 = new int* [m];
		m1 = new int* [m]; m2 = new int* [m]; m3 = new int* [m]; m4 = new int* [m]; m5 = new int* [m]; m6 = new int* [m]; m7 = new int* [m];
		L = new int* [m]; R = new int* [m];
		for (int i = 0; i < m; i++)
		{
			a11[i] = new int[m]; a12[i] = new int[m]; a21[i] = new int[m]; a22[i] = new int[m];
			b11[i] = new int[m]; b12[i] = new int[m]; b21[i] = new int[m]; b22[i] = new int[m];
			c11[i] = new int[m]; c12[i] = new int[m]; c21[i] = new int[m]; c22[i] = new int[m];
			m1[i] = new int[m]; m2[i] = new int[m]; m3[i] = new int[m]; m4[i] = new int[m]; m5[i] = new int[m]; m6[i] = new int[m]; m7[i] = new int[m];
			L[i] = new int[m]; R[i] = new int[m];
		}

		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++)
			{
				a11[i][j] = 0; a12[i][j] = 0; a21[i][j] = 0; a22[i][j] = 0;
				b11[i][j] = 0; b12[i][j] = 0; b21[i][j] = 0; b22[i][j] = 0;
				c11[i][j] = 0; c12[i][j] = 0; c21[i][j] = 0; c22[i][j] = 0;
				m1[i][j] = 0; m2[i][j] = 0; m3[i][j] = 0; m4[i][j] = 0; m5[i][j] = 0; m6[i][j] = 0; m7[i][j] = 0;
				L[i][j] = 0; R[i][j] = 0;
			}
			
		partition(n, a, a11, a12, a21, a22);
		partition(n, b, b11, b12, b21, b22);

		/*
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++)
				printf("%d ", a22[i][j]);
			printf("\n");
		}
		*/

		//m1
		madd(m, a11, a22, L);
		madd(m, b11, b22, R);
		strassen(m, L, R, m1);

		//m2
		madd(m, a21, a22, L);
		strassen(m, L, b11, m2);

		//m3
		msub(m, b12, b22, R);
		strassen(m, a11, R, m3);

		//m4
		msub(m, b21, b11, R);
		strassen(m, a22, R, m4);

		//m5
		madd(m, a11, a12, L);
		strassen(m, L, b22, m5);

		//m6
		msub(m, a21, a11, L);
		madd(m, b11, b12, R);
		strassen(m, L, R, m6);

		//m7
		msub(m, a12, a22, L);
		madd(m, b21, b22, R);
		strassen(m, L, R, m7);

		//c11
		madd(m, m1, m4, L);
		msub(m, L, m5, R);
		madd(m, R, m7, c11)
			;

		//c12
		madd(m, m3, m5, c12);

		//c21
		madd(m, m2, m4, c21);

		//c22
		madd(m, m1, m3, L);
		msub(m, L, m2, R);
		madd(m, R, m6, c22);

		combine(n, c, c11, c12, c21, c22);
	}
}