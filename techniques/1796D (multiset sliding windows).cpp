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
        int n, k, x; cin >> n >> k >> x;
        if (x < 0) {
            k = n-k;
            x = -x;
        }

        int a[n];
        long long b[n+1] = {0}, c[n+1] = {0};
        for (int i = 0; i < n; ++i) {
            cin >> a[i];

            b[i+1] = b[i] + a[i] + x;

            if (c[i] > 0) c[i+1] = c[i] + a[i] - x;
            else c[i+1] = a[i] - x;
        }

        if (k == 0) {
            cout << *max_element(c, c+n+1) << '\n';
            continue;
        }

        long long ans = 0LL;
        multiset<long long> ms;
        ms.insert(0);
        for (int i = 0; i < n; ++i) {
            if (i >= k) ms.erase(ms.find(b[i-k]));
            if (!ms.empty()) {
                ans = max(ans, b[i+1] - *ms.begin());
            }
            
            ms.insert(b[i+1]);
        }

        long long curSum = 0LL;
        for (int i = 0; i < k; ++i) {
            curSum += a[i] - x;
        }
        ans = max(ans, curSum+2LL*k*x);
        for (int i = k; i < n; ++i) {
            curSum += a[i] - a[i-k];
            ans = max(ans, curSum+2LL*k*x);
            ans = max(ans, curSum+c[i-k+1]+2LL*k*x);
        }

        cout << ans << '\n';
    }

    return 0;
}
