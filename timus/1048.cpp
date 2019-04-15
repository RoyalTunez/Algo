#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

vector<int> a, b, res;
int n, x, y, ptr;

int main() {
    cin >> n;
    a.push_back(0);
    b.push_back(0);
    res.push_back(0);
    for (int i = 0; i < n; i++){
        //cin >> x >> y;
        scanf("%d %d", &x, &y);
        a.push_back(x);
        b.push_back(y);
        res.push_back(0);
    }
   
    for (int i = n; i > 0; i--){
        res[i] = (a[i] + b[i] + res[i]) % 10;
        a[i - 1] += (a[i] + b[i]) / 10;
    }
    for (int i = 1; i <= n; i++)
        printf("%d", res[i]);
    
    return 0;
}
