#include <stdio.h>
#define MAXN 200
int num[MAXN][MAXN], core[MAXN][MAXN], ans[MAXN][MAXN];
int numH, numW, coreH, coreW, H, W; //数据矩阵大小，卷积核大小，池化核大小
void input(){
	scanf("%d%d%d%d%d%d", &numH, &numW, &coreH, &coreW, &H, &W);
	for(int i = 1; i <= coreH; ++i){
		for(int j = 1; j <= coreW; ++j){
			scanf("%d", &core[i][j]);
		}
	}
	for(int i = 1; i <= numH; ++i){
		for(int j = 1; j <= numW; ++j){
			scanf("%d", &num[i][j]);
		}
	}
	return;
}
int calculate(int x, int y){
	int ans = 0;
	for(int i = 0; i < coreH; ++i){
		for(int j = 0; j < coreW; ++j){
			ans += num[x + i][y + j] * core[i + 1][j + 1];
		}
	}
	return ans;
}
int deque[MAXN], head, tail;
void solve(){
	for(int i = 1; i <= numH - coreH + 1; ++i){
		for(int j = 1; j <= numW - coreW + 1; ++j){
			ans[i][j] = calculate(i, j);
		}
	}
	for(int i = 1; i <= numH; ++i){
		head = 0; tail = -1;
		for(int j = 1; j < W; ++j){
			while(tail >= head && ans[i][deque[tail]] <= ans[i][j]) --tail;
			deque[++tail] = j;
		}
		for(int j = W; j <= numW; ++j){
			int l = j - W + 1;
			while(tail >= head && deque[head] < l) ++head;
			while(tail >= head && ans[i][deque[tail]] <= ans[i][j]) --tail;
			deque[++tail] = j;
			ans[i][l] = ans[i][deque[head]];
		}
	}
	for(int j = 1; j <= numW; ++j){
		head = 0; tail = -1;
		for(int i = 1; i < H; ++i){
			while(tail >= head && ans[deque[tail]][j] <= ans[i][j]) --tail;
			deque[++tail] = i;
		}
		for(int i = W; i <= numH; ++i){
			int l = i - H + 1;
			while(tail >= head && deque[head] < l) ++head;
			while(tail >= head && ans[deque[tail]][j] <= ans[i][j]) --tail;
			deque[++tail] = i;
			ans[l][j] = ans[deque[head]][j];
		}
	}
	return;
}
void print(){
	for(int i = 1; i <= numH - coreH - H + 2; ++i){
		for(int j = 1; j <= numW - coreW - W + 2; ++j){
			printf("%d ", ans[i][j]);
		}
		printf("\n");
	}
	return;
}
int main(){
	// freopen("test.in", "r", stdin);
	input();
	solve();
	print();
}