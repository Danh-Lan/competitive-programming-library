#include <bits/stdc++.h>

using namespace std;

struct FFT {
    const double PI = 3.141592653589793;
    typedef complex<double> base;

    void fft( vector < base > & a, bool inv ) {
        int n = (int) a.size();
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = ( n >> 1 );
            for (; j >= bit; bit >>= 1) {
                j -= bit;
            }

            j += bit;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2. * PI / len * (inv ? -1 : 1);
            base wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                base w(1);
                long long len2 = len >> 1;
                for (int j = 0; j < len2; ++j) {
                    base u = a[i+j], v = a[i+j+len2] * w;
                    a[i+j] = u + v;
                    a[i+j+len2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (inv) {
            for (int i = 0; i < n; ++i) {
                a[i] /= n;
            }
        }
    }
    vector<long long> multiply(vector<long long> a, vector<long long> b) {
        vector < base > fa(a.begin(), a.end()), fb(b.begin(), b.end());
        long long n = 1;
        while (n < max((long long)a.size(), (long long)b.size())) {
            n <<= 1;
        }
        n <<= 1;
        fa.resize(n);
        fb.resize(n);
        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; ++i) {
            fa[i] *= fb[i];
        }
        fft(fa, true);
        vector<long long> ret(n, 0LL);
        for (int i = 0; i < n; ++i ) {
            ret[i] = (long long) (fa[i].real() + .5);
            if (ret[i]) {
                ret[i] = 1;
            }
        }
    
        while ((int)ret.size() > 1 && ret.back() == 0) ret.pop_back();

        return ret;
    }
};

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
        int n, k; cin >> n >> k;
        int a[n];
        int mx = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            mx = max(mx, a[i]);
        }

        vector<long long> poly(mx+1, 0LL);
        for (int i = 0; i < n; ++i) {
            poly[a[i]] = 1;
        }

        long long cnt = 0LL;
        vector<long long> ans;
        while (k > 0) {
            FFT fft;
            if (k % 2 != 0) {
                ++cnt;
                if (cnt == 1) ans = poly;
                else ans = fft.multiply(ans, poly);
            }

            k /= 2;
            poly = fft.multiply(poly, poly);
        }

        for (int i = 0; i < ans.size(); ++i) {
            if (ans[i] > 0) cout << i << ' ';
        } cout << '\n';
    }

    return 0;
}

// https://codeforces.com/contest/632/problem/E