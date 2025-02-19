#include <iostream>
using namespace std;

int n, val = 0;
int *a;

int main()
{
    void operateArr(int i, int u, int tmp);
    cin >> n;
    a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    operateArr(0, 1, 0);
    cout << val << endl;
    return 0;
}

void operateArr(int i, int u, int tmp)
{
    if (i < n)
    {
        operateArr(i + 1, u + 1, tmp + u * a[i]);
        operateArr(i + 1, u, tmp);
    }
    else val ^= tmp;
}
