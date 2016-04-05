#include <cstdio>

long long T, n;

int main(){
	freopen("c.in", "r", stdin), freopen("c.out", "w", stdout);
	
	scanf("%d", &T);
	for(int i = 1; i <= T; i ++){
		scanf("%d", &n);
		if(n == 2){printf("1\n"); continue;}
		if(n % 2) printf("%lld\n", (n/2)*(n/2 + 1));
		else if(n/2 % 2) printf("%lld\n", (n/2 - 2)*(n/2 + 2));
		else printf("%lld\n", (n/2 - 1)*(n/2 + 1));
	}
	
	return 0;
}