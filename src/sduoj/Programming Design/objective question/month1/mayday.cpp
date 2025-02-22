#include<iostream>
#include<string>
#include<sstream>

using namespace std;

int main()
{
    int n, ans = 0, mcost = 114514;
    cin >> n;
    cin.ignore(114514, '\n');
    for(int i = 1; i <= n; i++)
    {
        int cost, c0, c1, c5;
        string s, ns;
        stringstream ss;
        getline(cin, s);
        ss << s;
        ss >> cost >> ns;

        c0 = 2, c1 = 1, c5 = 1;
        for(auto it = ns.begin(); it != ns.end(); it++)
        {
            switch (*it)
            {
            case '0':
                if (c0 > 0) --c0;
                break;

            case '1':
                if (c1 > 0) --c1;
                break;

            case '5':
                if (c5 > 0) --c5;
                break;
            
            default:
                break;
            }

            if(c0 || c1 || c5) continue;
            else
            {
                if (cost < mcost)
                {
                    mcost = cost;
                    ans = i;
                }
                break;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}