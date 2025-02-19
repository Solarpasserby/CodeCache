#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, res = 0;
    vector<int> array;

    cin >> n;
    array.reserve(n);

    for(int i = 0; i < n; i++)
        cin >> array[i];

    for(int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        res += tmp * array[i];
    }

    if (res == 0) printf("Yes\n");
    else printf("No\n");

    return 0;
}