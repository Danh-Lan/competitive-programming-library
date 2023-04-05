#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int tt = 1; 
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n, x, y; 
        cin >> n >> x >> y;
        string s, t; cin >> s >> t;

        vector<int> pos;
        for (int i = 0; i < n; ++i) {
            if (s[i] != t[i]) {
                pos.push_back(i);
            }
        }

        if (pos.size() % 2 == 1) {
            cout << -1 << endl;
            continue;
        } else if (pos.size() == 0) {
            cout << 0 << endl;
            continue;
        }

        if (x >= y) {
            long long ans;
            if (pos.size() == 2 && pos[0]+1 == pos[1]) {
                ans = (long long) min(x, 2*y);
            } else {
                ans = 1LL*(pos.size()/2)*y;
            }

            cout << ans << endl;
        } else {
            // multiply by 2 everything to avoid decimal
            x *= 2; y *= 2;
            const long long INF = 1e16;
            vector<long long> dp(pos.size(), INF);
            dp[0] = 1LL*y/2; dp[1] = min(1LL*(pos[1]-pos[0])*x, 1LL*y);
            for (int i = 2; i < pos.size(); ++i) {
                dp[i] = min(dp[i-1] + 1LL*y/2, dp[i-2] + min(1LL*(pos[i]-pos[i-1])*x, 1LL*y));
            }

            cout << dp[pos.size()-1]/2 << endl;
        }
    }

    return 0;
}