#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

const int SIZE = 3 * 1e5;

int from, to, n, m;
unordered_set<int> g[SIZE];
int ans[SIZE];
int dp[SIZE]; 

void count(int v, int prev) {
	dp[v] = 1;
	for (int i: g[v]) {
		if (i != prev) {
			count(i, v);
			dp[v] += dp[i];
		}
	}
}

int centr(int v, int prev, int siz) {
	int check = -1;
	for (int i: g[v]) {
		if (i != prev && dp[i] * 2 > siz) {
			check = i;
			break;
		}
	}
	if (check == -1) {
		return v;
	} else {
		return centr(check, v, siz);
	}
}

void build(int v, int prev) {
	vector<int> del;
	for (int i: g[v]) {
		del.push_back(i);
	}
	for (int i: del) {
		g[v].erase(i);
		g[i].erase(v);
	}
	if (prev == -1) {
		ans[v] = 0;
	} else {
		ans[v] = prev;
	}
	if (g[v].empty()) {
		for (int i: del) {
			count(i, -1);
			int go = centr(i, -1, dp[i]);
			build(go, v);
		}	
	}
}
  
int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 1; i < n; i++) {
    	cin >> from >> to;
    	g[from].insert(to);
    	g[to].insert(from);
	}
	count(1, -1);
	int start = centr(1, -1, dp[1]);
	build(start, -1);
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " ";
	} 
    return 0;
}
