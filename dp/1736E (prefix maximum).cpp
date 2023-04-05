// thanks for the editorial
// nice technique

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
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin >> n;
        int a[n+1];
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        // dp[i][j][k] : turn i, a[i] taken value of a[j], k swap has been used
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(n+1, vector<int>(n+1, 0)));
        vector<vector<int>> pref(n+1, vector<int>(n+1, 0));
        int ans = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                for (int k = 0; k <= i; ++k) {
                    if (k > 0 && i+k >= j) {
                        // a[i] can't taken value from a[j] if j is too far away
                        // ex : a[2] can have at most the value of a[4]
                        // impossible to swap a[5] to a[2]
                        dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-1] + a[j]);
                    }

                    if (j >= i) {
                        int move = j-i;
                        if (move > k) continue;

                        dp[i][j][k] = max(dp[i][j][k], pref[j-1][k-move] + a[j]);
                        // pref[j-1][k-move] = max(dp[i][l][k-move], l from 1 to j-1)
                    }
                }
            }

            // udpate pref value
            for (int j = 1; j <= n; ++j) {
                for (int k = 0; k <= i; ++k) {
                    pref[j][k] = max(pref[j][k], dp[i][j][k]);
                }
            }

            for (int j = 1; j <= n; ++j) {
                for (int k = 0; k <= i; ++k) {
                    pref[j][k] = max(pref[j][k], pref[j-1][k]);
                    ans = max(ans, pref[j][k]);
                }
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
