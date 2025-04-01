#include<bits/stdc++.h>

using namespace std;

enum Cmd {
    END,
    BEGIN,
    LOOP,
    OP
};

struct Poly {
    int coef[11];

    Poly() {
        for(int i = 0; i < 11; ++i)
            coef[i] = 0;
    }

    Poly(const Poly &other) {
        for(int i = 0; i < 11; ++i)
            coef[i] = other.coef[i];
    }

    void clear() {
        for(int i = 0; i < 11; ++i)
            coef[i] = 0;
    }

    void operator+=(const Poly &other)& {
        for(int i = 0; i < 11; ++i)
            coef[i] += other.coef[i];
    }

    void operator*=(int a)& {
        for(int i = 0; i < 11; ++i)
            coef[i] *= a;
    }

    void operator<<(int a)& {
        for(int i = 10; i >= a; --i)
            coef[i] = coef[i - a];
        for(int i = 0; i < a; ++i)
            coef[i] = 0;
    }
};

struct Ele {
    int number; // -1代表n
    Cmd command;

    Ele(int n, Cmd c) { number = n; command = c; }
};

stack<Poly> ans;
stack<Ele> stk;

int func(string s) {
    if(s[0] == 'n') return -1;
    int res = 0;
    for(auto it = s.begin(); it != s.end(); ++it)
        res = res * 10 + (*it - '0');
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    Poly p, q;
    bool isFirst = true;
    bool endFlag = false;

    do {
        string cmdType;
        string num;

        cin >> cmdType;

        switch (cmdType[0]) {
        case 'E':
            endFlag = true;
            while(!stk.empty()) {
                Ele tmp = stk.top();
                if(tmp.command == Cmd::OP)
                    p.coef[0] += tmp.number;
                else if(tmp.command == Cmd::LOOP) {
                    if(tmp.number == -1) p << 1;
                    else p *= tmp.number;
                }

                stk.pop();
                if(!stk.empty() && stk.top().command == Cmd::BEGIN) {
                    ans.push(Poly(p));
                    p.clear();
                }
                if(tmp.command == Cmd::LOOP) break;
            }
            break;

        case 'B':
            stk.push(Ele(0, Cmd::BEGIN));
            break;

        case 'L':
            cin >> num;
            stk.push(Ele(func(num), Cmd::LOOP));
            break;

        case 'O':
            cin >> num;
            stk.push(Ele(func(num), Cmd::OP));
            break;

        default:
            break;
        }
    } while(!endFlag);

    while(!ans.empty()) {
        q += ans.top();
        ans.pop();
    }

    cout << "Runtime = ";

    for(int i = 10; i > 0; -- i) {
        if(q.coef[i] == 1) {
            if(!isFirst) cout << '+';
            isFirst = false;
            cout << "n^" << i;
        }
        else if(q.coef[i] != 0) {
            if(!isFirst) cout << '+';
            isFirst = false;
            cout << q.coef[i] << "*n^" << i;
        }
    }

    if(isFirst) cout << q.coef[0] << '\n';
    else if(q.coef[0] != 0) cout << '+' << q.coef[0] << '\n';

    return 0;
}