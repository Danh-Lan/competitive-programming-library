// merge interval isn't need but keep as template

#include<bits/stdc++.h>
 
using namespace std;

struct Interval {
    int b, e;
};

vector<Interval> mergeIntervals(vector<Interval> intervals, int n) {
    sort(intervals.begin(), intervals.end(), [&] (Interval i1, Interval i2) {
        return (i1.b < i2.b);
    });
 
    int index = 0;
    for (int i = 1; i < n; i++) {
        if (intervals[index].e >= intervals[i].b - 1) {
            intervals[index].e = max(intervals[index].e, intervals[i].e);
        }
        else {
            index++;
            intervals[index] = intervals[i];
        }
    }

    return vector<Interval>(intervals.begin(), intervals.begin() + index+1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout); 
    #endif

    int tt = 1; 
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n, k;
        cin >> n >> k;

        vector<Interval> intervals(n);
        for (int i = 0; i < n; ++i) {
            cin >> intervals[i].b;
        }
        for (int i = 0; i < n; ++i) {
            cin >> intervals[i].e;
        }

        intervals = mergeIntervals(intervals, n);
        int sz = intervals.size();
        int pos = -1;
        long long sum = 0LL;
        for (int i = 0; i < sz; ++i) {
            sum += intervals[i].e - intervals[i].b + 1;
            if (sum >= k) {

                pos = i;
                break;
            }
        }

        if (pos == -1) cout << -1 << '\n';
        else {
            int cnt1 = 0;
            long long cur = 0LL;
            long long ans = 1e16;
            for (int i = 0; i < sz; ++i) {
                int leng = intervals[i].e - intervals[i].b + 1;
                if (leng > 1) cur += leng;
                else cnt1++;

                if (cur < k) {
                    if (cur + cnt1 >= k) {
                        int cntSegs = (i + 1 - cnt1) + (k - cur);
                        ans = min(ans, intervals[i].e + 2LL * cntSegs);
                    }
                }
                else {
                    ans = min(ans, intervals[i].e - (cur - k) + 2LL * (i + 1 - cnt1));
                    break;
                }
            }

            cout << ans << '\n';
        }
    }

    return 0;
}