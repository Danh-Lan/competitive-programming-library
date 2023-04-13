#include<bits/stdc++.h>
 
using namespace std;

const int ALPHABET = 26;

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
        string s; 
        cin >> s;
        int n = s.size();
        vector<int> p = build_lps(s);

        vector<vector<int>> A(n, vector<int>(ALPHABET));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < ALPHABET; ++j) {
                if (i > 0 && j != s[i] - 'a') {
                    A[i][j] = A[p[i - 1]][j];
                } else {
                    A[i][j] = i + (j == s[i] - 'a');
                }
            }
        }

        int q;
        cin >> q;
        vector<vector<int>> ans(q);
        for (int query = 0; query < q; ++query) {
            string t;
            cin >> t;
            int m = t.size();
            s += t;

            for (int i = n; i < n + m; ++i) {
                A.push_back(vector<int>(ALPHABET));
                for (int j = 0; j < ALPHABET; ++j) {
                    if (j != s[i] - 'a')
                        A[i][j] = A[p[i - 1]][j];
                    else
                        A[i][j] = i + (j == s[i] - 'a');
                }
                p.push_back(A[p[i - 1]][s[i] - 'a']);
                ans[query].push_back(p[i]);
            }
            for (int i = 0; i < m; ++i) {
                p.pop_back();
                s.pop_back();
                A.pop_back();
            }
        }

        for (auto &it : ans) {
            for (int x : it) {
                cout << x << ' ';
            } cout << '\n';
        }
    }
 
    return 0;
}

// https://codeforces.com/contest/1721/problem/E