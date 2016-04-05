#include <cstdio>
#include <algorithm>

const int N = 
int n, q, tot;
int a[N], aa[N], aaa[N], q[N], rt[N], lt[N], num[N], sum[N];

bool cmp(int x, int y){return a[x] > a[y] ? 0 : 1;}

int Half(int L, int R, int k){
	while(L <= R){
		int mid = (L + R) / 2;
		if(aaa[mid] >= k) R = mid - 1;
		else L = mid + 1;
	}
	return L;
}

int main(){
	fropen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d %d", &n, &q);
	
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a[i]);
		aa[i] = i;
		while(tot && a[i] > q[tot]) rt[q[tot]] = i - 1, tot --;
		q[++ tot] = i;
	}
	while(tot) rt[q[tot --]] = n;
	for(int i = n; i >= 1; i --){
		while(tot && a[i] > q[tot]) lt[q[tot]] = i + 1, tot --;
		q[++ tot] = i;
	}
	while(tot) lt[q[tot --]] = 1;
	
	sort(aa + 1, aa + n, cmp);
	
	tot = 0;
	for(int i = 1; i <= n; i ++){
		if(i > 1 && aa[i] == aa[i - 1]) tot --;
		num[++ tot] += (rt[i] - i + 1)*(i - lt[i] + 1);
		aaa[tot] = aa[i];
	}
	for(int i = 1; i <= tot; i ++) sum[i] = sum[i - 1] + num[i];
	
	for(int i = 1; i <= q; i ++){
		char c; int x, pos;
		c = getchar(), scanf("%d",&x);
		pos = Half(1, tot, x);
		if(c == '=')
			if(aaa[pos] == k) printf("%d", sum[pos]);
			else printf("0");
		else if(c == '>')
			if(aaa[pos] == k) printf("%d", sum[tot] - sum[pos]);
			else printf("%d", sum[tot] - sum[pos - 1]);
		else 
			if(aaa[pos] == k) printf("%d", sum[pos - 1]);
			else printf("%d", sum[pos]);
	}
	
	return 0;
}