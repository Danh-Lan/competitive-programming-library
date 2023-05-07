// https://www.codechef.com/problems/ABCD0825

#include <bits/stdc++.h>
using namespace std;
int main(){
    int T, Q;
    cin >> T >> Q;
    if (Q == 200) {
        for (int i = 0; i < T; i++) {
            // divide and conquer, each while use at most log2(10^9)+1 = 30 iterations
            // tv1 will be the smallest s.t -10^7*A+tv1*D > 0, or tv1 approx 10^7*A/D
            // at minimum -10^7 can be replaced by -10^2, and tv1 = 10^4 fv1 = -10^4
            int tv1 = 1000000000, fv1 = -1000000000;
            while (tv1 - fv1 > 1) {
                int mid = (tv1 + fv1) / 2;
                cout << "?" << ' ' << -10000000 << ' ' << 0 << ' ' << 0 << ' ' << mid << endl;
                char c;
                cin >> c;
                if (c == '>' || c == '=') {
                    tv1 = mid;
                } else {
                    fv1 = mid;
                }
            }
            int tv2 = 1000000000, fv2 = -1000000000;
            while (tv2 - fv2 > 1) {
                int mid = (tv2 + fv2) / 2;
                cout << "?" << ' ' << 0 << ' ' << mid << ' ' << -10000000 << ' ' << 0 << endl;
                char c;
                cin >> c;
                if (c == '>' || c == '=') {
                    tv2 = mid;
                } else {
                    fv2 = mid;
                }
            }
            if (tv1 > tv2) {
                cout << "! >" << endl;
            } else if (tv1 < tv2){
                cout << "! <" << endl;
            } else {
                cout << "! =" << endl;
            }
        }
    } else {
        for (int i = 0; i < T; i++) {
            long long Xx = 1, Xy = 0, Yx = 0, Yy = 1;
            int ans = 0;
            int cnt = 0;
            while (true) {
                int U = 1;
                bool eq = false;
                while (true) { 
                    // after the first iteration of this while, only 2 cases left :
                    // 1 : (A - 2^m*D < 0 and C - 2^m*B < 0) ( 2^m = U ; m in [1;29])
                    // 2 : (A - 2^29*D > 0 and (C - 2^29*B > 0 and U = 2^30 > 10^9)
                    // the next while solve 2nd case 
                    // 2nd iteration : Xx Xy Yx Yy = 0 1 1 -vt ; deal 1st case
                    // xc = -2^m yc = 1+2^m*vt 
                    // note that vt is the closest to A/D in [2^(m-1);2^m] in the last iteration
                    // -2^m*A+(1+2^m*vt)D = 2^m*D*(1/(2^m) + vt - A/D) same sign as (1/(2^m)+vt-A/D)
                    // so the next iterations will exploit A/D and C/B much more than the last one
                    // But don't get why it will use less than 200 queries
                    long long xc = Xx - Yx * U, yc = Xy - Yy * U;
                    if (abs(xc) > 1000000000 || abs(yc) > 1000000000) {
                        break;
                    }
                    cout << "? " << xc << ' ' << 0 << ' ' << 0 << ' ' << yc << endl;
                    char c1;
                    cin >> c1;
                    cout << "? " << 0 << ' ' << yc << ' ' << xc << ' ' << 0 << endl;
                    char c2;
                    cin >> c2;
                    if (c1 != c2) {
                        if (c1 == '>') {
                            ans = 1;
                        } else if (c1 == '=' && c2 == '<') {
                            ans = 1;
                        } else {
                            ans = -1;
                        }
                        if (cnt % 2 == 1) {
                            ans *= -1;
                        }
                        break;
                    } else if (c1 == '=') {
                        eq = true;
                        break;
                    } else if (c1 == '>') {
                        U *= 2;
                    } else { // left the case c1 and c2 == '<' to deal later
                        break;
                    }
                }
                if (ans != 0) {
                    break;
                }
                if (eq) {
                    break;
                }
                int tv = U / 2, fv = U;
                while (fv - tv > 1) { 
                    // first iteration
                    // 2nd case (A - 2^29*D > 0 and (C - 2^29*B > 0 and U = 2^30 > 10^9)
                    // this while use divide and conquer to check for a number p in [2^29;10^9] s.t
                    // A - p*D and C - p*B have diff sign (p must exist because of the range of A B C D)
                    // 1st case : divide and conquer in [2^(m-1);2^m]
                    int mid = (tv + fv) / 2;
                    long long xc = Xx - Yx * mid, yc = Xy - Yy * mid;
                    if (abs(xc) > 1000000000 || abs(yc) > 1000000000) {
                        fv = mid;
                        continue;
                    }
                    cout << "? " << xc << ' ' << 0 << ' ' << 0 << ' ' << yc << endl;
                    char c1;
                    cin >> c1;
                    cout << "? " << 0 << ' ' << yc << ' ' << xc << ' ' << 0 << endl;
                    char c2;
                    cin >> c2;
                    if (c1 != c2) {
                        if (c1 == '>') {
                            ans = 1;
                        } else if (c1 == '=' && c2 == '<') {
                            ans = 1;
                        } else {
                            ans = -1;
                        }
                    if (cnt % 2 == 1) {
                        ans *= -1;
                    }
                    break;
                    } else if (c1 == '=') {
                        eq = true;
                        break;
                    } else if (c1 == '>') {
                        tv = mid;
                    } else {
                        fv = mid;
                    }
                }   
                if (ans != 0) {
                    break;
                }
                if (eq) {
                    break;
                }
                int q = tv;
                long long Xx2 = Yx, Xy2 = Yy;
                long long Yx2 = Xx - q * Yx, Yy2 = Xy - q * Yy;
                Xx = Xx2;
                Xy = Xy2;
                Yx = Yx2;
                Yy = Yy2;
                cnt++;
            }
            if (ans == 1) {
                cout << "! >" << endl;
            } else if (ans == -1){
                cout << "! <" << endl;
            } else {
                cout << "! =" << endl;
            }
        }
    }
}