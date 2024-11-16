// Anya and 1100

#include "iostream"
#include "vector"
#include "string"

using namespace std;

// int search(int n, const vector<int> &loc)
// {
//     if (loc.empty())
//         return -1;

//     int i = 0;
//     for (; loc[i] <= n && i < loc.size(); i++);
//     return i - 1;
// }

// int check(const int &n, const string &s)
// {
//     if (s[n] == '1')
//     {
//         if (s[n - 1] == '1' && s[n] == '1' && s[n + 1] == '0' && s[n + 2] == '0')
//             return 1;
//         else if (s[n] == '1' && s[n + 1] == '1' && s[n + 2] == '0' && s[n + 3] == '0')
//             return 0;
//         else
//             return -1;
//     }
//     else
//     {
//         if (s[n - 2] == '1' && s[n - 1] == '1' && s[n] == '0' && s[n + 1] == '0')
//             return 2;
//         else if (s[n - 3] == '1' && s[n - 2] == '1' && s[n - 1] == '0' && s[n] == '0')
//             return 3;
//         else
//             return -1;
//     }
// }

// void query(string &s, int n, char v, vector<int> &loc)
// {
//     if (s[n] == v)
//         return;
//     else
//     {
//         s[n] = v;
//         int offset = check(n, s);
//         int nearest = search(n, loc);
//         if (nearest == -1)
//         {
//             if (offset == -1)
//                 return;
//             else
//                 loc.insert(loc.begin(), n - offset);
//         }
//         else
//         {
//             if (loc[nearest] >= n - 3)
//             {
//                 if (offset == -1)
//                     loc.erase(loc.begin() + nearest);
//                 else
//                     loc[nearest] = n - offset;
//             }
//             else
//             {
//                 if (offset == -1)
//                     return;
//                 else
//                     loc.insert(loc.begin() + nearest + 1, n - offset);
//             }
//         }
//     }
// }

// void locate(string s, vector<int> &loc)
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
//                         loc.push_back(i);
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
// }

int locate(const string &s)
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
                        return i;
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
    return -1;
}

// int main()
// {
//     int t, q, n;
//     char v;
//     string s;
//     cin >> t;
//     vector<int> loc;
//     for (int i = 0; i < t; i++)
//     {
//         cin >> s;
//         cin >> q;
//         loc.clear();
//         locate(s, loc);

//         for (int j = 0; j < q; j++)
//         {
//             cin >> n >> v;
//             query(s, n - 1, v, loc);
//             if (!loc.empty())
//                 cout << "YES" << endl;
//             else
//                 cout << "NO" << endl;
//         }
//     }
//     return 0;
// }

int main()
{
    int t, q, n, loc;
    char v;
    string s;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        cin >> s;
        cin >> q;
        loc = locate(s);
        for (int j = 0; j < q; j++)
        {
            cin >> n >> v;

            if (s[n - 1] == v)
            {
                if (loc != -1)
                    cout << "YES" << endl;
                else
                    cout << "NO" << endl;
                continue;
            }

            s[n - 1] = v;
            if (n - 4 <= loc && loc <= n - 1)
                loc = locate(s);
            else if (loc == -1)
                loc = locate(s);
            if (loc != -1)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }
}