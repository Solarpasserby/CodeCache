#include<iostream>
#include<string>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (;n--;)
    {
        string s;
        bool ch[26] = {false}, check = true, lower = false, upper = false;
        cin >> s;
        for(auto it = s.begin(); it != s.end(); ++it)
        {
            if (*it == *(it + 1))
            {
                check = false;
                break;
            }

            if (*it >= 'a' && *it <= 'z')
            {
                if (!lower) lower = true;

                if (ch[*it - 'a']) continue;
                else ch[*it - 'a'] = true;
            }
            else
            {
                if (!upper) upper = true;

                if (ch[*it - 'A']) continue;
                else ch[*it - 'A'] = true;
            }
        }

        for (int i = 0; i < 26; i++)
        {
            if (ch[i]) continue;
            else
            {
                check = false;
                break;
            }
        }
    
        if (check && lower && upper) cout << "no" << '\n';
        else cout << "yes" << '\n';
    }

    return 0;
}