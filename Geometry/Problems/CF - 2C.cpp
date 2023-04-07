// call the exsimilicenter and insimilicenter of each pair of circle
// the exsimilicenters are collinear by d'alambert theorem
// the mid point of each pair of ex and in are collinear (gauss line) and circle with its
// as diameter are coaxial and have a common radical axis

#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 
 
    int test = 1;
    //cin>>test;
    for (long long tt = 0; tt < test; ++tt) {
        pair<int, int> p[3];
        int rad[3];
        for (int i = 0; i < 3; ++i) {
            int x, y; 
            cin >> x >> y >> rad[i];
            p[i] = {x, y};
        }

        if (rad[0] == rad[1] && rad[1] == rad[2]) {
            // circumcenter
            double D = 0.0, cirX = 0.0, cirY = 0.0;
            for (int i = 0; i < 3; ++i) {
                D += p[i].first*(p[(i+1)%3].second-p[(i+2)%3].second);
                cirX += (pow(p[i].first,2)+pow(p[i].second,2)) * (p[(i+1)%3].second-p[(i+2)%3].second);
                cirY += (pow(p[i].first,2)+pow(p[i].second,2)) * (p[(i+2)%3].first-p[(i+1)%3].first);
            }
            D = D * 2.0;

            cirX = cirX/D;
            cirY = cirY/D;

            printf("%.5f %.5f\n", cirX, cirY);
        } else {
            // "sort of" apollonius circles
            pair<int, int> circlePair[2];
            if (rad[0] == rad[1]) {
                circlePair[0] = {0, 2};
                circlePair[1] = {1, 2};
            } else if (rad[1] == rad[2]) {
                circlePair[0] = {0, 1};
                circlePair[1] = {0, 2};
            } else {
                circlePair[0] = {0, 1};
                circlePair[1] = {1, 2};
            }

            pair<double, double> ins[2], exs[2], mids[2];
            double radApo[2];
            for (int i = 0; i < 2; ++i)
            {
                int c1 = circlePair[i].first, c2 = circlePair[i].second;
                exs[i].first = (rad[c1]*p[c2].first - rad[c2]*p[c1].first)*1.0/(rad[c1]-rad[c2]);
                exs[i].second = (rad[c1]*p[c2].second - rad[c2]*p[c1].second)*1.0/(rad[c1]-rad[c2]);

                ins[i].first = (rad[c1]*p[c2].first + rad[c2]*p[c1].first)*1.0/(rad[c2]+rad[c1]);
                ins[i].second = (rad[c1]*p[c2].second + rad[c2]*p[c1].second)*1.0/(rad[c2]+rad[c1]);
            }

            for (int i = 0; i < 2; ++i)
            {
                mids[i].first = (ins[i].first+exs[i].first)/2.0;
                mids[i].second = (ins[i].second+exs[i].second)/2.0;
                radApo[i] = sqrtf(pow(exs[i].first-ins[i].first,2)+pow(exs[i].second-ins[i].second,2))/2.0;
            }

            double dist = sqrtf(pow(mids[1].first-mids[0].first,2)+pow(mids[1].second-mids[0].second,2));
            if (dist <= radApo[0]+radApo[1] && dist >= fabs(radApo[0]-radApo[1])) {
                // "isodynamic point"
                pair<double, double> iso[2];
                double ex = (mids[1].first - mids[0].first) / dist;
                double ey = (mids[1].second - mids[0].second) / dist;

                double x = (pow(radApo[0],2)-pow(radApo[1],2)+pow(dist,2))/(2.0*dist);
                double y = sqrtf(pow(radApo[0],2)-pow(x,2));

                iso[0].first = mids[0].first + x*ex - y*ey;
                iso[0].second = mids[0].second + x*ey + y*ex;

                iso[1].first = mids[0].first + x*ex + y*ey;
                iso[1].second = mids[0].second + x*ey - y*ex;

                // angle from iso to p[0] : 2*arcsin(dist(iso->p[0])/rad[0])
                // arcsin is bijective --> compare dist
                double distIso[2];
                for (int i = 0; i < 2; ++i)
                {
                    distIso[i] = sqrtf(pow(iso[i].first-p[0].first,2)+pow(iso[i].second-p[0].second,2));
                }
                if (distIso[0] < distIso[1]) {
                    printf("%.5f %.5f\n", iso[0].first, iso[0].second);
                } else {
                    printf("%.5f %.5f\n", iso[1].first, iso[1].second);
                }
            }
        }
    }
 
    return 0;
}