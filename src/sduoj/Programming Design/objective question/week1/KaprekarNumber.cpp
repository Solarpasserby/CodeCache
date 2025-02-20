#include<cstdio>

typedef long long ll;

int arr1[10], arr2[10];

ll funcG1()
{
    ll ans = 0;
    for (int i = 9; i >= 0; --i)
        while(arr1[i])
        {
            ans *= 10;
            ans += i;
            --arr1[i];
        }

    return ans;
}

ll funcG2()
{
    ll ans = 0;
    for (int i = 0; i <= 9; ++i)
        while(arr2[i])
        {
            ans *= 10;
            ans += i;
            --arr2[i];
        }

    return ans;
}

ll func(ll a)
{
    while(a)
    {
        int tmp = a % 10;
        a /= 10;
        ++arr1[tmp];
        ++arr2[tmp];
    }

    return (funcG1() - funcG2());
}

int main()
{
    ll a, ans;
    int b;
    scanf("%lld%d", &a, &b);

    ans = a;
    for (int i = 0; i < b; i++)
    {
        ans = func(a);
        a = ans;
    }

    printf("%lld", ans);

    return 0;
}