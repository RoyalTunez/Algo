#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <math.h>
#include <algorithm>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <queue>
using namespace std;
typedef long long ll;
const int len = 6020;
int SIZE;
const int inf = (int)1e9;
int n;
vector<int> in;
vector<vector<int>> g;
int flow[len][len], cost[len][len], pot[len];

int get_p(int u, int v) {
    return cost[u][v] + pot[u] - pot[v];
}

int add_path(int from, int to) {
    vector<int> dist(SIZE, (int)1e9), prv(SIZE);
    vector<bool> check(SIZE, false);
    dist[from] = 0;
    check[from] = true;
    priority_queue<pair<int, int>> q;
    q.push(make_pair(0, from));

    while (!q.empty()) {
        auto tmp = q.top();
        tmp.first *= -1;
        q.pop();
        if (dist[tmp.second] != tmp.first) {
            continue;
        }
        check[tmp.second] = true;
        for (auto i: g[tmp.second]) {
            if (flow[tmp.second][i] > 0 && dist[i] > dist[tmp.second] + get_p(tmp.second, i)) {
                dist[i] = dist[tmp.second] + get_p(tmp.second, i);
                prv[i] = tmp.second;
                q.push(make_pair(-dist[i], i));
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        pot[i] += dist[i];
    }

    if (!check[to]) {
        return inf;
    }
    int ptr = to, cap = inf, sum = 0;

    while (ptr != from) {
        cap = min(cap, flow[prv[ptr]][ptr]);
        ptr = prv[ptr];
    }

    ptr = to;
    while (ptr != from) {
        flow[prv[ptr]][ptr] -= cap;
        flow[ptr][prv[ptr]] += cap;
        sum += cost[prv[ptr]][ptr];
        ptr = prv[ptr];
    }

    return sum;
}

int solve(int from, int to) {
    int sum = 0, tmp;

    while ((tmp = add_path(from, to)) != inf) {
        sum -= tmp;
    }

    return sum;
}

void add(int from, int to, int in_flow, int in_cost) {
    g[from].push_back(to);
    g[to].push_back(from);
    flow[from][to] = in_flow;
    cost[from][to] = in_cost;
    cost[to][from] = -in_cost;
}

vector<int> super_cnt[100002];
vector<int> cnt[7];
vector<int> top_sort;
bool check[len];

void dfs(int v, int prv) {
    check[v] = true;
    for (int i: g[v]) {
        if (!check[i]) {
            dfs(i, v);
        }
    }
    top_sort.push_back(v);
}
int main() {
    scanf("%d", &n);
    SIZE = 2 * n + 3;
    in.resize(SIZE);
    for (int i = 0; i < n; i++) {
        scanf("%d", &in[i]);
    }
    g.resize(SIZE, vector<int>());
    add(0, 1, 4, 0);

    for (int i = 0; i < n; i++) {
        add(2 * i + 3, 2 * i + 4, 1, -1);
        add(1, 2 * i + 3, 1, 0);
        add(2 * i + 4, 2, 1, 0);
        for (int j: cnt[in[i] % 7]) {
            add(2 * j + 4, 2 * i + 3, 1, 0);
        }
        for (int j: super_cnt[in[i] - 1]) {
            add(2 * j + 4, 2 * i + 3, 1, 0);
        }
        for (int j: super_cnt[in[i] + 1]) {
            add(2 * j + 4, 2 * i + 3, 1, 0);
        }
        cnt[in[i] % 7].push_back(i);
        super_cnt[in[i]].push_back(i);
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < i; j++) {
            if (flow[j][i] && pot[j] + cost[j][i] < pot[i]) {
                pot[i] = pot[j] + cost[j][i];
            }
        }
    }
    dfs(0, -1);
    for (int i: top_sort) {
        for (int j: g[i]) {
            pot[j] += cost[i][j];
        }
    }
    cout << solve(0, 2);
    return 0;
}
