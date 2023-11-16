#include<stdio.h>
#include<math.h>
#define ACC 1e-6
double mysqrt(double x){
    double ans;
    if(x <= 1) ans = 0.5;
    else ans = x / 2;
    double last = -1;
    while(fabs(ans - last) > ACC){
        last = ans;
        ans = ans - (ans * ans - x) / (2 * ans);
    }
    return ans;
}
int main(){
    double n;
    scanf("%lf", &n);
    printf("%lf", mysqrt(n));
}