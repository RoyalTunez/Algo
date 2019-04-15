#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <unordered_set>

using namespace std;	

int n, start;
int g[1001][1001];
vector<int> res;
stack<int> st;

int main(int argc, char** argv) {
	cin >> n >> start;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cin >> g[i][j];
			g[i][j] = 1 - g[i][j]; 
		}
	for (int i = 0; i < n; i++)
		g[i][i] = 0;
	st.push(start - 1);
	while (!st.empty()) {
		int tmp = st.top();
		int i;
		for (i = 0; i < n; i++)
			if (g[tmp][i] == 1)
				break;
		if (i == n) {
			res.push_back(tmp);
			st.pop();
		} else {
			g[tmp][i] = 0;
			st.push(i);
		}
	}
	for (int i = res.size() - 1; i > 0; i--)
		cout << res[i] + 1  << " " << res[i - 1] + 1 << endl;
	return 0;
}
