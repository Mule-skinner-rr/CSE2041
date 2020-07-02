/*
*Name - Nikhil Ranjan Nayak
*Regd No - 1641012040
*Desc -	Simple conduction problems
*/

#include <stdio.h>

void header(void)
{
    printf("\n        kA (T2 - T1)   ");
    printf("\n   H = --------------  ");
    printf("\n             X         ");
}

double calc_h(double h, double k, double a, double del_t, double x)
{
    h = (k * a * del_t) / x;
    
    return(h);
}

double calc_k(double h, double k, double a, double del_t, double x)
{
    k = (h * x) / (a * del_t);
    
    return(k);
}

double calc_a(double h, double k, double a, double del_t, double x)
{
    a = (h * x) / (k * del_t);
    
    return(a);
}

double calc_t2(double h, double k, double a, double t1, double t2, double x)
{
    t2 = ((h * x) / (k * a)) + t1;
    
    return(t2);
}

double calc_t1(double h, double k, double a, double t1, double t2, double x)
{
    t1 = t2 - ((h * x) / (k * a));
    
    return(t1);
}

double calc_x(double h, double k, double a, double del_t, double x)
{
    x = (k * a * del_t) / h;
    
    return(x);
}

void display_solution(double h, double k, double a, double t2, double t1, double x)
{
    printf("\n  H = %.1f W.", h);
    printf("\n  k = %.3f W/m-K.", k);
    printf("\n  A = %.3f m^2.", a);
    printf("\n  T2 = %.0f K.", t2);
    printf("\n  T1 = %.0f K.", t1);
    printf("\n  x = %.3f m.\n\n", x);
}

char get_info(double*, double*, double*, double*, double*, double*);
double find_unk(char, double, double, double, double, double, double);

void main()
{
    double unk, h, k, a, t2, t1, x;
    char calc;
    
    calc = get_info(&h, &k, &a, &t2, &t1, &x);
    
    header();
    
    unk = find_unk(calc, h, k, a, t2, t1, x);
    
}

char get_info(double *h, double *k, double *a, double *t2, double *t1, double *x)
{
    int flag;
    char ch, calc = 0;
    
    printf("\nRespond to the prompts with the data known. For the unknown quantity, enter a question mark (?).");
    
    printf("\nRate of heat transfer (watts) >> ");
    flag = scanf("%lf", h);
    if (flag == 0) {
        scanf(" %c", &ch);
        calc = 'h';
    }
    printf("\nCoefficient of thermal conductivity (W/m-K) >> ");
    flag = scanf("%lf", k);
    if (flag == 0){
        scanf(" %c", &ch);
        calc = 'k';
    }
    printf("\nCross-sectional area of conductor (m^2) >> ");
    flag = scanf("%lf", a);
    if (flag == 0){
        scanf(" %c", &ch);
        calc = 'a';
    }
    printf("\nTemperature on one side (K) >> ");
    flag = scanf("%lf", t2);
    if (flag == 0){
        scanf(" %c", &ch);
        calc = '2';
    }
    printf("\nTemperature on other side (K) >> ");
    flag = scanf("%lf", t1);
    if (flag == 0){
        scanf(" %c", &ch);
        calc = '1';
    }
    printf("\nThickness of conductor (m) >> ");
    flag = scanf("%lf", x);
    if (flag == 0){
        scanf(" %c", &ch);
        calc = 'x';
    }
    return(calc);
}

double find_unk(char calc, double h, double k, double a, double t2, double t1, double x)
{
    double unk = 0.0;
    
    switch (calc)
    {
        case 'h':
            unk = calc_h(h, k, a, (t2 - t1), x);
            printf("\n\nThe rate of heat transfer is %.1f W\n", unk);
            display_solution(unk, k, a, t2, t1, x);
            break;
            
        case 'k':
            unk = calc_k(h, k, a, (t2 - t1), x);
            printf("\n\nThe coefficient of thermal conductivity is %.3f\n", unk);
            display_solution(h, unk, a, t2, t1, x);
            break;
            
        case 'a':
            unk = calc_a(h, k, a, (t2 - t1), x);
            printf("\n\nThe cross-sectional area of the conductor is %.3f\n", unk);
            display_solution(h, k, unk, t2, t1, x);
            break;
            
        case '2':
            unk = calc_t2(h, k, a, t1, t2, x);
            printf("\n\nThe temperature on one side is %.0f\n", unk);
            display_solution(h, k, a, unk, t1, x);
            break;
            
        case '1':
            unk = calc_t1(h, k, a, t1, t2, x);
            printf("\n\nThe temperature on the other side is %.0f\n", unk);
            display_solution(h, k, a, t2, unk, x);
            break;
            
        case 'x':
            unk = calc_x(h, k, a, (t2 - t1), x);
            printf("\n\nThe thickness of the conductor is %.3f\n", unk);
            display_solution(h, k, a, t2, t1, unk);
            break;
    }
    return(unk);
}
