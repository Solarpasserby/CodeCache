#include<iostream>
#include<string>
#include<sstream>

using namespace std;

bool func(string l, string r)
{
    if (l > r)
    {
        int len = min(l.length(), r.length());
        if (l.substr(0, len) == r.substr(0, len))
        {
            if(l[len] < r[0]) return false;
            else if(l[len] > r[0]) return true;
            else return func(l.substr(len, l.length() - len), r);
        }
        else return true;
    }
    else if (l == r) return false;
    else
    {
        int len = min(l.length(), r.length());
        if (l.substr(0, len) == r.substr(0, len))
        {
            if(r[len] < l[0]) return true;
            else if(r[len] > l[0]) return false;
            else return !(func(r.substr(len, r.length() - len), l));
        }
        else return false;
    }
}

int main()
{
    int n;
    string L, nums[30];
    stringstream ss;
    cin >> n;

    cin.ignore(114514, '\n');
    getline(cin, L);
    ss << L;
    for(int i = 1; i <= n; i++)
        ss >> nums[i];

    for(int i = 1; i <= n; i++)
    {
        int m = i;
        for(int j = i + 1; j <= n; j++)
            if (func(nums[j], nums[m])) m = j;
        swap(nums[m], nums[i]);
    }

    for(int i = 1; i <= n; i++)
        cout << nums[i];

    cout << '\n';

    return 0;
}