// angle of the n-gon = gcd(angle a, b c)
// https://www.geeksforgeeks.org/minimum-area-polygon-three-points-given/ for explanation

#include <bits/stdc++.h>
 
using namespace std;

const double PI = acos(-1.0), EPS = 1e-4;

double gcd(double a, double b) {
    if(fabs(b) < EPS) return a;
    if(fabs(a) < EPS) return b;
    return gcd(b,fmod(a,b));
}
 
double dis(double xi, double yi, double xj, double yj) {
    return sqrt((xi-xj)*(xi-xj)+(yi-yj)*(yi-yj));
}
 
double acosPrecise(double d) {
    if(d+1<EPS) return PI;
    return acos(d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif 

    int t = 1;
    //cin>>t;
    for (int tt = 0; tt < t; ++tt)
    {
        double xa,ya,xb,yb,xc,yc;
        cin>>xa>>ya>>xb>>yb>>xc>>yc;
 
        double a = dis(xb,yb,xc,yc);
        double b = dis(xa,ya,xc,yc);
        double c = dis(xa,ya,xb,yb);
     
        double p = (a+b+c)/2;
        double S = sqrt(p*(p-a)*(p-b)*(p-c));
     
        double R = a*b*c/4.0/S;
     
        double da = acosPrecise(1-a*a/(2*R*R));
        double db = acosPrecise(1-b*b/(2*R*R));
        //double dc = acosPrecise(1-c*c/(2*R*R));

        // angle of the polygon
        double alpha = gcd(gcd(da,db), 2*PI-da-db);
        printf("%.6lf\n",PI/alpha*R*R*sin(alpha));
    }

    return 0;
}