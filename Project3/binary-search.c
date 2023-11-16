#include<stdio.h>
#define ACC 1e-6
double sqrt(double x){
    if(x <= 1){
        double l = 0, r = 1;
        while(r - l >= ACC){
            double mid = (l + r) / 2;
            if(mid * mid < x) l = mid;
            else r = mid;
        }
        return (l + r) / 2;
    }
    else{
        double l = 1, r = x;
        while(r - l >= ACC){
            double mid = (l + r) / 2;
            if(mid * mid < x) l = mid;
            else r = mid;
        }
        return (l + r) / 2;
    }
}
int main(){
    double n;
    scanf("%lf", &n);
    printf("%lf", sqrt(n));
}