#include<bits/stdc++.h>
 
using namespace std;

vector<int> build_lps(string p) {
    int sz = p.size();
    vector<int> lps;
    lps.assign(sz, 0);
    int j = 0;
    lps[0] = 0;
    for (int i = 1; i < sz; i++) {
        while (j >= 0 && p[i] != p[j]) {
            if (j >= 1) j = lps[j - 1];
            else j = -1;
        }
        j++;
        lps[i] = j;
    }
    return lps;
}

int kmp(vector<int> lps, string s, string p) {
    int psz = p.size(), sz = s.size();
    int j = 0;
    int cnt = 0;
    for (int i = 0; i < sz; i++) {
        while (j >= 0 && p[j] != s[i]) {
            if (j >= 1) j = lps[j - 1];
            else j = -1;
        }
        j++;
        if (j == psz) {
            //j = 0;
            ++cnt;
        }
        // after each loop we have j=longest common suffix of s[0..i] which is also prefix of p
    }

    return cnt;
}

void solve() {
    string s, t;
    cin >> s >> t;
    vector<int> lps = build_lps(t);
    cout << kmp(lps, s, t) << '\n';
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

// CSES - String Matching