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
    cin>>tt;
    for (int test = 1; test <= tt; test++) {
        int n, k; cin>>n>>k;
        int a[n+1];
        for (int i = 1; i <= n; ++i) {
            cin>>a[i];
        }

        // dp[i][j] (j <= i) : reach a[i], delete j elements, = number of fixed points 
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        dp[0][0] = 0;
        int ans = -1;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (i+1-a[i+1] == j) {
                    dp[i+1][j] = max(dp[i+1][j], dp[i][j] + 1);
                    if (dp[i+1][j] >= k) {
                        if (ans == -1) ans = j;
                        else ans = min(ans, j);
                    }
                } else dp[i+1][j] = max(dp[i+1][j], dp[i][j]);

                dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]);
            }
        }
        
        cout<<ans<<"\n";
    }

    return 0;
}