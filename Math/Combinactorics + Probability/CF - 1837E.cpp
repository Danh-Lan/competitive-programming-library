#include<bits/stdc++.h>
 
using namespace std;

const int MOD = 998244353;
const int K = 19;
vector<long long> fact((1 << K) + 1);
vector<int> powTwo((1 << K) + 1);

void precal() {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= (1 << K); ++i) {
        fact[i] = (fact[i-1] * i) % MOD;
    }

    powTwo[0] = 1;
    for (int i = 1; i <= (1 << K); ++i) {
        powTwo[i] = (powTwo[i-1] * 2) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout); 
    #endif

    precal();

    int tt = 1;
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int k;
        cin >> k;
        int n = (1 << k);
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        long long ans = 1LL;
        while (n > 1) {
            vector<int> newA(n/2);
            vector<int> pos;
            int ones = 0, twos = 0;
            for (int i = 0; i < n; i += 2) {
                // 2 weak can't face each other
                if (a[i] > n/2 && a[i+1] > n/2) {
                    cout << 0 << '\n';
                    return 0;
                }
                
                // 2 strong can't face each other
                if (a[i] <= n/2 && a[i] != -1 && a[i+1] <= n/2 && a[i+1] != -1) {
                    cout << 0 << '\n';
                    return 0;
                }

                if (a[i] == -1 && a[i+1] == -1) {
                    twos++;
                    newA[i/2] = -1;
                } else if (a[i] == -1) {
                    if (a[i+1] <= n/2) {
                        ones++;
                        newA[i/2] = a[i+1];
                    } else {
                        newA[i/2] = -1;
                    }
                } else if (a[i+1] == -1) {
                    if (a[i] <= n/2) {
                        ones++;
                        newA[i/2] = a[i];
                    } else {
                        newA[i/2] = -1;
                    }
                } else {
                    newA[i/2] = min(a[i], a[i+1]);
                }
            }

            ans = ((ans * fact[twos+ones]) % MOD * powTwo[twos]) % MOD;

            n /= 2;
            a = newA;
        }

        cout << ans << '\n';
    }

    return 0;
}