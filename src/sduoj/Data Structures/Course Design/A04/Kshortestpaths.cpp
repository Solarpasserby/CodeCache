#include<bits/stdc++.h>

using namespace std;

const int INF = 1e7;
const int LIM = 1024;
const int TOPRANK = 5;

uint16_t n, a, b;
int m, k;
uint16_t multicnt[LIM][LIM];
vector<vector<pair<uint16_t, int>>> e, re;
vector<vector<uint16_t>> ansPath;
vector<int> ansG;

vector<int> dijsktra(uint16_t s)
{
    vector<int> dis(n + 3, INF);
    vector<bool> done(n + 3, false);
    priority_queue<pair<int, uint16_t>, vector<pair<int, uint16_t>>, greater<>> pq;

    dis[s] = 0;
    pq.emplace(0, s);
    while(!pq.empty())
    {
        auto [w, v] = pq.top();
        pq.pop();
        if(done[v]) continue;
        done[v] = true;
        for(const auto& [p, q]: re[v])
        {
            if(done[p]) continue;
            if(dis[p] > dis[v] + q)
            {
                dis[p] = dis[v] + q;
                pq.emplace(dis[p], p);
            } 
        }
    }

    return dis;
}

void printMinLexOrderPath() {
    int bg = k - 1, ed = k - 1, minP = k - 1;

    while (ed < ansG.size() && ansG[ed] == ansG[k - 1]) ++ed;
    while (bg >= 0 && ansG[bg] == ansG[k - 1]) --bg;

    if (bg + 1 >= ed) return;
    sort(ansPath.begin() + bg + 1, ansPath.begin() + ed);

    for (int i = 0; i < ansPath[k - 1].size() - 1; ++i) {
        cout << ansPath[k - 1][i] << '-';
    }
    cout << ansPath[k - 1].back() << "   " << ansG[k - 1] << '\n';
    for (int i = 0; i < ansPath[0].size() - 1; ++i) {
        cout << ansPath[0][i] << '-';
    }
    cout << ansPath[0].back() << "   " << ansG[0] << '\n';
}

void analyze()
{
    unordered_map<string, int> mp;
    for(auto &a: ansPath)
    {
        int sz = a.size();
        for(int i = 0; i < sz; ++i)
        {
            stringstream ss;
            for(int j = i; j < sz; ++j)
            {
                if(j != i) ss << "-";
                ss << a[j];
                ++mp[ss.str()];
            }
        }
    }

    vector<pair<string, int>> vec(mp.begin(), mp.end());
    sort(vec.begin(), vec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        if (a.second != b.second) {
            return a.second > b.second;
        } else {
            return a.first < b.first;
        }
    });

    int topPoint = TOPRANK, topSubpath = TOPRANK;
    vector<pair<string, int>> tpt, tsp;
    for(auto& a: vec)
    {
        if(a.first.size() <= 3 && a.first[1] != '-') { if(topPoint-- > 0) tpt.push_back(a); }
        else if(topSubpath-- > 0) tsp.push_back(a);
        else if(topPoint == 0) break;
    }
    for(auto& a: tpt)
        cout << a.first << ": " << a.second << "  ";
    cout << '\n';
    for(auto& a: tsp)
        cout << a.first << ": " << a.second << "  ";
    cout << '\n';
}

//总是觉得对于空间的浪费比较大，以后在想想有没有更好的办法
//适当优化了一下，不得不妥协
struct State
{
    int f, g;
    bitset<LIM> visited;
    vector<uint16_t> path;

    State(int _f, int _g, int _u) : f(_f), g(_g)
    {
        path.push_back(_u);
        visited.set(_u);
    }

    State(int _f, int _g, int _u, const State& _stt) : f(_f), g(_g)
    {
        path = _stt.path;
        visited = _stt.visited;
        path.push_back(_u);
        visited.set(_u);
    }

    void printPath() const
    {
        for(int i = 0; i < path.size() - 1; ++i)
            cout << path[i] << '-';
        cout << path.back() << '\n';
    }

    bool operator<(const State& other) const
    {
        if(f == other.f)
        {
            auto it = path.begin(), oit = other.path.begin();
            for(; it != path.end() || oit != other.path.begin(); ++it, ++oit)
                if(*it > *oit) return true;
                else if(*it < *oit) return false;
            if(it == path.end()) return false;
            else return true;
        }
        return f > other.f;
    }
};

