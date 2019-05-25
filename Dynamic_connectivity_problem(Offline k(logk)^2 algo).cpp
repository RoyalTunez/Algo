#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

constexpr int SIZE = 2 * 1e5 + 1;

vector<pair<int*, int>> changes;
int parent[SIZE], rang[SIZE];

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> & p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;  
    }
};

int find(int x){
    if (parent[x] != x)
        return find(parent[x]);
    else
        return x;
}

void union_set(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    if (rang[x] > rang[y]) {
    	changes.emplace_back(&parent[y], parent[y]);
    	parent[y] = x;
		return;
	}
	if (rang[x] < rang[y]) {
		changes.emplace_back(&parent[x], parent[x]);
    	parent[x] = y;
		return;
	}
	changes.emplace_back(&rang[x], rang[x]);
	changes.emplace_back(&parent[y], parent[y]);
	parent[y] = x;
	rang[x]++;
}

string s;
int check[SIZE];
pair<int, int> question[SIZE];
unordered_map<pair<int, int>, int, pair_hash> time;
vector<pair<int, int>> tree[4 * SIZE];

void add(int v, int cl, int cr, int l, int r, pair<int, int> in) {
	if (cl > r || cr < l) {
		return;
	}
	if (cl >= l && cr <= r) {
		tree[v].push_back(in);
		return;
	}
	int mid = (cl + cr) / 2;
	add(2 * v, cl, mid, l, r, in);
	add(2 * v + 1, mid + 1, cr, l, r, in);
}

int get_tree_size(int a) {
    int long b = 1;
    while (b < a) b *= 2;
    return b - 1;
}   

int length;

void solve(int v, int l, int r) {
	int oldSize = changes.size();
	for (auto edge: tree[v]) {
		union_set(edge.first, edge.second);
	}
	if (l == r) {
		if (check[l]) {
			if (find(question[l].first) == find(question[l].second)) {
				cout << "1\n";
			} else {
				cout << "0\n";
			}	
		}
	} else {
		int mid = (l + r) / 2;
		solve(2 * v, l, mid);
		solve(2 * v + 1, mid + 1, r);
	}
	while (changes.size() > oldSize) {
		*changes.back().first = changes.back().second;
        changes.pop_back();
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
    	parent[i] = i;
    	rang[i] = 1;
    }
    length = get_tree_size(m + 1);
    for (int i = 1; i <= m; i++) {
    	pair<int, int> edge;
    	cin >> s >> edge.first >> edge.second;
    	if (edge.first > edge.second) {
    		swap(edge.first, edge.second);
		}
    	if (s == "link") {
    		time[edge] = i;
    		continue;
	}
	if (s == "cut") {
		int start = time[edge];
		time.erase(edge);
		int end = i;
		add(1, 1, length + 1, start, end, edge);
		continue;
	}
	if (s == "connected") {
		check[i] = true;
		question[i] = edge;
		continue;
	}
    }
    for (pair<pair<int, int>, int> i: time) {
    	add(1, 1, length + 1, i.second, m, i.first);
    }
    solve(1, 1, length + 1);
    return 0;
}
