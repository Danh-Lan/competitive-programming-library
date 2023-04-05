#include <bits/stdc++.h>

using namespace std;

const int INF = 1e8;

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
        int n; cin>>n;
        int a[n];
        for (int i = 0; i < n; ++i) {
            cin>>a[i];
        }

        int dp[n][8192];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 8192; ++j) {
                dp[i][j] = INF;
            }
        }
        dp[0][a[0]] = 0;
        if (a[0] != 0) dp[0][0] = 1;

        for (int i = 0; i < n-1; ++i) {
            for (int j = 0; j <= 8191; ++j) {
                if (dp[i][j] != INF) {
                    dp[i][0] = min(dp[i][0], dp[i][j]+1);
                    dp[i+1][a[i+1]^j] = min(dp[i+1][a[i+1]^j], dp[i][j]+1);
                }
            }
            dp[i+1][0] = min(dp[i+1][0], dp[i][0]+1);
            dp[i+1][a[i+1]] = min(dp[i+1][a[i+1]], dp[i][0]);
        }

        cout<<dp[n-1][0]<<endl;
    }

    return 0;
}