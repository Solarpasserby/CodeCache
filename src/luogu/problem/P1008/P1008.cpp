#include<iostream>

using namespace std;

void func(int n, bool *arr)
{
    int n1, n2, n3;
    n1 = n, n2 = 2 * n, n3 = 3 * n;

    while(n1 > 0)
    {
        arr[n1 % 10] = true;
        arr[n2 % 10] = true;
        arr[n3 % 10] = true;
        n1 /= 10;
        n2 /= 10;
        n3 /= 10;
    }
}

int main()
{
    for(int i = 123; i < 330; i++)
    {
        bool arr[10] = {false};
        func(i, arr);
        for (int j = 1; j < 10; j++)
        {
            if (arr[j] == false) break;
            else if (j == 9) cout << i << ' ' << 2 * i << ' ' << 3 * i << '\n';
        }
    }

    return 0;
}