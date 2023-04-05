#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

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
        int a, n, m;
        cin >> a >> n >> m;
        vector<bool> rain(a+1, false);
        for (int i = 0; i < n; ++i) {
            int l, r; 
            cin >> l >> r;

            for (int j = l; j < r; ++j) {
                rain[j] = true;
            }
        }

        vector<pair<int, int>> umb(a+1, make_pair(INF, -1));
        vector<int> costs(m+1);
        for (int i = 0; i < m; ++i) {
            int pos, weight;
            cin >> pos >> weight;
            costs[i+1] = weight;
            umb[pos] = min(umb[pos], {weight, i+1});
        }

        vector<vector<int>> dp(a+1, vector<int>(m+1, INF));
        dp[0][0] = 0;

        for (int i = 0; i < a; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (dp[i][j] == INF) continue;

                if (!rain[i]) {
                    dp[i+1][0] = min(dp[i+1][0], dp[i][j]);
                }

                if (j > 0) {
                    dp[i+1][j] = min(dp[i+1][j], dp[i][j] + costs[j]);
                }

                if (umb[i].second != -1) {
                    dp[i+1][umb[i].second] = min(dp[i+1][umb[i].second], dp[i][j] + umb[i].first);
                }
            }
        }

        int ans = INF;
        for (int j = 0; j <= m; ++j) {
            ans = min(ans, dp[a][j]);
        }
        if (ans == INF) ans = -1;
        cout << ans << '\n';
    }

    return 0;
}