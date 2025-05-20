#include <bits/stdc++.h>

using namespace std;

static unsigned int p = 1;

int myrand(void)
{
    p = p * 1103515245 + 12345;
    return ((unsigned int)(p / 65536) % 100);
}

enum TaskType {
    TF,
    SF,
    LF,
    UNDFINED
};

struct Task {
    int tick;
    int duration;
    TaskType type;
    string name;

    Task(int _tk, int _d, TaskType _tp, const string &_name)
        : tick(_tk), duration(_d), type(_tp), name(_name) {}
};

struct Cmp {
    bool operator()(const Task &a, const Task &b)
    {
        if (a.type != b.type)
            exit(114514);
        switch (a.type) {
        case TaskType::TF:
            return a.tick > b.tick;
            break;

        case TaskType::SF:
            if (a.duration == b.duration)
                return a.name < b.name;
            else
                return a.duration > b.duration;
            break;

        case TaskType::LF:
            if (a.duration == b.duration)
                return a.name < b.name;
            else
                return a.duration < b.duration;
            break;

        default:
            exit(114514);
            break;
        }
    }
};

struct Workshop {
    TaskType type;
    pair<pair<int, string>, int> currentTask; // 当前任务： 任务名、起始时间、剩余完成时间
    priority_queue<Task, vector<Task>, Cmp> pq;

    Workshop(const string &_tt = "TF")
    {
        currentTask = {{-1, ""}, 0};
        if (_tt == "TF")
            type = TaskType::TF;
        else if (_tt == "SF")
            type = TaskType::SF;
        else if (_tt == "LF")
            type = TaskType::LF;
        else
            exit(114514);
    }
};

unordered_map<string, Workshop> mp;
queue<pair<Task, string>> q;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    while (n--) {
        string x, y;
        cin >> x >> y;
        mp[x] = Workshop(y);
    }
    while (m--) {
        int t, d, k;
        string s;
        cin >> t >> s >> d >> k;
        vector<string> tmp(k);
        for (int i = 0; i < k; ++i)
            cin >> tmp[i];

        int ch = 100 / k;
        for (const string &str : tmp)
            if (ch > myrand() || str == tmp.back()) {
                q.emplace(Task(t, d, TaskType::UNDFINED, s), str);
                break;
            }
    }

    int timeTick = 0;
    while (true) {
        ++timeTick;
        bool chend = true;
        vector<pair<int, string>> output;
        for (auto &[a, b] : mp) {
            if (b.currentTask.first.first == -1 && b.pq.empty())
                continue;
            if (--b.currentTask.second <= 0) {
                if (b.currentTask.first.first != -1) {
                    output.emplace_back(b.currentTask.first);
                    b.currentTask = {{-1, ""}, 0};
                }
                if (!b.pq.empty()) {
                    auto tmp = b.pq.top();
                    b.pq.pop();
                    b.currentTask.first = {tmp.tick, tmp.name};
                    b.currentTask.second = tmp.duration;
                }
            }

            chend = false;
        }

        if (q.empty() && chend)
            break;

        sort(output.begin(), output.end());
        for (auto [a, b] : output)
            cout << timeTick << ' ' << b << '\n';

        while (!q.empty() && q.front().first.tick == timeTick) {
            auto qf = q.front();
            auto it = mp.find(qf.second);
            q.pop();
            qf.first.type = it->second.type;
            if (it->second.currentTask.first.first == -1) {
                it->second.currentTask.first = {qf.first.tick, qf.first.name};
                it->second.currentTask.second = qf.first.duration;
            } else
                it->second.pq.emplace(qf.first);
        }
    }

    return 0;
}