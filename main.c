#include <stdio.h>
#include <math.h>
float abss(float x){
    return x > 0? x: -x;
}


//define our functions
float f0(float x){
    return 3*x;
}
float f1(float x){
    return 3*(0.5/(x+1)+1);
}
float f2(float x){
    return 2.5* x - 9.5;
}
float f3(float x){
    return 5 / x;
}



float root(float (*f)(float), float (*g)(float), float a, float b, float eps1){
    float c = f((a + b) / 2) - g((a + b) / 2); // c = result in then middle of [a, b] for function F = f - g
    if (b - a < eps1)// we are doing this process till length of [a, b] less than eps1
        return (a + b) / 2;
    if ((f(b) - g(b)) * c < 0)// if F(b) and F(c) has different sign => now new a is (a + b) / 2; else new b is (a + b) / 2
        return root(f, g, (a + b) / 2, b, eps1);
    else
        return root(f, g, a, (a + b) / 2, eps1);

}

float integral(float (*f)(float), float a, float b, float eps2){
    static int n = 10;
    /*
    inter1 = (b - a)/n *(f(x1) + .. + f(xn-1))
    inter2 is the same, but for 2n
    */
    float inter1 = 0;
    for (float i = a ; i <= b; i += ((b - a)/n)){
        inter1 += f(i);
    }
    inter1 *= ((b - a)/ n);

    float inter2 = 0;
    int m = 2 * n;
    for (float j = a ; j <= b; j += ((b - a)/m)){
        inter2 += f(j);
    }
    inter2 *= ((b - a)/ (2 * n));

    if (abss(inter1 - inter2) <= eps2)
        return inter2;
    n = n * 2;
    return integral(f, a, b, eps2);
}

/*
we have already counted "with hands" value of a and b for our functions

        a   b
f1  f2  5   6
f2  f3  4   5
f3  f1  1   2


*/

int main(void){
    printf("%.3f\n", root(f1, f2, 5, 6, 0.001));
    printf("%.2f", integral(f0, 5, 6, 0.001));
    return 0;
}
