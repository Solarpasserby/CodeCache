#include<cstdio>
#include<cmath>

int main()
{
    int l1, l2, d1, d2;
    scanf("%d%d%d%d", &l1, &l2, &d1, &d2);
    printf("%.10lf\n", sqrt(l1 * l1 + l2 * l2 - 2 * l1 * l2 * cos((30 * d1 - 5.5 * d2) * M_PI / 180.0)));

    return 0;
}