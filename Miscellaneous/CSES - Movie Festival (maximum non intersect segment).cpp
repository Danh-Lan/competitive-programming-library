#include<bits/stdc++.h>
 
using namespace std;

void solve() {
    int n;
    cin >> n;
    pair<int, int> p[n];
    for (int i = 0; i < n; ++i) {
        cin >> p[i].second >> p[i].first;

    }

    sort(p, p+n);
    int cur = p[0].first;
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        if (p[i].second >= cur) {
            cur = p[i].first;
            ans++;
        }
    }

    cout << ans << '\n';
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
