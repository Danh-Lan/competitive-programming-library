#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9+7;

vector<bool> prime(1001, true);
void sieve() {
    prime[0] = prime[1] = false;
    for (int i = 0; i < 1001; ++i) {
        if (prime[i] == true) {
            for (int j = 2*i; j < 1001; j += i) {
                prime[j] = false;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    int tt = 1; 
    //cin>>tt;
    for (int test = 1; test <= tt; test++) {
        sieve();
        int n; cin>>n;
        vector<int> div;
        for (int i = 2; i <= n; ++i) {
            if (prime[i]) {
                long long cnt = 0;
                long long val = i;
                while (val <= n) {
                    cnt += n/val;
                    val = val*i;
                }
                div.push_back(cnt);
            }
        }

        long long ans = 1LL;
        for (int i = 0; i < div.size(); ++i) {
            ans = (ans*(div[i]+1))%MOD;
        }

        cout<<ans<<endl;

    }

    return 0;
}