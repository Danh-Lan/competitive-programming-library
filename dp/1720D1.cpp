#include <bits/stdc++.h>

using namespace std;

const int RANGE = 256;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tt = 1;
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin >> n;
        int a[n];
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        int ans = 0;
        for (int i = 0; i < n; i += RANGE) {
            vector<vector<int>> graph(RANGE, vector<int>());
            for (int j = i; j < min(n, i+RANGE); ++j) {
                for (int k = j+1; k < min(n, i+RANGE); ++k) {
                    int val1 = a[j]^k, val2 = a[k]^j;
                    if (val1 < val2) {
                        graph[j-i].push_back(k-i);
                    }
                }
            }

            vector<int> dp(RANGE, 1);
            for (int j = 0; j < RANGE; ++j) {
                for (int k : graph[j]) {
                    dp[k] = max(dp[k], dp[j]+1);
                }
            }
            ans = max(ans, *max_element(dp.begin(), dp.end()));
        }

        cout << ans << '\n';
    }

    return 0;
}