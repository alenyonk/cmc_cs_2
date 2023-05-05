#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern double f1(double);
extern double f2(double);
extern double f3(double);

double abss(double x){
    return x > 0? x: -x;
}

int counter;
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1){
    double c = f((a + b) / 2) - g((a + b) / 2); // c = result in then middle of [a, b] for function F = f - g
    if ((b - a < eps1) | c == 0){// we are doing this process till length of [a, b] less than eps1
        counter++;
	return (a + b) / 2;
    }
    if ((f(b) - g(b)) * c < 0){// if F(b) and F(c) has different sign => now new a is (a + b) / 2; else new b is (a + b) / 2
	counter++;        
	return root(f, g, (a + b) / 2, b, eps1);
    }else{
	counter++;
        return root(f, g, a, (a + b) / 2, eps1);
    }
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

int main(int argc, char * argv[]){
    counter = 0;
    double x13 = root(f1, f3, 1, 2, 0.001);
    int counter1 = counter;
    counter = 0;
    double x12 = root(f1, f2, 5, 6, 0.001);
    int counter2 = counter;
    counter = 0;
    double x23 = root(f2, f3, 4, 5, 0.001);
    int counter3 = counter;
    counter = 0;
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (!strcmp(argv[i], "-help"))
            { printf("-help: help command\n\n"
                     "-roots: print roots of equations\n\n"
                     "-integral: print result of program (main integral, that mentioned in task)\n\n"
                     "-iterations: print amount of iterations for calculation of root\n\n"
                     "-test -root i1 i2 a b eps1: test root func\n"
                     "-test -integral i a b eps1: test integral func\n"
                     "    functions available for test:\n"
                     "        1: 3(0.5/(x + 1) + 1)"
                     "        2: 2.5x - 9.5"
                     "        3: 5/x \n");}
            else if (!strcmp(argv[i], "-roots"))
            {
                printf("f = 3(0.5/(x + 1) + 1)\ng = 2.5x - 9.5\nx1 = %lf\n\n"
                       "f = 3(0.5/(x + 1) + 1)\ng = 5/x \nx2 = %lf\n\n"
                       "f = 2.5x - 9.5\ng = 5/x \nx3 = %lf\n\n", x12, x13, x23);
            }
            else if (!strcmp(argv[i], "-iterations"))
            {
                printf("f = 3(0.5/(x + 1) + 1)\ng = 2.5x - 9.5\niterations1: %d\n\n"
                       "f = 3(0.5/(x + 1) + 1)\ng = 5/x\niterations2: %d\n\n"
                       "f = 2.5x - 9.5\ng = 5/x\niterations3: %d\n\n", counter1, counter2, counter3);
            }
            else if (!strcmp(argv[i], "-test"))
            {
                if (!strcmp(argv[i + 1], "-root") && argc - (i + 1) >= 6)
                {
                    int i1 = atoi(argv[i + 2]), i2 = atoi(argv[i + 3]);
                    double (*f)(double);
                    switch (i1) {
                        case 1:
                            f = &f1;
                            break;
                        case 2:
                            f = &f2;
                            break;
                        case 3:
                            f = &f3;
                            break;
                        default:
                            f = &f1;
                            break;
                    }
                    double (*g)(double);
                    switch (i2) {
                        case 1:
                            g = &f1;
                            break;
                        case 2:
                            g = &f2;
                            break;
                        case 3:
                            g = &f3;
                            break;
                        default:
                            g = &f2;
                            break;

                    }
                    printf("x = %lf\n\n",
                           root(f, g, atof(argv[i + 4]),
                                atof(argv[i + 5]),
                                atof(argv[i  + 6])));
                    i += 6;
                }
                else if (!strcmp(argv[i + 1], "-integral") && argc - (i + 1) >= 5)
                {
                    int i1 = atoi(argv[i + 2]);
                    double (*f)(double);
                    switch (i1) {
                        case 1:
                            f = &f1;
                            break;
                        case 2:
                            f = &f2;
                            break;
                        case 3:
                            f = &f3;
                            break;
                        default:
                            f = &f1;
                            break;
                    }
                    printf("I = %lf\n\n",
                           integral(f, atof(argv[i + 3]),
                                    atof(argv[i + 4]),
                                    atof(argv[i + 5]), 10));
                    i += 5;
                }
                else
                {
                    printf("Wrong format of '-test' command\n\n");
                }
            }
            else if (!strcmp(argv[i], "-integral"))
            {
                double I = integral(f1, x13, x12, 0.001, 10) - integral(f3, x13, x23, 0.001, 10) - integral(f2, x23, x12, 0.001, 10);
                printf("Integral = %lf\n\n", I);
            }
        }
    }
    else{
        printf("-help: help command\n\n"
               "-roots: print roots of equations\n\n"
               "-integral: print result of program (main integral, that mentioned in task)\n\n"
               "-iterations: print amount of iterations for calculation of root\n\n"
               "-test -root i1 i2 a b eps1: test root func\n"
               "-test -integral i a b eps1: test integral func\n"
               "    functions available for test:\n"
               "        1: 3(0.5/(x + 1) + 1)\n"
               "        2: 2.5x - 9.5\n"
               "        3: 5/x\n");
    }
    return 0;
}


