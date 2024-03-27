#include <iostream>
#include <algorithm>
using namespace std;
int main () {
    int n, x, y; cin >> n >> x >> y;
    int ans = 0;
    for(int i=0; i<n; i++) {
        int a; cin>>a;
        ans += min(a*x, y);
    }
    cout << ans << "\n";
}