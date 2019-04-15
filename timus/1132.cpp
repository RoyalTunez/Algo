#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;
const int size = 32768;
int k, a, n;
 
pair<int, int> tmp;
int arr[size];
pair<int, int> input[100001];
int output[100001];
vector<pair<int, int> > counter[size];

int main(int argc, char** argv) {
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &tmp.first, &tmp.second);
		tmp.first = tmp.first - tmp.second * (tmp.first / tmp.second);
		input[i] = tmp;
		counter[tmp.second].push_back(make_pair(tmp.first, i));
	}
	for (int i = 2; i < size; i++) {
		if (counter[i].empty())
			continue;
		for (int j = 0; j < counter[i].size(); j++)
			arr[counter[i][j].first] = -1;
		for (int j = 1, cnt = 2; cnt <= (i / 2) + 1; j+= 2*cnt - 1, cnt++)
			arr[j - i *(j / i)] = cnt - 1;
		for (int j = 0; j < counter[i].size(); j++) {
			output[counter[i][j].second] = arr[counter[i][j].first];
		}
	}
	
	for (int i = 0; i < k; i++) {
		int ans = output[i];
		if (ans == -1) {
			printf("No root\n");
			continue;
		}
		int second = input[i].second - ans;
		if (ans == second ) {
			printf("%d\n", ans);
			continue;
		}
		if (ans < second) {
			printf("%d %d\n", ans, second);
		} else {
			printf("%d %d\n", second, ans);
		}
	}
	return 0;
}
