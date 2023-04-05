// since eventually we still need to take bad key, taking max over dp[n][j] only can be wrong
// instead, taking max over the whole dp[i][j]

#include <bits/stdc++.h>

using namespace std;

const int BTMAX = 31;
const long long INF = -1e18;

long long rightshift(long long x, int times) {
    if (1LL<<times > x) return 0LL;
    else return x>>times;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
    
    int tt = 1; 
    cin>>tt;
    for (int test = 1; test <= tt; test++) {
        int n; long long k; cin>>n>>k;
        int a[n+1];
        for (int i = 1; i <= n; ++i)
        {
            cin>>a[i];
        }

        vector<vector<long long>> dp(n+1, vector<long long>(BTMAX+1, INF));
        dp[0][0] = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= min(BTMAX-1, i); ++j) {
                dp[i+1][j] = max(dp[i+1][j], dp[i][j] - k + rightshift(a[i+1], j) );
                dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] + rightshift(a[i+1], j+1) );
            }
        }

        long long ans = 0LL;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= BTMAX; ++j)
            {
                ans = max(ans, dp[i][j]);
            }
        }

        cout<<ans<<"\n";
    }

    return 0;
}