#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;

const int N = 1e5*2;
int n, Q;
LL a[N], h[N+10][2], s[N], sum[N], lm[N], rm[N];

int Hash(int x){
	int t = x % N + 1;
	while(h[t][0] != x && h[t][0]) t = t % N + 1;
	h[t][0] = x;
	return t;
}

bool cmp(int x, int y){return h[x][0] < h[y][0];}

int Half(int x){
	int L = 1, R = n;
	while(L <= R){
		int mid = (L + R) >> 1;
		if(h[a[mid]][0] >= x) R = mid - 1;
		else L = mid + 1;
	}
	return L;
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d %d", &n, &Q);
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a[i]);
		a[i] = Hash(a[i]);
	}
	
	int top = 0; s[0] = 0;
	for(int i = 1; i <= n; i ++){
		while(top > 0 && h[a[s[top]]][0] <= h[a[i]][0]) top --;
		s[++ top] = i;
		lm[i] = i - s[top - 1];
	}
	top = 0; s[0] = n + 1;
	for(int i = n; i >= 1; i --){
		while(top > 0 && h[a[s[top]]][0] < h[a[i]][0]) top --;
		s[++ top] = i;
		rm[i] = s[top - 1] - i;
		h[a[i]][1] += lm[i]*rm[i];
	}
	
	sort(a + 1, a + 1 + n, cmp);
	for(int i = 1; i <= n; i ++)
		sum[i] = sum[i - 1] + h[a[i]][1]*(h[a[i]][0] != h[a[i - 1]][0]);
	scanf("\n");
	for(int i = 1; i <= Q; i ++){
		char c = getchar(); int x;
		scanf("%d\n", &x);
		int pos = Half(x);
		if(x == h[a[pos]][0]){
			if(c == '=') printf("%lld\n", h[a[pos]][1]);
			else if(c == '>') printf("%lld\n", sum[n] - sum[pos]);
			else printf("%lld\n", sum[pos - 1]);
		}
		else{
			if(c == '=') printf("0\n");
			else if(c == '>') printf("%lld\n", sum[n] - sum[pos - 1]);
			else printf("%lld\n", sum[pos - 1]);
		}
	}
	
	return 0;
}