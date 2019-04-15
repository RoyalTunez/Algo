#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
typedef long long ll;

ll n, mx = -1;
int main(){
	cin >> n;
	mx = -1;
	for (int i = 3; i <= n; i++)
		if (n % i == 0){
			mx = i;
			break;
		}
	cout << mx - 1;
	return 0;
}
