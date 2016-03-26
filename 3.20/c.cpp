#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;

const int N = 1e5+10;
LL n, x, ans[3];
LL fi[3][N][40];
struct Sec{
	LL a[40];
	int num;
} a1[N], a2[3];

int main(){
	freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
	
	scanf("%d", &n);
	LL t = 0, sum = 0;
	for(int i = 1; i <= n; i ++){
		scanf("%d", &x); t = t ^ x; sum += x;
		for(int j = 1; j <= 30; j ++){
			a1[i].a[j] = x % 2;
			x = x >> 1; a1[i].num = max(j, a1[i].num);
			fi[0][i][j] = fi[0][i - 1][j];
			fi[1][i][j] = fi[1][i - 1][j];
			if(a1[i].a[j]) fi[1][i][j] = i;
			else fi[0][i][j] = i;
		}
		LL tt = t;
		for(int j = 1; j <= 30; j ++){
			a2[0].a[j] += tt % 2;
			tt = tt >> 1; a2[0].num = max(j, a2[0].num);
		}
		ans[0] += t;
	}
	
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= a1[i].num; j ++){
			a2[1].a[j] += i - fi[0][i][j];
			a2[2].a[j] += fi[1][i][j];
		}
	}
	for(int i = 1; i <= 30; i ++){
		ans[1] += (1 << (i - 1)) * a2[1].a[i];
		ans[2] += (1 << (i - 1)) * a2[2].a[i];
	}
	
	for(int i = 1; i <= n - 1; i ++){
		for(int j = 1; j <= a1[i].num; j ++)
			if(a1[i].a[j]) a2[0].a[j] = (n - i + 1) - a2[0].a[j];
		
		for(int j = 1; j <= a2[0].num; j ++)
			ans[0] += (1 << (j - 1)) * a2[0].a[j];
	}
	
	printf("%.3f %.3f %.3f", (ans[0] * 2 - sum) *1.0/ (n*n), (ans[1] * 2 - sum) *1.0/ (n*n), (ans[2] * 2 - sum) *1.0/ (n*n));
	
	return 0;
}