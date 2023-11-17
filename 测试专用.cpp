#define _CRT_SECURE_NO_WARNINGS                        //这个别删，叶镕瑄的电脑上没有它可编译不了
#include <stdio.h>
#define MAXN 200
int num[MAXN][MAXN], core[MAXN][MAXN], ans[MAXN][MAXN];//（猜的）原始数据，卷积核，结果
int numH, numW, coreH, coreW, H, W; //数据矩阵大小，卷积核大小，池化核大小
void input() {
	scanf("%d%d%d%d%d%d", &numH, &numW, &coreH, &coreW, &H, &W);
	for (int i = 1; i <= coreH; ++i) {
		for (int j = 1; j <= coreW; ++j) {
			scanf("%d", &core[i][j]);
		}
	}
	for (int i = 1; i <= numH; ++i) {
		for (int j = 1; j <= numW; ++j) {
			scanf("%d", &num[i][j]);
		}
	}
	return;
}
int calculate(int x, int y) {
	int ans = 0;
	for (int i = 0; i < coreH; ++i) {
		for (int j = 0; j < coreW; ++j) {
			ans += num[x + i][y + j] * core[i + 1][j + 1];
		}
	}
	return ans;
}
int deque[MAXN], head, tail;
void solve() {
	for (int i = 1; i <= numH - coreH + 1; ++i) {
		for (int j = 1; j <= numW - coreW + 1; ++j) {
			ans[i][j] = calculate(i, j);
		}
	}
	for (int i = 1; i <= numH; ++i) {
		head = 0; tail = -1;
		for (int j = 1; j < W; ++j) {
			while (tail >= head && ans[i][deque[tail]] <= ans[i][j]) --tail;
			deque[++tail] = j;
		}
		for (int j = W; j <= numW; ++j) {
			int l = j - W + 1;
			while (tail >= head && deque[head] < l) ++head;
			while (tail >= head && ans[i][deque[tail]] <= ans[i][j]) --tail;
			deque[++tail] = j;
			ans[i][l] = ans[i][deque[head]];
		}
	}
	for (int j = 1; j <= numW; ++j) {
		head = 0; tail = -1;
		for (int i = 1; i < H; ++i) {
			while (tail >= head && ans[deque[tail]][j] <= ans[i][j]) --tail;
			deque[++tail] = i;
		}
		for (int i = W; i <= numH; ++i) {
			int l = i - H + 1;
			while (tail >= head && deque[head] < l) ++head;
			while (tail >= head && ans[deque[tail]][j] <= ans[i][j]) --tail;
			deque[++tail] = i;
			ans[l][j] = ans[deque[head]][j];
		}
	}
	return;
}
void print() {
	for (int i = 1; i <= numH - coreH - H + 2; ++i) {
		for (int j = 1; j <= numW - coreW - W + 2; ++j) {
			printf("%d ", ans[i][j]);
		}
		printf("\n");
	}
	return;
}

//FILEGET使用方法：直接那他替代main函数中的input。读取外部txt文件是上一级文件夹的1.txt(原始数据)还有2.txt（卷积核）文件其他东西我懒得弄了，你scanf吧。附赠叶镕瑄最喜欢的1.txt文件和2.txt。
void FILEGET() {
NEGGER0:;
	printf("输入方式：键盘输入（1）还是txt输入（2）");
	int ip;
	char lines[MAXN][MAXN] = {};         //txt每行最多100个数字
	int temp1 = 0, temp2 = 0;//用于计数
	scanf("%d", &ip);
	if (ip == 1) {//原版键盘输入
		input();
	}          
	else if (ip == 2) {         //txt输入
		FILE* file;
		file = fopen("..\\1.txt", "r");
		if (file == NULL) {
			printf("无法打开原始数据\n");
			getchar();
			goto NEGGER0;     //在最开始的地方！main下面一行！
		}
		temp2 = 0;
		while (temp2 < MAXN && fgets(lines[temp2], MAXN+1, file)) {
			temp2++;
		}
		for (int i = 0, j; i < MAXN; i++) {
			j = 0;
			while (lines[i][j] != '\n' && j < MAXN) {
				if (lines[i][j] == 0)core[i][j] = 0;
				else num[i][j] = lines[i][j] - 48;
				j++;
			}
		}
		file = freopen("..\\2.txt", "r",file);
		if (file == NULL) {
			printf("无法打开卷积核\n");
			getchar();
			goto NEGGER0;     //在最开始的地方！main下面一行！
		}
		temp2 = 0;
		while (temp2 < MAXN && fgets(lines[temp2], MAXN + 1, file)) {
			temp2++;
		}
		for (int i = 0, j; i < MAXN; i++) {
			j = 0;
			while (lines[i][j] != '\n' && j < MAXN) {
				if (lines[i][j] ==0)core[i][j] = 0;
				else core[i][j] = lines[i][j]-48;
				j++;
			}
		}
		printf("数据矩阵大小(横纵)，卷积核大小（横纵），池化核大小（横纵）。一共6个数据。\n");
		scanf("%d%d%d%d%d%d", &numH, &numW, &coreH, &coreW, &H, &W);
	}

	//检查输入情况，记得注释掉。
	/*
	for (int i = 1; i <= MAXN; i++) {
		for (int j = 1; j <= MAXN; j++)
			printf("%d", num[i][j]);
		printf("\n");
	}
	for (int i = 1; i <= MAXN; i++) {
		for (int j = 1; j <= MAXN; j++)
			printf("%d", core[i][j]);
		printf("\n");
	}
	*/
}

int main() {
	// freopen("test.in", "r", stdin);
	input();
	solve();
	print();
}