#include <iostream>
#include <algorithm>
#include <set>
#include <stdio.h>
#include <math.h>
#include <queue>
#include <iomanip>
using namespace std;
typedef long long ll;


vector<unsigned long long> in;
unsigned long long tmp;

int main(void) {
    while (cin >> tmp) {
        in.push_back(tmp);
    }
    reverse(in.begin(), in.end());
    for (int i = 0; i < in.size(); i++)
        cout << setprecision(5) << fixed << sqrt(in[i]) << endl;
    return 0;
}
