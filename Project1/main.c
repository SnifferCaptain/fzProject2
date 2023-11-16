#include "FFT.h"
#include <stdio.h>
#define MAXN 100010
int a[MAXN], b[MAXN], ans[MAXN];
void swap(int *a, int *b){
	int c = *a;
	*a = *b;
	*b = c;
	return;
}
int head, tail = -1;
int deque[MAXN];
int main(){
	int n, m, len;
	scanf("%d%d%d", &n, &m, &len);
	--n;
	--m;
	for(int i = 0; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 0; i <= m; ++i) scanf("%d", &b[i]);
	for(int i = 0; i <= (n >> 1); ++i) swap(&a[i], &a[n - i]);
	// for(int i = 0; i <= n; ++i) printf("%d ", a[i]);
	convolution(n, m, a, b, ans);
    for(int i = 0; i <= m - n; ++i) ans[i] = ans[i + n];
    for(int i = 0; i <= m - n; ++i) printf("%d ", ans[i]);
	printf("\n");
	for(int i = 0; i < len; ++i){
		while(tail >= head && ans[deque[tail]] <= ans[i]) --tail;
		deque[++tail] = i;
	}
	ans[0] = ans[deque[head]];
	for(int i = len; i <= m - n; ++i){
		int l = i - len + 1;
		while(tail >= head && deque[head] < l) ++head;
		while(tail >= head && ans[deque[tail]] <= ans[i]) --tail;
		deque[++tail] = i;
		ans[l] = ans[deque[head]];
	}
	for(int i = 0; i <= m - n - len + 1; ++i) printf("%d ", ans[i]);
}