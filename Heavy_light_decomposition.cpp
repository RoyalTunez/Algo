#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;
constexpr int SIZE = 3 * 1e5;   
   
int n, m;   
int from, to;
vector<int> g[SIZE];
vector<int> up[SIZE];
int depth[SIZE];
int power[SIZE];
vector<int> get_range[SIZE];
pair<int, int> timer[SIZE];
int get_index[SIZE];
int in_tree[SIZE];
long long tree[4 * SIZE];

void count_power(int v, int prev) {
	for (int i: g[v]) {
		if (i == prev) {
			continue;
		}
		count_power(i, v);
		power[v] += power[i];
	}
	power[v]++;
}

vector<int> tmp;

int time_cnt = 1;

void binary_up(int v, int prev) {
	timer[v].first = time_cnt;
	tmp.push_back(v);
	int p = 1;
	while (p < tmp.size()) {
		up[v].push_back(tmp[tmp.size() - p - 1]);
		p *= 2;
		depth[v]++;
	}
	for (int i: g[v]) {
		if (i == prev) {
			continue;
		}
		time_cnt++;
		binary_up(i, v);
	}
	tmp.pop_back();
	time_cnt++;
	timer[v].second = time_cnt;
}

bool Luke_I_am_Your_Father(int Luke, int Darth_Vader) {
	if (timer[Luke].first >= timer[Darth_Vader].first && timer[Luke].second <= timer[Darth_Vader].second)
		return true;
	return false;
}

int lca(int u, int v) {
	if (Luke_I_am_Your_Father(u, v)) return v;
	if (Luke_I_am_Your_Father(v, u)) return u;
	if (depth[u] > depth[v])
		swap(u, v);
	int p = depth[u];
	for (int i = p; i >= 0; i--) {
		if (i < up[u].size() && !Luke_I_am_Your_Father(v, up[u][i]))
			u = up[u][i];
	}
	return up[u][0];
}

int index = 1;
int cnt = 1;

void build_hld(int v, int prev) {
	if (g[v].empty() || (g[v].size() == 1 && prev != -1)) {
		get_range[index].push_back(v);
		get_index[v] = index;
		in_tree[v] = cnt;
		cnt++;
		return;
	}
	int hard = -1;
	for (int i: g[v]) {
		if (i != prev) {
			hard = i;
			break;
		}
	}
	for (int i: g[v]) {
		if (i != prev && power[i] > power[hard]) {
			hard = i;
		}
	}
	get_index[v] = index;
	in_tree[v] = cnt;
	cnt++;
	get_range[index].push_back(v);
	build_hld(hard, v);
	for (int i: g[v]) {
		if (i == prev || i == hard) {
			continue;
		}
		index++;
		build_hld(i, v);
	}
}

long long getsum(int c, int cl, int cr, int l, int r) {
  if (cl >= l && cr <= r) {
      return tree[c];
  } 
	if (cl > r || cr < l) {
        return 0;
  }
  int middle = (cl + cr) / 2;
  
  return getsum(2 * c, cl, middle, l, r) + 
         getsum(2 * c + 1, middle + 1, cr, l, r);
}

int get_tree_size(int a) {
    int long b = 1;
    while (b < a) b *= 2;
    return b;
}           

void update(int x, long long delta) {
	tree[x] += delta;
	x /= 2;
	while (x > 0) {
		tree[x] += delta;
		x /= 2;
	} 
}

int length;

void update(int l, int r, long long val) {
	update(l + length, val);
	update(r + length + 1, -val);
}

long long get_x(int x) {
	return getsum(1, 1, length + 1, 1, x);
}

void add_sum(int x, int y, long long val) {
	if (Luke_I_am_Your_Father(y, x)) {
		swap(x, y);
	}
	while (get_index[x] != get_index[y]) {
		int i = get_index[x];
		int l = get_range[i][0], r = x;
		update(in_tree[l], in_tree[r], val);
		x = up[get_range[i][0]][0];
	}
	update(in_tree[y], in_tree[x], val);
}
   
int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> from >> to;
		if (from == to) {
			continue;
		}
		g[from].push_back(to);
		g[to].push_back(from);
	}
    int start = 1;
    count_power(start, -1);
    binary_up(start, -1);
    up[start].push_back(start);
	build_hld(start, -1);
	length = get_tree_size(n + 1) - 1;
	cin >> m;
	while (m--) {	
		char c;
		cin >> c;
		if (c == '?') {
			int x;
			cin >> x;
			cout << get_x(in_tree[x]) << endl;
		} else {
			int x, y;
			long long val;
			cin >> x >> y >> val;
			if (x == y) {
				update(in_tree[x], in_tree[x], val);
				continue;
			}
			if (Luke_I_am_Your_Father(x, y)) {
				add_sum(y, x, val);
				continue;
			}
			if (Luke_I_am_Your_Father(y, x)) {
				add_sum(x, y, val);
				continue;
			}
			int v = lca(x, y);
			add_sum(v, x, val);
			add_sum(v, y, val);
			update(in_tree[v], in_tree[v], -val);
		}
	}
    return 0;
}
