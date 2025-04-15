#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// stringstream read()
// {
//     string s;
//     getline(cin, s);
//     return stringstream(s);
// }

void addLog(string s = "success", bool reset = false)
{
    static int count = 0;
    if(reset)
    {
        count = 0;
        return;
    }
    cout << "OpId #" <<  ++count << ": " << s << ".\n";
}

auto find(const deque<pair<int, ll>*> &dq, int x)
{
    for(auto it = dq.begin(); it != dq.end(); ++it)
        if ((**it).first == x) return it;
    return dq.end();
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    
    int t, n;
    pair<int, ll>* top;
    deque<pair<int, ll>*> dq;
    map<int, pair<int, ll>*> m;

    cin >> t;
    while(t--)
    {
        cin >> n;
        top = nullptr;
        addLog("", true);
        while(n--)
        {
            int u;
            string s;
            cin >> s;
            switch (s[0])
            {
            case 'A':
                cin >> u;
                if(m.count(u)) addLog("same likeness");
                else
                {
                    pair<int, ll>* np = new pair<int, ll> {u, 0};
                    dq.push_back(np);
                    m.insert({u, np});
                    addLog();
                }
                break;

            case 'C':
                cin >> u;
                if(s[1] == 'l')
                {
                    if(m.count(u))
                    {
                        auto p = m[u];
                        auto it = find(dq, u);
                        if(top == p) top = nullptr;
                        addLog("close " + to_string(u) + " with " + to_string(p->second));
                        dq.erase(it);
                        m.erase(u);
                        delete p;
                    }
                    else addLog("invalid likeness");
                }
                else if(s[2] == 'a')
                {
                    if(dq.empty()) addLog("empty");
                    else
                    {
                        auto p = top == nullptr ? dq.front() : top;
                        p->second += u;
                        addLog();
                    }
                }
                else
                {
                    if(m.count(u))
                    {
                        auto p = m[u];
                        auto it = find(dq, u);
                        dq.erase(it);
                        dq.emplace_front(p);
                        addLog();
                    }
                    else addLog("invalid likeness");
                }
                break;

            case 'R':
                cin >> u;
                if(u < 1 || u > dq.size()) addLog("out of range");
                else
                {
                    auto p = dq[u - 1];
                    dq.erase(dq.begin() + u - 1);
                    dq.emplace_front(p);
                    addLog();
                }
                break;

            case 'P':
                if(m.empty()) addLog("empty");
                else
                {
                    auto p = prev(m.end())->second;
                    auto it = find(dq, p->first);
                    dq.erase(it);
                    dq.emplace_front(p);
                    addLog();
                }
                break;

            case 'T':
                cin >> u;
                if(m.count(u))
                {
                    top = m[u];
                    addLog();
                }
                else addLog("invalid likeness");
                break;

            case 'U':
                if(top == nullptr) addLog("no such person");
                else
                {
                    top = nullptr;
                    addLog();
                }
                break;
                
            default:
                break;
            }
        }

        if(top != nullptr && top->second != 0) addLog("Bye " + to_string(top->first) + ": " + to_string(top->second));
        for(auto a: dq)
        {
            if(a != top && a->second != 0) addLog("Bye " + to_string(a->first) + ": " + to_string(a->second));
            delete a;
        }
        dq.clear();
        m.clear();
    }

    return 0;
}