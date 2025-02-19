#include <iostream>
using namespace std;

int n, res = 0;

int main()
{
    void operate(int arr[][2], int start, int tmp, int order);
    cin >> n;
    int arr[n][2];
    for (int i = 0; i < n; i++)
    {
        if (i + 1 < n)
            arr[i][1] = i + 1;
        else
            arr[i][1] = -1;
        cin >> arr[i][0];
    }
    operate(arr, 0, 0, 1);
    cout << res << endl;
    return 0;
}

void operate(int arr[][2], int start, int tmp, int order)
{
    if (order <= n)
    {
        operate(arr, arr[start][1], tmp + (order ^ arr[start][0]), order + 1);
        int m, i = start;
        while (arr[i][1] != -1)
        {
            m = arr[i][1];
            arr[i][1] = arr[m][1];
            operate(arr, start, tmp + (order ^ arr[m][0]), order + 1);
            arr[i][1] = m;
            i = m;
        }
    }
    else if (tmp != 0)
        res |= tmp;
}