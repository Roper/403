#include <cstdio>

void Work(){
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= k; i ++){
		int x, y;
		scanf("%d %d", &x, &y);
		a[x][0] ++;
		a[x][a[x][0]] = y;
	}
	for(int i = 1; i <= n; i ++)
		
}

int main(){
	freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
	
	scanf("%d", &T);
	while(T --) Work();
	
	return 0;
}