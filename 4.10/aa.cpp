#include <cstdio>

const int N = 1e5;
int n, m, ans;
char st[N][5];

int main(){
	freopen("a.in", "r", stdin), freopen("aa.out", "w", stdout);
	
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n ; i ++)
		scanf("%s", st[i]);
	
	for(int i = 1; i < n; i ++)
		for(int j = i + 1; j <= n; j ++){
			int num = 0;
			for(int k = 0; k < 4; k ++)
				if(st[i][k] != st[j][k]) num ++;
			if(num == m){
				ans ++;
			}
		}
			
	printf("%d", ans);
	
	return 0;
}