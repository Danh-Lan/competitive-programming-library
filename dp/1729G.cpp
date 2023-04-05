#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int tt = 1; 
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        string s, t;
        cin >> s >> t;

        s = '#' + s;
        int n = s.length(), m = t.length();
        vector<int> move(n+1, 1000);
        vector<long long> cnt(n+1, 1);
        move[0] = 0; cnt[0] = 1;
        for (int i = 1; i <= n; ++i) {
            if (i-m+1 >= 1 && s.substr(i-m+1, m) == t) {
                cnt[i] = 0;
                for (int j = i-m+1; j <= i; ++j) {
                    if (j-m+1 >= 1 && s.substr(j-m+1, m) == t) {
                        move[i] = min(move[i], move[j-m] + 1);
                    }
                }

                for (int j = i-m+1; j <= i; ++j) {
                    if (j-m+1 >= 1 && s.substr(j-m+1, m) == t && move[i] == move[j-m]+1) {
                        cnt[i] = (cnt[i] + cnt[j-m]) % MOD;
                    }
                }
            } else {
                move[i] = move[i-1];
                cnt[i] = cnt[i-1];
            }
        }


        cout << move[n] << ' ' << cnt[n] << '\n';
    }

    return 0;
}