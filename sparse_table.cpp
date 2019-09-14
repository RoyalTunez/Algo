#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
 
int n, m, a[200001], a0, u0, v0;
int u[20000001], v[20000001];
int powerTable[200001], tmp;
vector<int> table[50];
 
int get(int l, int r) {
	int lsize = powerTable[r- l + 1];
	int ptr = -1;
	int safe = lsize;
	while (safe > 0) {
		safe /= 2;
		ptr++;
	}
	//cout << ptr << endl;
 //	cout << l << " " << r << " " << lsize << " " << ptr << " " << r - lsize << endl;
	return min(table[ptr][l], table[ptr][r - lsize + 1]);
}
 
int main() {
	cin >> n >> m >> a[0];
	for (int i = 1; i < n; i++)
		a[i] = (23 * a[i - 1] + 21563) % 16714589;
	tmp = 1;
	while (tmp <= n) {
		int ntmp = tmp * 2;
		for (int i = tmp; i <= ntmp; i++)
			powerTable[i] = tmp;
		tmp = ntmp;
	}
//	for (int i = 1; i < n; i++)
	//	cout << powerTable[i] << " ";
	for (int i = 0; i < n; i++)
		table[0].push_back(a[i]);
	int tmpPow = 1;
	while (tmpPow < n)
		tmpPow *= 2;
	tmpPow -= n;
	while (tmpPow--)
		table[0].push_back(16714590);
			
	int tableSize = 1;
	for (int power = 2; power <= table[0].size(); power *= 2, tableSize++) {
		for (int i = 0; i + power / 2 < table[tableSize - 1].size(); i++)
			table[tableSize].push_back(min(table[tableSize - 1][i], table[tableSize - 1][i + power / 2]));
	}
	/*for (int i = 0; i < tableSize; i++) {
		for (int j = 0; j < table[i].size(); j++)
			cout << table[i][j] << " ";
		cout << endl;
	}*/
	cin >> u[0] >> v[0];
	int ans = get(min(u[0], v[0]) - 1, max(u[0], v[0]) - 1);
	for (int i = 1; i < m; i++) {
		//cout << u[i - 1]  << " " << v[i - 1] << " - " << ans << endl;
		u[i] = (17 * u[i - 1] + 751 + ans + 2 * i) % n + 1;
		v[i] = (13 * v[i - 1] + 593 + ans + 5 * i) % n + 1;
		ans = get(min(u[i], v[i]) - 1, max(u[i], v[i]) - 1);
	}
	cout << u[m - 1] << " " << v[m - 1] << " " << ans;
 
    return 0;
}
