#include<iostream>
#include<string>

using namespace std;

int main()
{
    bool isRight = true;
    string s;
    getline(cin, s);
    for (int i = 0; i < s.length(); ++i)
    {
        if (i % 2 == 0 && s[i] >= 'a' && s[i] <= 'z' || i % 2 == 1 && s[i] >= 'A' && s[i] <= 'Z') continue;
        else 
        {
            isRight = false;
            break;
        }
    }

    if (isRight) cout << "Yes" << '\n';
    else cout << "No" << '\n';

    return 0;
}