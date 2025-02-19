#include <cstdio>

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%.3lf", (a - b) * 1.0 / a * 100);

    return 0;
}