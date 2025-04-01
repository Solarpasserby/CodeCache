#include<iostream>

using namespace std;

int func(int k)
{
    if (k < 1) return 0;
    return 1 + (func(k - 1) << 1);
}

int main()
{
    for(int i = 0; i < 11; ++i)
        cout << func(i) << '\n';

    return 0;
}