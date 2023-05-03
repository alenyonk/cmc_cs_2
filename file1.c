#include <stdio.h>

extern double f1(double);
extern double f2(double);
extern double f3(double);

double abss(double x){
    return x > 0? x: -x;
}


double root(double (*f)(double), double (*g)(double), double a, double b, double eps1){
    double c = f((a + b) / 2) - g((a + b) / 2); // c = result in then middle of [a, b] for function F = f - g
    if ((b - a < eps1) | c == 0)// we are doing this process till length of [a, b] less than eps1
        return (a + b) / 2;
    if ((f(b) - g(b)) * c < 0)// if F(b) and F(c) has different sign => now new a is (a + b) / 2; else new b is (a + b) / 2
        return root(f, g, (a + b) / 2, b, eps1);
    else
        return root(f, g, a, (a + b) / 2, eps1);

}

double integral(double (*f)(double), double a, double b, double eps2, int n){
    /*
    inter1 = (b - a)/n *(f(x1) + .. + f(xn-1))
    inter2 is the same, but for 2n
    */
    double inter1 = 0;
    for (double i = a ; i <= b; i += ((b - a)/n)){
        inter1 += f(i);
    }
    inter1 *= ((b - a)/ n);

    double inter2 = 0;
    int m = 2 * n;
    for (double j = a ; j <= b; j += ((b - a)/m)){
        inter2 += f(j);
    }
    inter2 *= ((b - a)/ (2 * n));

    if (abss(inter1 - inter2) <= eps2)
        return inter1;
    return integral(f, a, b, eps2, 2 * n);
}

/*
we have already counted "with hands" value of a and b for our functions

        a   b
f1  f2  5   6
f2  f3  4   5
f3  f1  1   2


*/

int main(void){
    double x13 = root(f1, f3, 1, 2, 0.001);
    double x12 = root(f1, f2, 5, 6, 0.001);
    double x23 = root(f2, f3, 4, 5, 0.001);
    printf("%.3lf\n", integral(f1, x13, x12, 0.001, 10) - integral(f3, x13, x23, 0.001, 10) - integral(f3, x23, x12, 0.001, 10)) ;
    return 0;
}
