#include<cstdio>

int main()
{
    int n, x, a;
    scanf("%d%d", &n, &x);

    for (;n--;)
    {
        scanf("%d", &a);
        if (a == x) continue;
        else printf("%d ", a);
    }

    printf("\n");

    return 0;
}