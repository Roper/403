#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;

const int N = 100, MxT = 220000;
const double prcs = 1e-8;
int n, m, t2, v, tot;
int a[2][N][2], Last[N*N], opp[N*N*N];
bool used[N*N*N];
double t1;
double dis[N][N];

int sqr(int x){return x*x;}

struct Edge{
	int to, next;
	Edge(int X = 0, int Y = 0){to = X, next = Y;}
} E[N*N*N]; 

void Link(int x, int y){
	E[++ tot] = Edge(y, Last[x]), Last[x] = tot;
}

bool Match(int x){
	for(int p = Last[x]; p; p = E[p].next){
		int to = E[p].to;
		if(!used[to]){
			used[to] = 1;
			if(opp[to] == 0 || Match(opp[to])){
				opp[to] = x;
				return 1;
			}
		}
	}
	
	return 0;
}

int Judge(double lim){
	memset(E, 0, sizeof(E));
	memset(Last, 0, sizeof(Last));
	memset(opp, 0, sizeof(opp));
	double once = t1 + t2;
	int tms = lim / once;
	tms = min(tms, n);
	tot = 0;
	for(int i = 1; i <= m; i ++)
		for(int j = 1; j <= n; j ++)
		for(int k = 0; k <= tms; k ++){
			int now = (i - 1) * (tms + 1) + k + 1;
			if(k * once + dis[i][j] / v - lim + t1 <= prcs)
				Link(now, m * (tms + 1) + j + 1);
			else break;
	  }
	
	int ret = 0;
	for(int i = 1; i <= m; i ++) 
		for(int k = 0; k <= tms; k ++){
			int now = (i - 1) * (tms + 1) + k + 1;
			memset(used, 0, sizeof(used));
			ret += Match(now);
		}
		
	return ret;
}

LL Half(LL L, LL R){
	while(L <= R){
		LL mid = (L + R) / 2;
		if(Judge(mid *1.0/ 10000000) == n) R = mid - 1;
		else L = mid + 1;
	}
	return L;
}

int main(){
	freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
	
	scanf("%d %d %lf %d %d", &m, &n, &t1, &t2, &v);
	t1 = t1 / 60;
	for(int i = 1; i <= n; i ++) 
		scanf("%d %d", &a[0][i][0], &a[0][i][1]);
	for(int i = 1; i <= m; i ++) 
		scanf("%d %d", &a[1][i][0], &a[1][i][1]);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++) 
			dis[j][i] = sqrt(sqr(a[0][i][0] - a[1][j][0]) + sqr(a[0][i][1] - a[1][j][1]));
	
	printf("%.6f", Half(0, MxT *1LL* 10000000) *1.0/ 10000000);
	
	return 0;
}