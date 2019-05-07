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
   
constexpr int SIZE = 100001;
     
struct hash_sets { 
    template <class T> 
    size_t operator()(const T & p) const { 
      
      return p[0];
    } 
}; 
   
vector<int> g[SIZE];
char c;
int n, m, k, from, to;
vector<int> rev[SIZE];
unordered_set<int> special, p;
unordered_set<char> symbols;
vector<unordered_set<int>> my_set;
int my_map[SIZE][26];
pair<vector<int>, vector<int>> tmpset;
vector<int> inv[SIZE][26];
unordered_map<int, int> anspos;
unordered_set<int> ansspecial;
set<pair<pair<int, int>, char>> edges;
int clas[SIZE];
map<pair<int, char>, int>::iterator it;
unordered_map<int, vector<int>> involved;
queue<pair<int, char>> q;
unordered_set<int> specv;
bool check[SIZE][2];
   
void dfs1(int v, int c) {
    check[v][c] = true;
    for (int i: g[v]) {
        if (!check[i][c])
            dfs1(i, c);
    }
}
   
void dfs2(int v, int c) {
    check[v][c] = true;
    for (int i: rev[v]) {
        if (!check[i][c])
            dfs2(i, c);
    }
}
   
int main(int argc, char** argv) {
  freopen("fastminimization.in", "r", stdin);
  	freopen("fastminimization.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> k;
    while (k--) {
        int tmp;
        cin >> tmp;
        special.insert(tmp);
    }
    while (m--) {
        cin >> from >> to >> c;
        g[from].push_back(to);
        rev[to].push_back(from);
        my_map[from][c - 'a'] = to;
    }
    dfs1(1, 0);
    for (int i: special) {
        dfs2(i, 1);
    }
    for (int i = 1; i <= SIZE; i++)
        check[i][0] = check[i][0] and check[i][1];
    for (int i = 1; i < SIZE; i++)
        for (int j = 0; j < 26; j++)
            if (!(check[i][0] && check[my_map[i][j]][0])) {
            	my_map[i][j] = 0;
						} else {
							inv[my_map[i][j]][j].push_back(i);
							symbols.insert(char(j + 'a'));
						}
        
     
    for (int i = 1; i <= n; i++) {
      if (check[i][0]) {
        if (special.find(i) == special.end()) {
          p.insert(i);
          clas[i] = 1;
        } else {
          specv.insert(i);
          clas[i] = 0;
        }
      }
    }
    if (specv.size() > 0) {
    	my_set.push_back(specv);
		} 
    if (p.size() > 0) {
      my_set.push_back(p);
    } 
    for (char i: symbols) {
    	q.push(make_pair(0, i));
      if (p.size() > 0) {
      		q.push(make_pair(1, i));
      } 
    }
    while (!q.empty()) {
        pair<int, char> tmp = q.front();
        q.pop();
        involved.clear();
        for (int i: my_set[tmp.first]) {
        	for (int j: inv[i][tmp.second - 'a']) {
        		int ptr = clas[j];
        		involved[ptr].push_back(j);
					}
				}
				for (auto i: involved) {
					if (i.second.size() < my_set[i.first].size()) {
						unordered_set<int> newset = *new unordered_set<int>();
						int newptr = my_set.size();
						for (int j: i.second) {
							my_set[i.first].erase(j);
							newset.insert(j);
						}
						my_set.push_back(newset);
						for (int j: my_set[newptr]) {
							clas[j] = newptr;
						}
						for (char j: symbols) {
							q.push(make_pair(newptr, j));
						}
					}
				}
    }
    vector<unordered_set<int>> tmpvec;
    tmpvec.clear();
    for (auto i: my_set) {
        tmpvec.push_back(i);
    }
    int hello = 0;
    for (auto i: tmpvec) {
        if (i.find(1) != i.end()) {
            break;
        }
        hello++;
    }
    swap(tmpvec[0], tmpvec[hello]);
    for (auto i: tmpvec) {
        for (auto j : i) {
            anspos[j] = cnt;
        }
        cnt++;
    }
       
    for (auto i : specv) {
        ansspecial.insert(anspos[i]);
    }
     for (int i = 1; i < SIZE; i++)
        for (int j = 0; j < 26; j++)
            if (my_map[i][j] > 0)
            	edges.insert(make_pair(make_pair(anspos[i], anspos[my_map[i][j]]), char(j + 'a')));
    cout << my_set.size() << " " << edges.size() << " " << ansspecial.size() << endl;
    for (int i: ansspecial) {
        cout << i << " ";
    }
    cout << endl;
    for (auto i: edges) {
        cout << i.first.first << " " << i.first.second << " " << i.second << endl;
    }
       
    return 0;
}

