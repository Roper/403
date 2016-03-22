#include <cstdio>

void Manacher(char *st, int *a){
	int len = stlen(st);
	for(int i = 0; i < len; i ++) stt[i * 2] = '#', stt[i * 2 + 1] = st[i];
	len = len * 2 + 1;
	stt[len - 1] = '#';
	
	int mx = 0, p = 0;
	for(int i = 0; i < len; i ++){
		if(mx > i) a[i] = min(mx - i + 1, a[p * 2 - i]);
		else a[i] = 1;
		for(; i - a[i] >= 0 && i - a[i] < len && stt[i + a[i]] == stt[i - a[i]]; a[i] ++);
		if(mx < a[i] + i){
			mx = a[i] + i;
			p = i;
		}
	}
}

void Hash(LL x, int st, int en, int k){
	int ha = x % hmo;
	while(h2[ha].x){
		if(h2[ha].x == x) break;
		ha = (ha + 1) % hmo;
	}
	if(k == 1){
		if(h2[ha].x == x) h2[ha].num[0] ++;
		else{
			h2[ha].x = x; h2[ha].num[0] = 1;
			h2[ha].st = st; h2[ha].en = en;
			ah[++ ah[0]].x = en - st + 1;
			ah[ah[0]].y = ha;
		}
	}
	else if(h2[ha].x == x) h2[ha].num[1] ++;
}

void Find(char *st, int k){
	int len = strlen(st);
	
	for(int i = 0; i < len; i ++){
		if(i != 0) h1[k][i] = (h1[k][i - 1] * 27 + st[i] - 'a' + 1) % mo;
		else h1[k][i] = st[i] - 'a' + 1;
	}
	len = len * 2 + 1;
	for(int i = 0; i < len; i ++){ // (i - 1) / 2
		int st = i - a[k][i] + 1, en = i + a[k][i] - 1;
		if(!(st % 2)) st ++; if(!(en % 2)) en --;
		st = (st - 1) / 2, en = (en - 1) / 2;
		
		if(st == 0) Hash(h1[k][en], st, en, k);
		else Hash((h1[k][en] - h1[k][st - 1] * hh[en - st + 1] + mo * mo) % mo, st, en, k);
	}
}

bool cmp(aHash A, aHash B){return A.x > B.x;}

void Work(){
	scanf("%s", str[0]);
	scanf("%s", str[1]);
	
	Manacher(str[0], a[0]);
	Manacher(str[1], a[1]);
	
	hh[0] = 1;
	for(int i = 1; i <= len; i ++) hh[i] = hh[i - 1] * 27 % mo; // long long
	Find(str[0], 0);
	sort(ah + 1, ah + 1 + ah[0], cmp);
}

int main(){
	freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);

	Work();

	return 0;
}
