#include <stdio.h>
float my_pow(float base, int exp)
{
    float base1 = base;
    for(int i=0; i < exp-1; i++)
    {
        base = base*base1;
    }
    return base;
}

void main()
{
    float a = 5, b;
    b = my_pow(a,3);
    printf("%.0f\n", b);
}