//最后的挣扎
//目前似乎是有效的...
struct Node
{
    int f, g;
    uint16_t current, length;
    Node* pre;
    bitset<LIM> visited;

    Node() {};
    Node(int _f, int _g, uint16_t _u, Node* _node = nullptr) 
        : f(_f), g(_g), current(_u), pre(_node)
    {
        if(_node != nullptr)
        {
            length = _node->length + 1;
            visited = _node->visited;
        }
        else length = 1;
        visited.set(_u);
    }

    vector<uint16_t> getPath() const
    {
        const Node* cur = this;
        vector<uint16_t> res(length);
        for(int i = length - 1; i >= 0; --i)
        {
            if(cur == nullptr) break;
            res[i] = cur->current;
            cur = cur->pre;
        }
        return res;
    }

    void printPath() const
    {
        vector<uint16_t> path = getPath();
        for(int i = 0; i < path.size() - 1; ++i)
            cout << path[i] << '-';
        cout << path.back() << '\n';
    }

    bool operator<(const Node& other) const { return f > other.f; }
    Node& operator=(const Node& other) {
        if (this == &other) return *this; // 防止自我赋值
    
        f = other.f;
        g = other.g;
        current = other.current;
        length = other.length;
        pre = other.pre;
        visited = other.visited;
    
        return *this;
    }
};

struct NodePool {
    deque<Node> block;
    int index = 0;

    Node* allocate(int f, int g, int u, Node* pre) {
        if (index >= block.size()) {
            block.resize(block.size() + 256); // 每次预分配256个对象
        }
        Node* obj = &block[index++];
        *obj = Node(f, g, u, pre);
        return obj;
    }

    void reset() { index = 0; block.clear(); }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f; // 按照key值从小到大排序
    }
};


void kShortestPaths(uint16_t s, uint16_t t)
{
    vector<int> h = dijsktra(t);

    int cnt = 0;
    priority_queue<State> pq;

    pq.emplace(h[s], 0, s);
    while(!pq.empty())
    {
        State stt = pq.top();
        pq.pop();

        uint16_t v = stt.path.back();
        if(v == t)
        {
            ++cnt;
            if(cnt == k) { stt.printPath(); break; }
            continue;
        }

        for(const auto& [p, q]: e[v])
        {
            if(stt.visited[p]) continue;
            pq.emplace(stt.g + q + h[p], stt.g + q, p, stt);
        }
    }
}

void optimizedKShortestPaths(uint16_t s, uint16_t t)
{
    vector<int> h = dijsktra(t);

    int cnt = 0, maxG = 0;
    priority_queue<Node*, vector<Node*>, Compare> pq;
    NodePool np;

    pq.push(np.allocate(h[s], 0, s, nullptr));
    while(!pq.empty())
    {
        Node* cur = pq.top();
        pq.pop();

        uint16_t v = cur->current;
        if(v == t)
        {
            ++cnt;
            ansPath.push_back(cur->getPath());
            ansG.push_back(cur->g);
            if(cnt > k && maxG < cur->g || pq.empty()) 
            {
                printMinLexOrderPath();
                analyze();
                break;
            }
            maxG = max(cur->g, maxG);
            continue;
        }

        for(const auto& [p, q]: e[v])
        {
            if(cur->visited[p]) continue;
            pq.push(np.allocate(cur->g + q + h[p], cur->g + q, p, cur));
        }
    }
}

void multiKShortestPaths()
{
    priority_queue<Node*, vector<Node*>, Compare> pq;
    NodePool np;

    for(uint16_t i = 1; i <= n; ++i)
        pq.push(np.allocate(0, i, i, nullptr)); //取巧g为起点
    while(!pq.empty())
    {
        Node* cur = pq.top();
        pq.pop();

        uint16_t v = cur->current;
        uint16_t start = cur->g;

        if(multicnt[start][v] >= k) continue;
        else if(++multicnt[start][v] == k)
        {
            cout << start << "->" << v << ": ";
            cur->printPath();
        }

        if(cur->visited.count() >= n) continue;
        for(const auto& [p, q]: e[v])
        {
            if(cur->visited[p]) continue;
            pq.push(np.allocate(cur->f + q, start, p, cur));
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> m >> k >> a >> b;
    e.resize(n + 3), re.resize(n + 3);
    while(m--)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        re[v].emplace_back(u, w);
    }

    //kShortestPaths(a, b);
    optimizedKShortestPaths(a, b);
    multiKShortestPaths();

    return 0;
}