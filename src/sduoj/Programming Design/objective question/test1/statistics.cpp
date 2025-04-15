#include<bits/stdc++.h>

using namespace std;

int times[30];

int main()
{
    int cnt = 0;
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    for(int i = 0; i < s.length(); ++i)
    {
        if(times[s[i] - 'a'] == 0) ++cnt;
        ++times[s[i] - 'a'];
    }

    for(int i = 0; i <cnt; ++i)
    {
        int c, m;
        c = m = 0;
        for(int j = 0; j < 26; ++j)
        {
            if (times[j] > m)
            {
                c = j;
                m = times[j];
            }
        }
        cout << (char)(c + 'a') << ' ';
        times[c] = 0;
    }
    cout << '\n';

    return 0;
}