#include<iostream>
#include<string>

using namespace std;

char c[10];
int num[30];
string s[10][10];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int count = 0;
        cin >> s[i][0];
        for(int j = 1; j < n; j++)
        {
            cin >> s[i][j];
            if (s[i][j].length() > 1) ++count;
        }
        if (i != 0)
        {
            if (c[count])
            {
                cout << "ERROR!" << '\n';
                return 0;
            }

            c[count] = s[i][0][0];
            num[s[i][0][0] - 'A'] = count;
        }
    }

    for(int i = 0; i < n - 1; i++)
    {
        if (c[i]) continue;
        else
        {
            cout << "ERROR!" << '\n';
            return 0;
        }
    }

    for(int i = 1; i < n; i++)
    {
        for(int j = 1; j < n; j++)
        {
            int a = num[s[i][0][0] - 'A'], b = num[s[j][0][0] - 'A'];
            if (a + b < n - 1)
            {
                if (c[a + b] == s[i][j][0] && s[i][j].length() == 1)
                    continue;
                else
                {
                    cout << "ERROR!" << '\n';
                    return 0;
                }
            }
            else
            {
                if (s[i][j][0] == c[1] && s[i][j][1] == c[a + b - n + 1] && s[i][j].length() == 2)
                    continue;
                else
                {
                    cout << "ERROR!" << '\n';
                    return 0;
                }
            }
        }
    }

    for(int i = 1; i < n; i++)
        cout << s[i][0][0] << '=' << num[s[i][0][0] - 'A'] << ' ';
    cout << '\n' << n-1 << '\n';

    return 0;
}