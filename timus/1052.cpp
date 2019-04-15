#include <stdio.h>
#include <iostream>
#include <math.h> 
#include <fstream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <queue>
#include <string>
using namespace std;
typedef long long ll;
typedef double d;
const d eps = 1e-8;

d s(pair<d, d> a, pair<d, d> b, pair<d, d> c){
	return abs(a.first * b.second + b.first * c.second + c.first * a.second - a.second * b.first - b.second * c.first - c.second * a.first) / 2.0;
}

int n, best = -1;
pair<d, d> a[201];
int main(){
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i].first >> a[i].second;
	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			int tmp = 2;
			for (int z = 0; z < n; z++){
				if (z == i || z == j) continue;
				if (s(a[i], a[j], a[z]) <= eps) tmp++;
			}
			best = max(best, tmp);
		}
			
	}
	cout << best;
	//system("pause");
  return 0;
}
