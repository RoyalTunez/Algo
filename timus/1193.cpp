#include<stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <vector>
#include <set>
#include <queue>
#define forn(a, b) for (int a = 0; i < b; a++)

using namespace std;
typedef long long ll;

int n, t, max_t = -1;

struct stud {
    int start, end, time;
    bool used = false;
};

stud a[41];

bool comp(stud a, stud b) {
    return a.start < b.start;
}

int main(int argc, char** argv) {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i].start >> a[i].time >> a[i].end;
    sort(a, a + n, comp);
    t = a[0].start + a[0].time;
    a[0].used = true;
    if (a[0].end < t) max_t = abs(a[0].end - t);
    for (int i = 1; i < n; i++){
            if (t < a[i].start) t = a[i].start;
            t += a[i].time;
            if (t > a[i].end) max_t = max(max_t, t - a[i].end);
    }

    if (max_t == -1) cout << 0;
    else cout << max_t;
    return 0;
}
