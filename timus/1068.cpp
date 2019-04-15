#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <math.h>
#include <complex>
using namespace std;

int n;

int main() {
	cin >> n;
	if (n > 0) {
		cout << n * (n + 1) / 2;
	} else {
		cout << n * (-n + 1) / 2 + 1;
	}

    return 0;
}
