#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
typedef long long ll;

int n, l, r;
vector<pair<int, int> > v;
map<int, int> my_map;
map<int, int>::iterator it;
vector<pair<int, int> > ans;

int main(){
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> l >> r;
		v.push_back(make_pair(min(l, r), max(l, r)));
		my_map.insert(make_pair(v[i].first, v[i].second));
	}
	sort(v.begin(), v.end());
	int ptr = 0;
	for (int i = 1; i < n; i++)
		if (v[i].second < v[ptr].second) ptr = i;
	ans.push_back(v[ptr]);
	r = v[ptr].second;
	while (true){
		ptr = -1;
		for (int i = 0; i < n; i++){
			if (v[i].first >= r && ptr == -1){
				ptr = i;
				continue;
			}
			if (v[i].first >= r && v[i].second < v[ptr].second){
				ptr = i;
				continue;
			}
		}
		if (ptr == -1) break;
		ans.push_back(v[ptr]);
		r = v[ptr].second;
	}
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i].first << " " << ans[i].second << endl;
	//system("pause");
	return 0;
}
