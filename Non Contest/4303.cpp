#include <cstdio>
typedef long long LL;

LL n;
int d, a, b;

LL Half(int x){
	LL L = a, R = a + d*n;
	for(; L <= R;){
		LL mid = (L + R) >> 1;
		LL ti = (mid - a) / d + ((mid - a) % d != 0);
		if(mid - b <= (n - ti)*d) L = mid + 1;
		else R = mid - 1;
	}
	return R;
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%lld %d %d %d", &n, &d, &a, &b);
	n --;
	printf("%lld", Half(b - a));
	
	return 0;
}