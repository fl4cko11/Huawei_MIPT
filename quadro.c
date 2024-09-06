#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool sign_of_diskr(double a, double b, double c){
    double D = (b*b - 4*a*c);
    if (D>0)
        return(true);
    else
        return(false);
}

double diskr(double a, double b, double c){
    double D = (b*b - 4*a*c);
    return (D);
}

int main(){
    double a, b, c;
    printf("vvedite a");
    scanf("%lf", &a);
    printf("vvedite b");
    scanf("%lf", &b);
    printf("vvedite c");
    scanf("%lf", &c);

    if (a==0){
        printf("ne kvadratnoe");
        return 0;
    }

    else{
        bool s = sign_of_diskr(a, b, c);
        double d = diskr(a, b, c);
        if (s && d!=0){
            double sol1 = ((-b + sqrt(d))/(2*a));
            double sol2 = ((-b - sqrt(d))/(2*a));
            printf("1st sol %f\n", sol1);
            printf("2nd sol %f\n", sol2);
            return 0;
        }
        else if (s && d==0){
            double sol = ((-b)/(2*a));
            printf("sol %f\n", sol);
            return(0);
        }
        else{
            printf("no sol in R\n");
            return 0;
        }
    }
}