#include<cstdio>
#include<iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, a, s1 = 0, s2 = 0, m;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a);
        s2 += a * a;
        s1 += a;
    }

    m = s1 / n;
    printf("%d", std::min(s2 + n * m * m - 2 * m * s1, s2 + n * (m + 1) * (m + 1) - 2 * (m + 1) * s1));

    return 0;
}