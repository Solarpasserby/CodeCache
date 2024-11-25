// Anya and 1100

#include "iostream"
#include "unordered_map"
#include "string"

using namespace std;

int check(const int &n, const string &s)
{
    if (s[n] == '1')
    {
        if (s[n - 1] == '1' && s[n] == '1' && s[n + 1] == '0' && s[n + 2] == '0')
            return -1;
        else if (s[n] == '1' && s[n + 1] == '1' && s[n + 2] == '0' && s[n + 3] == '0')
            return 0;
        else
            return -1;
    }
    else
    {
        if (s[n - 2] == '1' && s[n - 1] == '1' && s[n] == '0' && s[n + 1] == '0')
            return -2;
        else if (s[n - 3] == '1' && s[n - 2] == '1' && s[n - 1] == '0' && s[n] == '0')
            return -3;
        else
            return -1;
    }
}

void query(string &s, int n, char v, unordered_map<int, char> &loc)
{
    if (s[n] == v)
        return;
    else
    {
        int offset = check(n, s);
        if (offset != -1)
        {
            loc.erase(n + offset);
        }
        s[n] = v;
        offset = check(n, s);
        if (offset != -1)
        {
            loc.insert({n + offset, '1'});
        }
    }
}

void locate(string s, unordered_map<int, char> &loc)
{
    for (int i = 0; i < s.size() - 3; i++)
    {
        if (s[i] == '1')
        {
            if (s[i + 1] == '1')
            {
                if (s[i + 2] == '0')
                {
                    if (s[i + 3] == '0')
                    {
                        loc.insert({i, '1'});
                    }
                    else
                    {
                        i += 2;
                    }
                }
            }
            else
            {
                i += 1;
            }
        }
    }
}

// int locate(const string &s)
// {
//     for (int i = 0; i < s.size() - 3; i++)
//     {
//         if (s[i] == '1')
//         {
//             if (s[i + 1] == '1')
//             {
//                 if (s[i + 2] == '0')
//                 {
//                     if (s[i + 3] == '0')
//                     {
//                         return i;
//                     }
//                     else
//                     {
//                         i += 2;
//                     }
//                 }
//             }
//             else
//             {
//                 i += 1;
//             }
//         }
//     }
//     return -1;
// }

int main()
{
    int t, q, n;
    char v;
    string s;
    cin >> t;
    unordered_map<int, char> loc;
    for (int i = 0; i < t; i++)
    {
        cin >> s;
        cin >> q;
        loc.clear();
        locate(s, loc);

        for (int j = 0; j < q; j++)
        {
            cin >> n >> v;
            query(s, n - 1, v, loc);
            if (!loc.empty())
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }
    return 0;
}

// int main()
// {
//     int t, q, n, loc;
//     char v;
//     string s;
//     cin >> t;
//     for (int i = 0; i < t; i++)
//     {
//         cin >> s;
//         cin >> q;
//         loc = locate(s);
//         for (int j = 0; j < q; j++)
//         {
//             cin >> n >> v;

//             if (s[n - 1] == v)
//             {
//                 if (loc != -1)
//                     cout << "YES" << endl;
//                 else
//                     cout << "NO" << endl;
//                 continue;
//             }

//             s[n - 1] = v;
//             if (n - 4 <= loc && loc <= n - 1)
//                 loc = locate(s);
//             else if (loc == -1)
//                 loc = locate(s);
//             if (loc != -1)
//                 cout << "YES" << endl;
//             else
//                 cout << "NO" << endl;
//         }
//     }
// }