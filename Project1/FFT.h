#include<math.h>
#include<stdio.h>
#define FFT_MAXN 100010
#define Pi 3.14159265358979323846
struct complex {
    double x, y;
}FFT_a[FFT_MAXN], FFT_b[FFT_MAXN];
struct complex add(struct complex a, struct complex b){
    struct complex ans;
    ans.x = a.x + b.x;
    ans.y = a.y + b.y;
    return ans;
}
struct complex sub(struct complex a, struct complex b){
    struct complex ans;
    ans.x = a.x - b.x;
    ans.y = a.y - b.y;
    return ans;
}
struct complex mul(struct complex a, struct complex b){
    struct complex ans;
    ans.x = a.x * b.x - a.y * b.y;
    ans.y = a.x * b.y + a.y * b.x;
    return ans;
}
int N, M;
int l, r[FFT_MAXN];
int limit = 1;
void FFT_swap(struct complex *a, struct complex *b){
    struct complex c = *a;
    *a = *b;
    *b = c;
    return;
}
void FFT(struct complex *A, int type) {
    for (int i = 0; i < limit; i++)
        if (i < r[i]){
            FFT_swap(&A[i], &A[r[i]]); //求出要迭代的序列
        }
    for (int mid = 1; mid < limit; mid <<= 1) { //待合并区间的长度的一半
        struct complex Wn; //单位根
        Wn.x = cos(Pi / mid);
        Wn.y = (double)type * sin(Pi / mid);
        for (int R = mid << 1, j = 0; j < limit; j += R) { //R是区间的长度，j表示前已经到哪个位置了
            struct complex w; //幂
            w.x = 1.0;
            w.y = 0.0;
            for (int k = 0; k < mid; k++, w = mul(w, Wn)) { //枚举左半部分
                struct complex x = A[j + k], y = mul(w, A[j + mid + k]); //蝴蝶效应
                A[j + k] = add(x, y);
                A[j + mid + k] = sub(x, y);
            }
        }
    }
}
void convolution(int N, int M, int *A, int *B, int *ans){
    for(int i = 0; i <= N; i++) FFT_a[i].x = A[i];
    for(int i = 0; i <= M; i++) FFT_b[i].x = B[i];
    limit = 1; l = 0;
    while(limit <= N + M) limit <<= 1, l++;
    for(int i = 0; i <= limit; ++i) r[i] = 0;
    for (int i = 0; i < limit; i++)
        r[i] = ( r[i >> 1] >> 1 ) | ( (i & 1) << (l - 1) ) ;
    // 在原序列中 i 与 i/2 的关系是 ： i可以看做是i/2的二进制上的每一位左移一位得来
    // 那么在反转后的数组中就需要右移一位，同时特殊处理一下奇数
    FFT(FFT_a, 1);
    FFT(FFT_b, 1);
    for (int i = 0; i <= limit; i++) FFT_a[i] = mul(FFT_a[i], FFT_b[i]);
    FFT(FFT_a, -1);
    for (int i = 0; i <= N + M; i++)
        ans[i] = floor(FFT_a[i].x / limit + 0.5);
    return;
}
#undef FFT_MAXN
#undef Pi