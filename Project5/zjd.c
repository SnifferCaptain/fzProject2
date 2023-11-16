#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define MAXN 1000010
#define eta 0.999
#define ACC 1e-9
double cal(double x){
	return 10 * sin(x * x) - 2 * sin(x) + 5;
}
double f(double x){
	double T = 100;
	while(T >= ACC){
		double delta = rand() & 1 ? T : -T ;
		if(cal(x + delta) < cal(x)){
			x = x + delta;
		}
		else{
			x = x + delta * T;
		}
		T *= eta;
//		printf("%lf %lf\n", x, cal(x));
	}
	return x;
}
int main(){
    srand(time(NULL));
	double ans = 505150.8199844008;
    int k;
    scanf("%d", &k);
	for(int i = 1; i <= k; ++i){
		double x = f(x);
		if(cal(x) < cal(ans)) ans = x;
		printf("%d: %.10lf %.10lf\n", i, ans, cal(ans));
	}
	printf("%.10lf %.10lf\n", ans, cal(ans));
	return 0;
}