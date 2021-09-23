#include<stdlib.h>
#include<stdio.h>
#include<math.h>

double getu(double l,double d,double hf,double myu,double eps){
    double p = 1000;
    double res = -2*pow(2*d*hf/l,0.5)*log10(eps/3.7+2.51*myu/1000/d/p*sqrt(l/2/d/hf));
    return res;
}

int main(){
    double l = 138;
    double d = 0.082;
    double hf = 49.1;
    double myu = 2.51;
    double eps = 0.0001;
    double res = getu(l,d,hf,myu,eps);
    printf("res is %.3f\n",res);
    return 0;
}
