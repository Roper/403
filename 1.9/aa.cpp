#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 55, inf = 2147483647;
int n, ans, tot;
bool b[MAXN];
struct Calc{
	int x, op;
} a[MAXN], aa[MAXN];

int Dfs(int L, int R){
	if(L == R) return aa[L].x;
	int ret = -inf;
	for(int i = L + 1; i <= R; i ++){
		int cper;
		if(aa[i - 1].op) cper = Dfs(L, i - 1) * Dfs(i, R);
		else cper = Dfs(L, i - 1) + Dfs(i, R);
		ret = max(ret, cper);
	}
	return ret;
}

void Work(){
	scanf("%d\n", &n);
	for(int i = 1; i <= n; i ++){
		char c; int x;
		scanf("%c %d ", &c, &x);
		a[i].x = x;
		a[i - 1].op = (c == 'x');
	}
	a[n].op = a[0].op; a[0].op = 0;
	for(int i = 1; i <= n; i ++){
		int j = i % n + 1; tot = 0;
		while(j != i){
			aa[++ tot] = a[j];
			j = j % n + 1;
		}
		aa[++ tot].x = a[i].x;
		int t = Dfs(1, tot);
		if(t == ans) b[i % n + 1] = 1;
		if(t > ans){
			ans = t;
			memset(b, 0, sizeof(b));
			b[i % n + 1] = 1;
		}
	}
	printf("%d\n", ans);
	for(int i = 1; i <= n; i ++) if(b[i]) printf("%d ", i);
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	Work();
	
	return 0;
}