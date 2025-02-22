#include<iostream>
#include<string>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, r, g, b;
    string s;
    r = g = b = 0;
    cin >> n;
    cin.ignore(114514, '\n');
    getline(cin, s);

    for(int i = 0; i < n; i++)
    {
        switch (s[i])
        {
        case 'R':
            r++;
            break;

        case 'G':
            g++;
            break;

        case 'B':
            b++;
            break;
        
        default:
            break;
        }
    }

    if (r > g) r = g;
    if (r > b) r = b;

    printf("%d", r);

    return 0;
}