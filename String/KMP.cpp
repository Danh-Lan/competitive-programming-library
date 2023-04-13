#include <bits/stdc++.h>

using namespace std;

// returns the longest proper prefix array of pattern p
// where lps[i]=longest proper prefix which is also suffix of p[0...i]
vector<int> build_lps(vector<int> p) {
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

int kmp(vector<int> lps, vector<int> s, vector<int> p) {
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
            j = 0;
            ++cnt;
        }
        // after each loop we have j=longest common suffix of s[0..i] which is also prefix of p
    }

    return cnt;
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
        int n; cin >> n;
        string s[n];
        map<string, int> hash;
        int cur = 0;
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
            if (hash.find(s[i]) == hash.end()) {
                cur++;
                hash[s[i]] = cur;
            }
        }

        vector<int> reduce;
        reduce.push_back(-1);
        for (int i = 0; i < n; ++i) {
            reduce.push_back(hash[s[i]]);
        }
        vector<int> pref(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            pref[i] = pref[i-1] + s[i-1].length();
        }

        int ans = pref[n] + n-1;
        for (int i = 1; i <= n; ++i) {
            vector<int> pattern;
            for (int leng = 1; leng <= (n+1-i)/2; ++leng) {
                pattern.push_back(reduce[i+leng-1]);
                vector<int> lps = build_lps(pattern);
                int cnt = kmp(lps, reduce, pattern);
                if (cnt == 1) continue;

                ans = min(ans, pref[n] + n-1 - cnt*(pref[i+leng-1]-pref[i-1]-1));
            }
        }

        cout << ans << endl;
    }

    return 0;
}

// 1003F
