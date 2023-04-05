#include <bits/stdc++.h>

using namespace std;

int N = 1001;
vector<int> dist(N, 1e9);

void setup() {
    dist[0] = dist[1] = 0;
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (i+i/j < N) {
                dist[i+i/j] = min(dist[i+i/j], dist[i]+1);                
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    setup();

    int tt = 1;
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n, k; cin >> n >> k;
        int a[n+1], coin[n+1];
        int moves = 0, sum = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            moves += dist[a[i]];
            a[i] = dist[a[i]];
        }

        for (int i = 1; i <= n; ++i) {
            cin >> coin[i];
            sum += coin[i];
        }

        if (k >= moves) {
            cout << sum << '\n';
            continue;
        }

        vector<vector<int>> dp(n+1, vector<int>(k+1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                dp[i][j] = max(dp[i][j], dp[i-1][j]);
                if (j - a[i] >= 0) {
                    dp[i][j] = max(dp[i][j], dp[i-1][j-a[i]] + coin[i]);
                } 
            }
        }

        int ans = 0;
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                ans = max(ans, dp[i][j]);
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
