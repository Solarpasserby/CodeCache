#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

static unsigned int p = 1;
int myrand(void) {
    p = p * 1103515245 + 12345;
    return((unsigned int)(p/65536) % 100);
}

struct Task {
    ll tick;
    ll duration;
    string name;

    Task(ll _tk, ll _d, string _name)
        : tick(_tk), duration(_d), name(_name) {}
};

struct Workshop {
    ll endTime = 0;
    Task* current;
    
    struct Cmp {
        char policy;
        Cmp(char pl) : policy(pl) {}
        
        bool operator()(const Task* a, const Task* b) const {
            if (policy == 'T') {
                if(a->tick != b->tick)
                    return a->tick > b->tick;
                return a->name < b->name;
            }
            else if (policy == 'S') {
                if (a->duration != b->duration)
                    return a->duration > b->duration;
                return a->name < b->name;
            }
            else {
                if (a->duration != b->duration)
                    return a->duration < b->duration;
                return a->name < b->name;
            }
        }
    };
    
    priority_queue<Task*, vector<Task*>, Cmp> pq;
    
    Workshop(char pl) : 
        current(nullptr), pq(Cmp(pl)) {}
};

unordered_map<string, Workshop*> mp;
vector<tuple<ll, ll, string>> res;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    while(n--) {
        string _name, _policy;
        cin >> _name >> _policy;
        mp[_name] = new Workshop(_policy[0]);
    }
    while(m--) {
        ll t, d;
        int k;
        string s;
        cin >> t >> s >> d >> k;

        string target;
        vector<string> tmp(k+1);
        for(int i = 1; i <= k; ++i) cin >> tmp[i];
        int pos = 1, chp = 100 / k;
        for(; pos < k && chp <= myrand(); ++pos);
        target = tmp[pos];

        Workshop* ws = mp[target];
        while(ws->current != nullptr) {
            ll ed = max(ws->endTime, ws->current->tick)+ws->current->duration;
            if(ed <= t) {
                res.push_back({ed, ws->current->tick, ws->current->name});
                ws->endTime = ed;
                delete ws->current;
                if(ws->pq.empty()) ws->current = nullptr;
                else {
                    ws->current = ws->pq.top();
                    ws->pq.pop();
                }
            }
            else break;
        }
        if(ws->current == nullptr) ws->current = new Task(t, d, s);
        else ws->pq.push(new Task(t, d, s));
    }
    for(auto [_a, ws]: mp) {
        while(ws->current != nullptr) {
            ll ed = max(ws->endTime, ws->current->tick)+ws->current->duration;
            res.push_back({ed, ws->current->tick, ws->current->name});
            ws->endTime = ed;
            delete ws->current;
            if(ws->pq.empty()) ws->current = nullptr;
            else {
                ws->current = ws->pq.top();
                ws->pq.pop();
            }
        }
        delete ws;
    }

    sort(res.begin(), res.end());
    for(auto[_a, _b, _c]: res) cout << _a << ' ' << _c << '\n';

    return 0;
}