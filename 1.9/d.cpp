#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 55;
int n;
double f[MAXN][MAXN];
struct Point{
	double x, y;
	Point(double X = 0, double Y = 0){x = X, y = Y;}
} a[MAXN];

double sqr(double x){return x * x;}

double CrsPrd(Point A, Point B){return A.x * B.y - A.y * B.x;}

bool cmp(Point A, Point B){return (CrsPrd(A, B)) < 0;}

void Work(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		scanf("%lf %lf", &a[i].x, &a[i].y);
		if(i > 1) a[i].x -= a[1].x, a[i].y -= a[1].y;
	}
	a[1].x = 0, a[1].y = 0;
	sort(a + 2, a + 1 + n, cmp);
	double averS = 0; 
	for(int i = 2; i <= n; i ++){
		averS += double(CrsPrd(a[i], a[i - 1])) / 2;
	}
	averS /= n - 2;
	for(int len = 3; len <= n; len ++)
		for(int i = 1; i <= n; i ++){
			int j = (i + len - 2) % n + 1; 
			Point a1 = Point(a[j].x - a[i].x, a[j].y - a[i].y);
			for(int k = i + 1; k != j; k = k % n + 1){
				Point a2 = Point(a[k].x - a[i].x, a[k].y - a[i].y);
				int np1, np2;
				if(j > i) np1 = k - i + 1;
				else if(k <= n) np1 = k - i + 1;
				else np1 = n - i + 1 + k;
				np2 = len - np1 + 1;
				if(f[i][len] != 0) f[i][len] = min(f[i][len], f[i][np1] + f[k][np2] + sqr(CrsPrd(a2, a1) / 2));
				else f[i][len] = f[i][np1] + f[k][np2] + sqr(CrsPrd(a1, a2) / 2);
			}
		}
	printf("%.2f", sqrt(f[1][n] / (n - 2) - sqr(averS)));
}

int main(){
	freopen("d.in", "r", stdin), freopen("d.out", "w", stdout);
	
	Work();
	
	return 0;
}