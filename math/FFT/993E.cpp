#include <bits/stdc++.h>

using namespace std;

struct FFT {
    const double PI = acos(-1);
    typedef complex<double> base;

    void fft(vector<base> & a, bool inv) {
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
        vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
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
        for (int i = 0; i < n; ++i) {
            ret[i] = (long long) (fa[i].real() + .5);
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
        int n, x; cin >> n >> x;
        vector<long long> a(n + 1, 0), b(n + 1, 0), c(n + 1, 0);
        vector<long long> ans(n+1);
        int cnt = 0;
        a[0] = 1; b[n] = 1;
        // a[i] = number of prefix that have i number < k
        // b[i] = same but suffix
        long long z = 0;
        for (int i = 1; i <= n; i++) {
            int k; cin >> k;
            if (k < x) cnt++;
            a[cnt]++; b[-cnt + n]++;

            // for ans[0] only
            z += c[cnt] + !cnt; c[cnt]++; 
        }

        FFT fft;
        vector<long long> res = fft.multiply(a, b);

        for (int i = n + 1; i < res.size(); i++) {
            ans[i - n] += res[i];
        }
        ans[0] = z;
        for (int i = 0; i <= n; i++) {
            cout << ans[i] << ' ';
        } cout << '\n';
    }

    return 0;
}