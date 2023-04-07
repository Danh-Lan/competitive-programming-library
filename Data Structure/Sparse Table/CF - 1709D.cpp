#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 18;
int lg[N], sparse[N][20];

void setup() {
    for (int i = 2; i < N; i++) {
        lg[i] = lg[i-1];
        if (i % 2 == 0) lg[i] = lg[i/2] + 1;
    }
}

void build(int n) {
    for (int j = 1; j <= 18; j++) {
        for (int i = 1; i + (1<<j) - 1 <= n; i++) { 
            sparse[i][j] = max(sparse[i][j-1], sparse[i+(1<<(j-1))][j-1]);
        }
    }
}

int getMax(int l, int r) {
    int k = lg[r-l+1];
    return max(sparse[l][k], sparse[r-(1<<k)+1][k]);
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
    //cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n, m; cin >> n >> m;
        for (int i = 1; i <= m; ++i) {
            int x; cin >> x;
            sparse[i][0] = x;      
        }
        build(m);
        int q; cin >> q;
        for (int qq = 0; qq < q; ++qq) {
            int x[2], y[2], k;
            cin >> x[0] >> y[0] >> x[1] >> y[1] >> k;
            if (y[0] > y[1]) {
                swap(x[0], x[1]);
                swap(y[0], y[1]);
            }
            if ( (x[1]-x[0]) % k != 0 || (y[1]-y[0]) % k != 0) {
                cout << "NO\n";
                continue;
            }

            int mx = getMax(y[0], y[1]);
            if (n-(n-x[0])%k > mx) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}