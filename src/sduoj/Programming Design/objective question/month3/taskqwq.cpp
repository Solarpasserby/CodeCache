#include<bits/stdc++.h>

using namespace std;

static unsigned int p = 1;

int myrand(void) {
    p = p * 1103515245 + 12345;
    return((unsigned int)(p/65536) % 100);
}

struct Task {
    int tick;
    int duration;
    string name;

    Task(int _tk, int _d, const string &_name)
        : tick(_tk), duration(_d), name(_name) {}
};

struct Workshop {
    string name;
    int ed = 1;
    
    struct Cmp {
        char policy;
        Cmp(char p) : policy(p) {}
        
        bool operator()(const Task* a, const Task* b) const {
            if (policy == 'T') { // TF
                return a->tick > b->tick;
            }
            else if (policy == 'S') { // SF
                if (a->duration != b->duration)
                    return a->duration > b->duration;
                return a->name < b->name;
            }
            else { // LF
                if (a->duration != b->duration)
                    return a->duration < b->duration;
                return a->name < b->name;
            }
        }
    };
    
    priority_queue<Task*, vector<Task*>, Cmp> pq;
    
    Workshop(string n, char p) : 
        name(n), pq(Cmp(p)) {}
};

unordered_map<string, Workshop*> mp;
vector<tuple<int, int, string>> res;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    while(n--) {
        string x, y;
        cin >> x >> y;
        mp[x] = new Workshop(x, y[0]);
    }
    while(m--) {
        int t, d, k;
        string s;
        cin >> t >> s >> d >> k;
        
        int q = 100 / k;
        string twksp;
        vector<string> tmp(k+1);
        for(int i = 1; i <= k; ++i) cin >> tmp[i];
        int j = 1;
        for(; q <= myrand() && j < k; ++j);
        twksp = tmp[j];

        Workshop* ws = mp[twksp];
        while(!ws->pq.empty() && ws->ed <= t) {
            Task* topTk = ws->pq.top();
            ws->pq.pop();
            ws->ed = max(ws->ed, topTk->tick) + topTk->duration;
            res.push_back({ws->ed, topTk->tick, topTk->name});
            delete topTk;
        }
        ws->pq.push(new Task(t, d, s));
    }

    for(auto [a, ws]: mp) {
        while(!ws->pq.empty()) {
            Task* topTk = ws->pq.top();
            ws->pq.pop();
            ws->ed = max(ws->ed, topTk->tick) + topTk->duration;
            res.push_back({ws->ed, topTk->tick, topTk->name});
            delete topTk;
        }
        delete ws;
    }

    sort(res.begin(), res.end());
    for(auto[a, b, c]: res) cout << a << ' ' << c << '\n';
    return 0;    
}