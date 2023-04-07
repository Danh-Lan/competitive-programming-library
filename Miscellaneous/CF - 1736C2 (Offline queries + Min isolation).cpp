// the solution try to isolate dp[i-1]+1 and a[i] from the eq
// dp[i] = min(dp[i-1]+1, a[i]) for easier calculation

#include<bits/stdc++.h>
 
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
    for (int test = 1; test <= tt; test++) {
        int n; cin >> n;
        
        vector<long long> track(n+5, 0LL), sum(n+5, 0LL);

        vector<pair<int,pair<int, int>>> traverse;
        vector<long long> pref(n+5, 0LL);
        vector<int> dp(n+5, 0);
        
        for (int i = 1; i <= n; ++i) {
            int x; cin >> x;
            sum[i] = sum[i-1] + i; 
            traverse.push_back({x-i, {i, 0}});
            dp[i] = min(dp[i-1]+1, x);
            pref[i] = pref[i-1] + dp[i];
        }

        int q; cin >> q;
        vector<long long> ans(q+5, 0LL);
        for (int i = 1; i <= q; ++i) {
            int p, x; cin >> p >> x;
            x = min(dp[p-1]+1, x);
            traverse.push_back({x-p, {p, i}});
        }

        sort(traverse.begin(), traverse.end());
        set<int> found; found.insert(n+1);
        for (auto it : traverse) {
            int query = it.second.second;
            int val = it.first; // a[i]-i || dp[i]-i
            int pos = it.second.first;
            if (query > 0) {
                int r = *found.upper_bound(pos);
                ans[query] = pref[pos-1] + track[r] + sum[r-pos] + 1LL*(val+pos-1)*(r-pos);
            } else {
                int r = *found.lower_bound(pos);
                found.insert(pos);
                // not sum[r-pos-1] to avoid out of bound
                track[pos] = track[r] + sum[r-pos] + 1LL*(val+pos-1)*(r-pos);
            }
        }

        for (int i = 1; i <= q; ++i) {
            cout << ans[i] << '\n';
        }
    }
 
    return 0;
}