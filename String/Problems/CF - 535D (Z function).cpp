#include <bits/stdc++.h>

using namespace std;

int MOD = 1e9 + 7;

// An element Z[i] of Z array stores length of the longest substring
// starting from str[i] which is also a prefix of str[0..n-1].
// The first entry of Z array is meaning less as complete string is always prefix of itself.
vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        // value of z[i] in [l, r],
        // prefix of i doesn't go outside of r a.k.a i+z[i] < r
        if (i <= r) {
            z[i] = min (r - i + 1, z[i - l]);
        }

        // search for [l, r]
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }

        // prefix of i goes outside of r,
        // need to create new [l, r]
        if (i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}

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
        int n, m; cin >> n >> m;
        string s; cin >> s;
        int l = 0, r = 0;
        vector<int> pref(n), z(s.size()), q(m);
        z = z_function(s);
        z[0] = s.size();
        for (int i = 0; i < m; i++) {
            cin >> q[i];
            q[i]--;
            pref[q[i]]++;
            if (q[i] + s.size() < n) pref[q[i] + s.size()]--;
        }
        for (int i = 1; i < m; i++) {
            int len = q[i - 1] + s.size() - q[i];
            if (len <= 0) continue;
            if (z[s.size() - len] < len) {
                cout << "0\n";
                return 0;
            }
        }
        long long ans = 1;
        for (int i = 0; i < n; i++) {
            if (i) pref[i] += pref[i - 1];
            if (pref[i] == 0) ans = 1LL * ans * 26 % MOD;
        }
        cout << ans << '\n';
    }

    return 0;
}