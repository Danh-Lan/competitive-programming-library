#include<bits/stdc++.h>
 
using namespace std;

const int MOD = 1e9 + 7;

map<long long, long long> m;

// Honsberger's Identity : ∀m,n∈Z>0:Fm+n=Fm−1Fn+FmFn+1
// take m = n, we have : F2n = Fn-1Fn + FnFn+1
// F_2n = Fn-1Fn+Fn(Fn-1+Fn) = Fn(2*Fn-1+Fn), avoid Fn+1 to save memory
// take m = n+1, we have : F2n+1=Fn^2+Fn+1^2
long long fibo(long long n) {
    if (m.count(n)) return m[n];
    if (n == 0) return 0;
    if (n == 1 || n == 2) return 1;

    if (n % 2 == 1) {
        long long k = n/2;
        long long res1 = fibo(k), res2 = fibo(k+1);

        return m[n] = (res1*res1 % MOD + res2*res2 % MOD) % MOD;
    } else {
        long long k = n/2;
        long long res1 = fibo(k), res2 = fibo(k-1);

        return m[n] = ((2LL*res2+res1) % MOD * res1) % MOD;
    }
}

void solve() {
    long long n;
    cin >> n;

    cout << fibo(n) << endl;
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
