#include<stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <vector>
#include <set>
#include <queue>

using namespace std;
typedef unsigned long long ull;	

ull n, a, b;
ull c[1001][1001];
 
int main(int argc, char** argv) {
	cin >> n >> a >> b;
	c[0][0] = 1;
	c[0][1] = 0;
	for (int i = 1; i < n + 1 + max(a, b); i++){
		c[i][0] = 1;
		for (int j = 1; j <= n; j++)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
	
	cout << c[a + n][n] * c[b + n][n];	
	//system("pause");
	return 0;
}
