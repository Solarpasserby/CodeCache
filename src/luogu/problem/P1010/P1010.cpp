#include<iostream>

using namespace std;

void func(int n)
{
    bool exp[20] = {0}, firstTime = true;
    for (int i = 0; n > 0; i++, n /= 2)
        exp[i] = n % 2;

    for (int i = 19; i >= 0; i--)
    {
        if (exp[i])
        {
            if (firstTime)
            {
                cout << "2";
                firstTime = false;
            }
            else
                cout << "+2";
            switch (i)
            {
            case 0:
                cout << "(0)";
                break;

            case 1:
                break;

            case 2:
                cout << "(2)";
                break;
            
            default:
                cout << '(';
                func(i);
                cout << ')';
                break;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    func(n);

    return 0;
}