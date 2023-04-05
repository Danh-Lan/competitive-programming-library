// implementation trick :
// because parent[i] < i
// insteaed of a queue, we can simply iterate from n-1 to 0

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
        
        int parent[n];
        parent[0] = 0;
        for (int i = 1; i < n; ++i) {
            cin >> parent[i];
            parent[i]--;
        }

        vector<int> dp(n, 0), dist(n, 1);
        for (int i = n-1; i >= 0; --i) {
            dp[i] = max(dp[i], dist[i]);
            if (i != 0) {
                dp[parent[i]] += dp[i];
                dist[parent[i]] = max(dist[parent[i]], dist[i]+1);
            }
        }

        cout << dp[0] << '\n';

    }

    return 0;
}