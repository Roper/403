#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 30, MAXS = 300000;
int n;
double f[MAXS];
struct Point{
	int x, y, fixd, num;
} a[MAXN], P;
struct Round{
	int a[MAXN];
	double dis[MAXN];
} r[MAXN];

int sqr(int x){return x * x;}
double Dis(Point A, Point B){return sqrt(sqr(A.x - B.x) + sqr(A.y - B.y));}
bool cmp1(Point A, Point B){return Dis(A, P) < Dis(B, P);}
bool cmp2(Point A, Point B){return A.num < B.num;}

void Work(){
	memset(a, 0, sizeof(a));
	memset(f, 0, sizeof(f));
	memset(r, 0, sizeof(r));
	int t = 0;
	bool b = 0;
	
	for(int i = 1; i <= n; i ++){
		scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].fixd);
		a[i].num = i;
		if(t > 0 && a[i].fixd) b = 1;
		t += (1 << (i - 1)) * a[i].fixd;
	}
	if(n == 1 && a[1].fixd){printf("0.000000\n"); return;}
	if(!b){printf("No Solution\n"); return;}
	
	for(int i = 1; i <= n; i ++){
		int now = 0;
		for(now = 1; now <= n; now ++) if(a[now].num == i) break;
		P = a[now];
		sort(a + 1, a + 1 + n, cmp1);
		for(int j = 2; j <= n; j ++){
			r[i].a[j - 1] = 1 << (a[j].num - 1);
			r[i].dis[j - 1] = Dis(a[1], a[j]);
		}
	}
	
	sort(a + 1, a + 1 + n, cmp2);
	
	int maxs = (1 << n) - 1;
	for(int S = t + 1; S <= maxs; S ++)
		for(int i = 1; i <= n; i ++) if(!a[i].fixd){
			int tt = 0, now = 1 << (i - 1);
			if(!(S & now)) continue;
			double F = f[S - now];
			for(int j = 1; j <= n - 1; j ++) if(S & r[i].a[j]){
				tt ++;
				F += r[i].dis[j];
				if(tt > 1) break;
			}
			if(f[S] > 0) f[S] = min(f[S], F);
			else f[S] = F;
		}
	
	printf("%.6f\n", f[maxs]);
}

int main(){
	freopen("b.in", "r", stdin), freopen("b.out", "w", stdout);
	
	while(scanf("%d", &n) && n != 0) Work();
	
	return 0;
}