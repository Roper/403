#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 60;
int T;
int a[N][3];

void Work(){
	memset(a, 0, sizeof(a));
	int n = 0, m; char c;
	while(c = getchar(), c >= '0' && c <= '9'){
		a[++ n][0] = c - '0';
		a[n][1] = n - 1;
		a[n][2] = n + 1;
	}
	int head = 1, hhead = 1;
	a[n][2] = 0;
	scanf("%d\n", &m);
	
	while(m > 0 && head > 0){
		int mn = min(n, m), mx = head, dis = 0;
		for(int i = 1, p = a[head][2]; i <= mn && p; i ++, p = a[p][2])
			if(a[p][0] > a[mx][0]){mx = p; dis = i;}
		if(mx == head){head = a[head][2]; continue;}
		a[a[mx][1]][2] = a[mx][2], a[a[mx][2]][1] = a[mx][1];
		a[mx][1] = a[head][1], a[mx][2] = head; 
		a[a[head][1]][2] = mx; a[head][1] = mx;
		if(!a[mx][1]) hhead = mx;
		m -= dis;
	}
	
	for(int p = hhead; p; p = a[p][2]) printf("%d", a[p][0]);
	printf("\n");
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	
	scanf("%d\n", &T);
	while(T --) Work();
	
	return 0;
}