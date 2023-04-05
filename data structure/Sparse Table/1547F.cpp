#include <bits/stdc++.h>

using namespace std;

const int N = 4e5 + 18;
vector<int> lg(N);

void setup() {
    for (int i = 2; i < N; i++) {
        lg[i] = lg[i-1];
        if (i % 2 == 0) lg[i] = lg[i/2] + 1;
    }
}

void build(vector<vector<int>>& sparse, int n) {
    for (int j = 1; j <= 19; j++) {
        for (int i = 1; i + (1<<j) - 1 <= n; i++) {
            sparse[i][j] = __gcd(sparse[i][j-1], sparse[i+(1<<(j-1))][j-1]);
        }
    }
}

int getGCD(vector<vector<int>>& sparse, int l, int r) {
    int k = lg[r-l+1];
    return __gcd(sparse[l][k], sparse[r-(1<<k)+1][k]);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    ios::sync_with_stdio(false);
    cin.tie(0);

    setup();

    int tt = 1;
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n; cin >> n;
        int a[n];
        int gcd;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (i == 0) gcd = a[i];
            else gcd = __gcd(gcd, a[i]);
        }

        vector<vector<int>> sparse(2*n+1, vector<int>(20));
        for (int i = 0; i < n; ++i) {
            a[i] /= gcd;
            sparse[i+1][0] = a[i];
            sparse[i+n+1][0] = a[i];
        }
        build(sparse, 2*n);

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int l = 0, r = n-1;
            while (l < r) {
                int m = (l+r)/2;
                int gcd = getGCD(sparse, i, i+m);
                if (gcd == 1) {
                    r = m;
                } else {
                    l = m+1;
                }
            }

            ans = max(ans, l);
        }

        cout << ans << '\n';
    }

    return 0;
}