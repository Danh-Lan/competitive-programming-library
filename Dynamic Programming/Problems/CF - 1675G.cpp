// editorial solution
// dp[i][last][sum] = min(dp[i−1][last+j][sum−last] + add)
// add is calculate by 2 prefix sums on n and on m (a and pancakes)
// calculate dp using suffix minimum

#include<bits/stdc++.h>
 
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout); 
    #endif

    int tt = 1; 
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n), pancakes(1);

        for (int &e: a) cin >> e;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < a[i]; ++j) {
                pancakes.emplace_back(i);
                int c = pancakes.size();
                pancakes[c - 1] += pancakes[c - 2];
            }
            if (i > 0) a[i] += a[i - 1];
        }

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m + 1, vector<int>(m + 1, INF)));
        for (int j = 0; j <= m; j++) {
            if (a[0] >= j) dp[0][j][j] = a[0] - j; //moved right
            else dp[0][j][j] = pancakes[j]; //moved from right
        }
        for (int j = m - 1; j >= 0; --j) {
            for (int k = j; k <= m; ++k) {
                dp[0][j][k] = min(dp[0][j][k], dp[0][j + 1][k]);
            }
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= m; ++j) {
                for (int k = j; k <= m; ++k) {
                    int add = 0;
                    if (a[i] >= k) add = a[i] - k; //moved to i + 1
                    else {
                        int lend = min(j, k - a[i]);
                        add = pancakes[k] - pancakes[k - lend] - i * (lend);//moved from greater i
                    }
                    dp[i][j][k] = dp[i - 1][j][k - j] + add;
                }
            }

            for (int j = m - 1; j >= 0; --j) {
                for (int k = (i + 1) * j; k <= m; ++k) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i][j + 1][k]);
                }
            }
        }
        cout << dp[n-1][0][m] << '\n';
    }

    return 0;
}