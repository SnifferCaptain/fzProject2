#include<stdio.h>
#include<math.h>
#define MAXN 310
struct Node{
    double input[MAXN];
    double w[MAXN];
    int l1, r1, l2, r2;
}nerv[MAXN];
void build(int p, int l1, int r1, int l2, int r2, double *w){
    nerv[p].l1 = l1;
    nerv[p].r2 = r2;
    nerv[p].l2 = l2;
    nerv[p].r2 = r2;
    for(int i = nerv[p].l1; i <= nerv[p].r1; ++i){
        nerv[p].w[i] = w[i];
    }
    return;
}
double f(double x){
    return 1 / (1 + exp(-x));
}
void stimulate(int p){
    double ans = 0;
    for(int i = nerv[p].l1; i <= nerv[p].r1; ++i){
        ans += nerv[p].input[i] * nerv[p].w[i];
    }
    ans += nerv[p].w[0] * (-1);
    ans = f(ans);
    for(int i = nerv[p].l2; i <= nerv[p].r2; ++i){
        nerv[i].input[p] = ans;
    }
    return;
}
int main(){


    return 0;
}