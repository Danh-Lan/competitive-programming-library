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
    //cin >> tt;
    for (int test = 0; test < tt; ++test) {
        int n; cin >> n;
        vector<pair<int,int>> a(n);
        for (int i = 0; i < n; ++i) {
            int num; cin>>num;
            a[i] = {num, i};
        }
        sort(a.begin(), a.end());
        
        long long dp[n];
        int group[n];

        dp[0] = dp[1] = 0;
        dp[2] = a[2].first-a[0].first; 
        dp[3] = a[3].first-a[0].first; 
        dp[4] = a[4].first-a[0].first;
        group[0] = group[1] = 0;
        group[2] = 3; group[3] = 4; group[4] = 5;

        for (int i = 5; i < n; ++i) {
            int opt = 3;
            dp[i] = dp[i-3] + a[i].first-a[i-2].first;

            if (i >= 6 && dp[i] > dp[i-4] + a[i].first-a[i-3].first) {
                opt = 4;
                dp[i] = dp[i-4] + a[i].first-a[i-3].first;
            }
            if (i >= 7 && dp[i] > dp[i-5] + a[i].first-a[i-4].first) {
                opt = 5;
                dp[i] = dp[i-5] + a[i].first-a[i-4].first;
            }
            group[i] = opt;
        }

        int ans[n] = {0};
        int cnt = 0;
        for (int i = n-1; i >= 0; --i) {
            ++cnt;
            int type = group[i];
            for (int j = i; j > i-type; --j) {
                ans[a[j].second] = cnt;
            } 
            i -= type-1;
        }

        cout << dp[n-1] << " " << cnt << endl;
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << " ";
        } cout << endl;

    }
 
    return 0;
}