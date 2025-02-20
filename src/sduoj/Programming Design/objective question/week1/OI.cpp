#include<iostream>
#include<sstream>
#include<string>

using namespace std;

typedef long long ll;

#define OI7

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll a, b;
    
#ifdef OI1
    cin >> n;

    while(n--)
    {
        cin >> a >> b;
        cout << a + b << '\n';
    }
#endif

#ifdef OI2
    for(;;)
    {
        cin >> a >> b;
        if (a || b) cout << a + b << '\n';
        else break;
    }
#endif

#ifdef OI3
    while (cin >> a >> b)
        cout << a + b << '\n';
#endif

#ifdef OI4
    a = 0;
    cin >> n;
    while (n != 0)
    {
        while(n--)
        {
            cin >> b;
            a += b;
        }
        cout << a << '\n';
        a = 0;
        cin >> n;
    }
#endif

#ifdef OI5
    a = 0;
    cin >> n;
    while (n--)
    {
        int m;
        cin >> m;
        while(m--)
        {
            cin >> b;
            a += b;
        }
        cout << a << '\n';
        a = 0;
    }
#endif

#ifdef OI6
    string s;
    
    while (getline(cin, s) && !s.empty())
    {
        stringstream ss;
        ss << s;
        a = 0;
        while (ss >> b)
            a += b;
        cout << a << '\n';
    }
#endif

#ifdef OI7
    string s;
        
    while (cin.peek() != EOF && getline(cin, s))
    {
        stringstream ss;
        ss <<s;
        a = 0;
        while (ss >> hex >> b)
            a += b;
        cout << a << '\n';
    }
#endif

    return 0;
}