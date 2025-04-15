#include <bits/stdc++.h>

using namespace std;

stringstream read()
{
    string s;
    getline(cin, s);
    return stringstream(s);
}

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

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    
    int t, n, top, front;
    vector<pair<int, int>> v;
    map<int, int> m;

    read() >> t;
    while(t--)
    {
        read() >> n;
        top = -1, front = 0;
        v.clear();
        m.clear();
        addLog("", true);
        while(n--)
        {
            int u;
            string s;
            stringstream ss = read();
            ss >> s;
            switch (s[0])
            {
            case 'A':
                ss >> u;
                if(m.count(u)) addLog("same likeness");
                else
                {
                    v.emplace_back(u, 0);
                    m.insert({u, v.size() - 1});
                    while(front < v.size() && v[front].first == -1) ++front;
                    addLog();
                }
                break;

            case 'C':
                ss >> u;
                if(s[1] == 'l')
                {
                    if(m.count(u))
                    {
                        int loc = m[u];
                        if(top == loc) top = -1;
                        addLog("close " + to_string(u) + " with " + to_string(v[loc].second));
                        v[loc] = {-1, -1};
                        m.erase(u);
                        while(front < v.size() && v[front].first == -1) ++front;
                    }
                    else addLog("invalid likeness");
                }
                else if(s[2] == 'a')
                {
                    int loc = top == -1 ? front : top;
                    if(loc != v.size())
                    {
                        v[loc].second += u;
                        addLog();
                    } 
                    else addLog("empty");
                }
                else
                {
                    if(m.count(u))
                    {
                        int loc = m[u];
                        if(top == front) top = loc;
                        else if(top == loc) top = front;
                        swap(m[v[front].first], m[u]);
                        swap(v[front], v[loc]);
                        addLog();
                    }
                    else addLog("invalid likeness");
                }
                break;

            case 'R':
                ss >> u;
                if(u < 1) addLog("out of range");
                else
                {
                    int loc = front;
                    for(; loc < v.size(); ++loc)
                    {
                        if(v[loc].first != -1) --u;
                        if(u < 1) break;
                    }
                    if(loc == v.size()) addLog("out of range");
                    else
                    {
                        if(top == front) top = loc;
                        else if(top == loc) top = front;
                        swap(m[v[front].first], m[v[loc].first]);
                        swap(v[front], v[loc]);
                        addLog();
                    }
                }
                break;

            case 'P':
                if(m.empty()) addLog("empty");
                else
                {
                    int loc = prev(m.end())->second;
                    if(top == front) top = loc;
                    else if(top == loc) top = front;
                    swap(m[v[front].first], m[v[loc].first]);
                    swap(v[front], v[loc]);
                    addLog();
                }
                break;

            case 'T':
                ss >> u;
                if(m.count(u))
                {
                    top = m[u];
                    addLog();
                }
                else addLog("invalid likeness");
                break;

            case 'U':
                if(top == -1) addLog("no such person");
                else
                {
                    top = -1;
                    addLog();
                }
                break;
                
            default:
                break;
            }
        }

        if(top != -1 && v[top].second != 0) addLog("Bye " + to_string(v[top].first) + ": " + to_string(v[top].second));
        for(; front < v.size(); ++front)
        {
            auto tmp = v[front];
            if(tmp.first == top) continue;
            if(tmp.first != -1 && tmp.second != 0)
                addLog("Bye " + to_string(tmp.first) + ": " + to_string(tmp.second));
        }
    }

    return 0;
}