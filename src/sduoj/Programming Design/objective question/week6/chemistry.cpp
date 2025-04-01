#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

bool isupper(const char &c) { return c >= 'A' && c <= 'Z'; }
bool islower(const char &c) { return c >= 'a' && c <= 'z'; }
bool isnumeric(const char &c) { return c >= '0' && c <= '9'; }

struct Element
{
    map<string, ll> val;

    Element(const string &s) { val[s] = 1; }

    void operator+=(const Element &other)
    {
        for(const auto &p : other.val)
            val[p.first] += p.second;
    }

    void operator*=(const ll &a)
    {
        for(auto &p : val)
            p.second *= a;
    }

    bool cmp(const Element &other) { return val == other.val; }
};

stack<Element> stk;

void func(int l)
{
    while(stk.size() > l)
    {
        Element tmp = stk.top();
        stk.pop();
        stk.top() += tmp;
    }
}

ll getNum(const string &s)
{
    ll res = 0;
    for(int i = 0; i < s.length(); ++i)
        res = res * 10 + (s[i] - '0');
    return res;
}
 
void tackle(const string &eq, vector<string> &v)
{
    for(int i = 0; i < eq.length(); ++i)
    {
        if(isnumeric(eq[i]))
        {
            int j = 1;
            while(isnumeric(eq[i + j])) j++;
            v.push_back(eq.substr(i, j));
            i = i + j - 1;
        }
        else if(isupper(eq[i]))
        {
            if(i+1 < eq.length() && islower(eq[i+1])) v.push_back(eq.substr(i++, 2));
            else v.push_back(eq.substr(i, 1));
        }
        else if(eq[i] == '=')
        {
            v.push_back("+");
            v.push_back("=");
        }
        else v.push_back(eq.substr(i, 1));
    }
    v.push_back("+");
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while(n--)
    {
        string eq;
        vector<string> v;
        stack<int> lf;
        int limit = 1;
        ll coef = 0;
        cin >> eq;
        tackle(eq, v);
        for(const auto& it: v)
        {
            if(isnumeric(it[0]))
            {
                if(coef == 0) coef = getNum(it);
                else stk.top() *= getNum(it);
            }
            else if(isupper(it[0]))
            {
                if(coef == 0) coef = 1;
                stk.push(Element(it));
            }
            else if(it[0] == '+')
            {
                func(limit);
                stk.top() *= coef;
                coef = 0;
                ++limit;
            }
            else if(it[0] == '=')
            {
                func(1);
                limit = 2;
            }
            else if(it[0] == '(') lf.push(stk.size() + 1);
            else if(it[0] == ')') 
            {
                func(lf.top());
                lf.pop();
            }
        }

        func(2);
        Element tmp = stk.top();
        stk.pop();
        if(tmp.cmp(stk.top())) cout << "Y\n";
        else cout << "N\n";
        stk.pop();
    }

    return 0;
}