#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

struct DirF
{
    ll localStorage, entireStorage;
    ll localLimit, entireLimit;

    map<string, DirF*> dirFile;
    map<string, int> regFile;

    DirF(ll _ll = 0, ll _el = 0) : localStorage(0), entireStorage(0), localLimit(_ll), entireLimit(_el) {}
    ~DirF()
    {
        for (auto& it : dirFile)
            delete it.second;
        dirFile.clear();
    }

    static string readMainPath(const string &p)
    {
        if (p.length() == 1) return "";
        int l = 1;
        for(; l < p.length() && p[l] != '/'; ++l);
        return p.substr(1, l - 1);
    }

    static void cutMainPath(string &p)
    {
        int l = 1;
        for(; l < p.length() && p[l] != '/'; ++l);
        p.erase(0, l);
    }

    bool createRegFile(string &path, int size)
    {
        bool checkCreation = false;
        string fileName = readMainPath(path);
        cutMainPath(path);

        if(entireLimit && entireStorage + size > entireLimit) return false;

        if(path.empty())
        {
            if(dirFile.count(fileName)) return false;
            if(localLimit && localStorage + size > localLimit) return false;
            
            localStorage += size;
            entireStorage += size;
            regFile[fileName] += size;
            return true;
        }
        else if(!dirFile.count(fileName)) 
        {
            if(regFile.count(fileName)) return false;
            dirFile[fileName] = new DirF();
            checkCreation = true;
        }

        if(dirFile[fileName]->createRegFile(path, size))
        {
            entireStorage += size;
            return true;
        }
        else if(checkCreation)
        {
            delete dirFile[fileName];
            dirFile.erase(fileName);
        }
        return false;
    }

    pair<bool, ll> deleteFile(string &path)
    {
        pair<bool, ll> res(false, 0);
        string fileName = readMainPath(path);
        cutMainPath(path);

        if(path.empty())
        {
            if(dirFile.count(fileName))
            {
                res.first = true;
                res.second = dirFile[fileName]->entireStorage;
                entireStorage -= res.second;
                delete dirFile[fileName];
                dirFile.erase(fileName);
                return res;
            }
            else if(regFile.count(fileName))
            {
                res.first = true;
                res.second = regFile[fileName];
                localStorage -= res.second;
                entireStorage -= res.second;
                regFile.erase(fileName);
                return res;
            }
            else return res;
        }
        else if(dirFile.count(fileName))
        {
            res = dirFile[fileName]->deleteFile(path);
            if(res.first) entireStorage -= res.second;
            return res;
        }
        else return res;
    }

    bool assignDirFLimit(string &path, const ll &_ll, const ll &_el)
    {
        string fileName = readMainPath(path);
        cutMainPath(path);

        if(fileName.empty())
        {
            if(_ll != 0 && _ll < localStorage) return false;
            if(_el != 0 && _el < entireStorage) return false;
            localLimit = _ll;
            entireLimit = _el;
            return true;
        }
        else if(dirFile.count(fileName))
            return dirFile[fileName]->assignDirFLimit(path, _ll, _el);
        
        return false;
    }

    int readRegFile(string &path)
    {
        string fileName = readMainPath(path);
        cutMainPath(path);

        if(path.empty())
        {
            if(regFile.count(fileName))
                return regFile[fileName];
            return 0;
        }
        else if(dirFile.count(fileName))
            return dirFile[fileName]->readRegFile(path);
        else return 0;
    }
};


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    DirF dir;
    cin >> n;
    while(n--)
    {
        char op;
        int s;
        ll ld, lr;
        string cmd, cpy;
        cin >> op >> cmd;
        switch (op)
        {
        case 'C':
            cin >> s;
            cpy = cmd;
            if(dir.createRegFile(cmd, s - dir.readRegFile(cpy))) cout << "Y\n";
            else cout << "N\n";
            break;
        
        case 'R':
            dir.deleteFile(cmd);
            cout << "Y\n";
            break;

        case 'Q':
            cin >> ld >> lr;
            if(cmd.back() != '/') cmd += "/";
            if(dir.assignDirFLimit(cmd, ld, lr)) cout << "Y\n";
            else cout << "N\n";
            break;

        default:
            break;
        }
    }

    return 0;
}