#include <bits/stdc++.h>

using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tt = 1;
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin >> n;
        int x[n], t[n];
        long long mn = 1e15, mx = -1e15;
        for (int i = 0; i < n; ++i) {
            cin >> x[i];
        }
        for (int i = 0; i < n; ++i) {
            int t; cin >> t;
            mn = min(mn, 1LL*(x[i]-t));
            mx = max(mx, 1LL*(x[i]+t));
        }

        printf("%.6f\n", (mx+mn)*1.0/2);
    }

    return 0;
}