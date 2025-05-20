#include<bits/stdc++.h>

using namespace std;

struct TXT
{
    int mode; // 0 关闭 1 开启 2 选中
    string data, clipboard;
    size_t cur, subcur; //偏移

    TXT() : mode(0), cur(0), subcur(0)
        { data.push_back('#'); /*应当可以是任意字符*/ }

    size_t getLineHead() const
    {
        size_t bg = cur;
        for(; bg > 0 && data[bg] != '\n'; --bg);
        return bg;
    }

    size_t getLineEnd() const
    {
        size_t ed = cur;
        if(data[ed] == '\n') ++ed;
        for(; ed < data.size() && data[ed] != '\n'; ++ed);
        return ed - 1;
    }

    void curMove()
    {
        string cmd;
        cin >> cmd;
        if(mode == 2) mode = 0;
        switch (cmd[0])
        {
        case 'H':
            cur = getLineHead();
            break;

        case 'E':
            cur = getLineEnd();
            break;

        case 'U':
        {
            size_t offset, tmp;
            tmp = getLineHead();
            offset = cur - tmp;
            if(tmp != 0) --tmp;
            else return;
            cur = tmp;
            cur = min(cur, getLineHead() + offset);
            break; 
        }    

        case 'D':
        {
            size_t offset, tmp;
            offset = cur - getLineHead();
            tmp = getLineEnd();
            if(tmp + 1 != data.size()) ++tmp;
            else return;
            cur = tmp;
            cur = min(getLineEnd(), cur + offset);
            break; 
        } 

        case 'L':
            if(cur != 0) --cur;
            break;

        case 'R':
            if(cur + 1 != data.size()) ++cur;
            break;
        
        default:
            break;
        }
    }

    void insert()
    {
        string cmd;
        cin >> cmd;

        if(mode == 2)
        {
            size_t bg = min(cur, subcur);
            if(bg + 1 != data.size()) ++bg;
            data.erase(bg, (cur > subcur ? cur - subcur : subcur - cur));
            cur = min(cur, subcur);
            mode = 0;
        }

        switch (cmd[0])
        {
        case 'C':
        {   
            char c;
            cin >> c;
            data.insert(++cur, 1, c); 
            break;
        }

        case 'E':
            data.insert(++cur, 1, '\n');
            break;

        case 'S':
            data.insert(++cur, 1, ' ');
            break;

        case 'P':
            data.insert(cur + 1, clipboard);
            cur += clipboard.size();
            break;
        
        default:
            break;
        }
    }

    void remove()
    {
        string cmd;
        cin >> cmd;

        if(mode == 2)
        {
            size_t bg = min(cur, subcur);
            if(bg + 1 != data.size()) ++bg;
            data.erase(bg, (cur > subcur ? cur - subcur : subcur - cur));
            cur = min(cur, subcur);
            mode = 0;
            return;
        }

        switch (cmd[0])
        {
        case 'D':
            if(cur + 1 != data.size()) data.erase(cur + 1, 1);
            break;

        case 'B':
            if(cur != 0) data.erase(cur--, 1);
            break;
        
        default:
            break;
        }
    }

    void shift()
    {
        if(mode == 0)
        {
            mode = 1;
            subcur = cur;
        }
        else if(mode == 1)
        {
            if(cur != subcur) mode = 2;
            else mode = 0;
        }
        else mode = 1;
    }

    void find() const
    {
        string s;
        cin >> s;

        size_t bg, ed, cnt = 0;
        bg = mode == 2 ? min(cur, subcur) : 0;
        ed = mode == 2 ? max(cur, subcur) : data.size() - 1;
        if(bg + 1 != data.size())
        {
            for(int i = bg + 1; i <= ed; ++i)
            {
                int j = 0;
                if(i + s.size() - 1 > ed) break; //及时终止条件
                while(j < s.size() && s[j] == data[i + j]) ++j;
                if(j == s.size()) ++cnt;
            }
        }
        cout << cnt << '\n';
    }

    void count() const
    {
        size_t bg, ed, cnt = 0;
        bg = mode == 2 ? min(cur, subcur) : 0;
        ed = mode == 2 ? max(cur, subcur) : data.size() - 1;
        if(bg + 1 != data.size())
        {
            for(int i = bg + 1; i <= ed; ++i)
                if(data[i] != '\n' && data[i] != ' ') ++cnt;
        }
        cout << cnt << '\n';
    }
    
    void cpy()
    {
        size_t bg, ed;
        bg = mode == 2 ? min(cur, subcur) : getLineHead();
        ed = mode == 2 ? max(cur, subcur) : getLineEnd();
        if(bg + 1 == data.size() || bg == ed) return;
        clipboard.clear();
        clipboard = data.substr(bg + 1, ed - bg);
    }

    void printData()
    {
        if (data.size() > 1) cout << data.substr(1) << '\n';
        else cout << '\n';
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    TXT t;
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        string op;
        cin >> op;
        switch (op[0])
        {
        case 'C':
            if(op[2] == 'P') t.cpy();
            else
            {
                t.count();
            }
            break;

        case 'F':
            t.find();
            break;

        case 'I':
            t.insert();
            break;

        case 'M':
            t.curMove();
            break;

        case 'P':
            t.printData();
            break;

        case 'R':
            t.remove();
            break;

        case 'S':
            t.shift();
            break;
        
        default:
            break;
        }
    }

    return 0;
}