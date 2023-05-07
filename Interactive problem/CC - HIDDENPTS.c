// https://www.codechef.com/problems/HIDDENPTS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

struct Point {
  long double x;
  long double y;
}; 

struct Point point[100000];

long double query(long ai, long aj) {
    long double leng;
    printf("? %ld %ld\n", ai+1, aj+1);
    fflush(stdout);
    scanf("%Lf", &leng);
    return leng;
}

int cmp(const void* a, const void* b) {
    struct Point *p1 = (struct Point *)a,  *p2 = (struct Point *)b;
    if (p1->x != p2->x) {
        if (p1->x > p2->x) {
            return 1;
        } else {
            return -1;
        }
    } else {
        if (p1->y > p2->y) {
            return 1;
        } else if (p1->y == p2->y) {
            return 0;
        } else {
            return -1;
        }
    }
}

int main(void) {
	int T;
	const long double limErr = 1e-12;
	scanf("%d", &T);
	while (T--) {
	    long N;
	    scanf("%ld", &N);

	    point[0].x = 0;  
	    point[0].y = 0;
	    // a1
	    long double dist01 = query(0,1);
	    point[1].x = sqrtl(dist01);  
	    point[1].y = 0;
        
        // others points
        // 2 intersections of 2 circle from a0, a1, only 1 satisfy leng[k][aj]
        // because a0 a1 on Ox, need to find a point not on Ox
        long thirdPoint = 0;
        for (long i = 2; i < N; i++) {
            long double dist0i = query(0,i);
            long double dist1i = query(1,i);
            long double a = (dist0i-dist1i+dist01) / (2.0*point[1].x);
            point[i].x = a;
            
            if ( (dist0i - a*a) <= 0) {
                point[i].y = 0;
            } else {
                point[i].y = sqrtl(dist0i-a*a);
                if (thirdPoint == 0) {
                    if ( (dist0i - a*a) > limErr ) {
                        thirdPoint = i;
                    }
                    continue;
                }
                long double dist2i = query(thirdPoint,i);
                long double lDiff1 = dist2i - (a-point[thirdPoint].x)*(a-point[thirdPoint].x) - (point[i].y-point[thirdPoint].y)*(point[i].y-point[thirdPoint].y);
                long double lDiff2 = dist2i - (a-point[thirdPoint].x)*(a-point[thirdPoint].x) - (-point[i].y-point[thirdPoint].y)*(-point[i].y-point[thirdPoint].y);
                if (lDiff1 < 0) { lDiff1 = -lDiff1; }
                if (lDiff2 < 0) { lDiff2 = -lDiff2; }
                if (lDiff2 < lDiff1) {
                    point[i].y = -point[i].y;
                }
            }
        }
        
        qsort(point,N,sizeof(struct Point),cmp);
        /*for (int i = 0; i < N; i++) {
            printf("%Lf %Lf\n",point[i].x, point[i].y);
        }*/
        long double min = dist01;
        for(long i = 0; i < N-1; i++) {
            for(long j = i+1; j < N; j++) {
                if(min+1 < (point[i].x-point[j].x)*(point[i].x-point[j].x)) {
                    break;
                }
                long double dist = (point[i].x-point[j].x) * (point[i].x-point[j].x) + (point[i].y-point[j].y) * (point[i].y-point[j].y);
                if (dist < min) {
                    min = dist;
                }
            }
        }
        
        printf("! %.0Lf\n", min);
        fflush(stdout);
	}
	return 0;
}
