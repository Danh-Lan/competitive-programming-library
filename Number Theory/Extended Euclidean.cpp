#include <bits/stdc++.h>

using namespace std;

// x y is 1 solution of ax+by = extended_gcd(a,b)
long long extended_gcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// ax0 + by0 = c --> extended_gcd(a,b) | c
// ax0 + k*lcm(a,b)
bool find_any_solution(long long a, long long b, long long c, long long &x0, long long &y0, long long &g) {
    g = extended_gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tt = 1;
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin >> n;
        int a[n], b[n];
        for (int i = 0; i < n; ++i) {
            cin >> a[i] >> b[i];
        }

        long long cur = accumulate(b, b+n, 0LL);
        vector<long long> diffs(n);
        for (int i = 0; i < n; ++i) {
            diffs[i] = a[i] - b[i];  
        }
        sort(diffs.begin(), diffs.end(), greater<int>());
        vector<long long> best(n + 1);
        for (int i = 0; i <= n; ++i) {
            best[i] = cur;
            if (i < n) cur += diffs[i];
        }
        int mx = max_element(best.begin(), best.end()) - best.begin();
        
        int m; cin >> m;
        for (int i = 0; i < m; ++i) {
            int x, y; cin >> x >> y;
            long long x0, y0, g;
            if (!find_any_solution(x, y, n, x0, y0, g)) {
                cout << -1 << '\n';
                continue;
            }

            long long lcm = x * 1LL * y / g;
            long long red = x0 * 1LL * x;
            red = red + (max(0LL, mx - red) + lcm - 1) / lcm * lcm;
            red = red - max(0LL, red - mx) / lcm * lcm;
            long long ans = -1;
            if (red <= n) ans = max(ans, best[red]);
            red -= lcm;
            if (red >= 0) ans = max(ans, best[red]);

            cout << ans << '\n';
        }
    }

    return 0;
}

// 1728E