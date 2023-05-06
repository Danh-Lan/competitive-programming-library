#include<bits/stdc++.h>
 
using namespace std;
 
void solve() {
    int n;
    cin >> n;
 
    int a[n];
    long long sum = 0LL;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
 
    // dp[l][r] = score1 - score2 on [l,r], player1 go first
    // minimax idea : 1 maximize, 2 minimize
    // dp[l][r] if 2 go first --> -(score1-score2)
    vector<vector<long long>> dp(n,vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = a[i];
    }
 
    for (int d = 1; d < n; ++d) {
        for (int l = 0; l <= n-1-d; ++l) {
            int r = l+d;
 
            dp[l][r] = max(a[l] - dp[l+1][r], a[r] - dp[l][r-1]);
        }
    }
 
    cout << (sum + dp[0][n-1])/2 << '\n';
 
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
 
    int tt = 1; 
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        solve();
    }
 
    return 0;
}