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
    //cin>>tt;
    //for (int test = 1; test <= tt; test++) {

    //}

    int n, k; cin>>n>>k;
    string s, t; cin>>s>>t;

    if (t[0] == t[1]) {
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == t[0]) cnt++;
        }

        if (cnt + k <= n) cnt += k;
        else cnt = n;

        int ans = cnt*(cnt-1)/2;
        cout<<ans<<"\n";
        return 0;
    }


    const int INF = -1e9;
    // reach s[i], use j turn, has l t[0]
    int dp[n+1][n+1][n+1];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int l = 0; l <= n; ++l) {
                dp[i][j][l] = INF;
            }
        }
    }
    dp[0][0][0] = 0LL;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            for (int l = 0; l <= i; ++l) {
                if (s[i] == t[0]) {
                    dp[i+1][j][l+1] = max(dp[i+1][j][l+1], dp[i][j][l]);
                    dp[i+1][j+1][l] = max(dp[i+1][j+1][l], l + dp[i][j][l]);
                } 
                if (s[i] == t[1]) {
                    dp[i+1][j+1][l+1] = max(dp[i+1][j+1][l+1], dp[i][j][l]);
                    dp[i+1][j][l] = max(dp[i+1][j][l], l + dp[i][j][l]);
                } 
                if (s[i] != t[0] && s[i] != t[1]) {
                    dp[i+1][j][l] = max(dp[i+1][j][l], dp[i][j][l]);
                    dp[i+1][j+1][l+1] = max(dp[i+1][j+1][l+1], dp[i][j][l]);
                    dp[i+1][j+1][l] = max(dp[i+1][j+1][l], l + dp[i][j][l]);
                }
            }
        }
    }

    int ans = 0LL;
    for (int j = 0; j <= k; ++j) {
        for (int l = 0; l <= n; ++l) {
            ans = max(ans, dp[n][j][l]);
        }
    }

    cout<<ans<<"\n";

    return 0;
}