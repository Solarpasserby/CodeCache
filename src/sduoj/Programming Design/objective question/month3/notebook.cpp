#include<bits/stdc++.h>

using namespace std;

struct TXT
{
    int mode; // 0 关闭 1 开启 2 选中
    string data, clipboard;
    size_t cur, subcur; //偏移

    TXT() : mode(0), cur(0), subcur(0) {}

    size_t getLineHead() const
    {
        size_t bg = cur;
        for(; bg > 0 && data[bg] != '\n'; --bg)
        return bg;
    }

    size_t getLineEnd() const
    {
        size_t ed = cur;
        for(; ed < data.size() && data[ed] != '\n'; ++ed)
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
            size_t offset, hd;
            hd = getLineHead();
            offset = cur - hd;
            if(cur != 0) --cur;
            cur = min(cur, getLineHead() + offset);
            break; 
        }    

        case 'D':
        {
            size_t offset;
            offset = cur - getLineHead();
            cur = getLineEnd();
            if(cur + 1 != data.size()) ++cur;
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
        if(mode == 2) remove();
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
            // size_t bg = min(cur, subcur);
            // if(bg + 1 != data.size()) ++bg;
            // clipboard = data.substr(bg, (cur > subcur ? cur - subcur : subcur - cur));
        }
        else mode = 1;
    }

    void find()
    {
        string s;
        cin >> s;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    return 0;
}