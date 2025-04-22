#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>

#define DIRMANAGER

struct Directory
{
    std::map<std::string, Directory *> subDir;
    std::set<std::string> files;
    Directory *father;
    std::string name;

    Directory(const std::string &_name, Directory* _father = nullptr) : name(_name), father(_father) {};
    ~Directory()
    {
        files.clear();
        for(auto& [a, b]: subDir)
            delete b;
        subDir.clear();
    }

    std::string getAbsPath()
    {
        if(this->father == nullptr) return "/";

        std::stack<std::string> stk;
        Directory *f = this;
        std::string path;
        while (f->father != nullptr)
        {
            stk.push(f->name);
            f = f->father;
        }
        while (!stk.empty())
        {
            path += "/" + stk.top();
            stk.pop();
        }
        return path;
    }

    Directory* copy(Directory* father = nullptr)
    {
        Directory* cpyDir = new Directory(this->name, father);
        for(auto& a: files) cpyDir->files.insert(a);
        for(auto& [a, b]: subDir) cpyDir->subDir.emplace(a, b->copy(this));
        return cpyDir;
    }

    bool createFile(const std::string &s)
    {
        if(subDir.count(s)) return false;
        return files.insert(s).second;
    }
    bool removeFile(const std::string &s) { return files.erase(s); }

    Directory* createDir(const std::string &s)
    {
        if(files.count(s)) return nullptr;
        Directory* newDir = new Directory(s, this);
        bool ch = subDir.emplace(s, newDir).second;
        if (!ch) delete newDir;
        return (ch ? newDir : nullptr);
    }
    bool pasteDir(Directory* dir)
    {
        if(files.count(dir->name)) return false;
        bool ch = subDir.emplace(dir->name, dir).second;
        if (!ch) delete dir;
        return ch;
    }
    bool removeDir(const std::string &s)
    {
        auto it = subDir.find(s);
        if(it != subDir.end())
        {
            delete it->second;
            subDir.erase(it);
            return true;
        }
        return false;
    }

    std::pair<bool, std::set<std::string>::iterator> copyFile(const std::string &s)
    {
        auto it = files.find(s);
        return {it != files.end(), it};
    }
    std::pair<Directory*, std::map<std::string, Directory*>::iterator> copyDir(const std::string &s)
    {
        auto it = subDir.find(s);
        if(it != subDir.end()) return {it->second->copy(), it};
        return {nullptr, it};
    }
};

struct CatalogManager
{
    Directory *root, *current;
    std::string path;

    struct JSONParser
    {
        const std::string* JSONStr;
        int end;

        JSONParser(const std::string& json, int _end) : JSONStr(&json), end(_end) {};

        void skip(int& pos) const { while(pos < end && (*JSONStr)[pos] != ':') ++pos; }
        std::string getName(int& pos) const
        {
            int ns;
            while(pos < end && (*JSONStr)[pos] != '\"')
            {
                if((*JSONStr)[pos] == ']') return "";
                ++pos;
            }
            ns = ++pos;
            while(pos < end && (*JSONStr)[pos] != '\"') ++pos;
            return JSONStr->substr(ns, pos++ - ns);
        }
        int getDirObjectSize(int& pos) const
        {
            while(pos < end && (*JSONStr)[pos] != '{')
            {
                if((*JSONStr)[pos] == ']') return 0;
                ++pos;
            }
            int s = pos + 1, sign = 0;
            while(s < end && ((*JSONStr)[s] != '}' || sign))
            {
                if((*JSONStr)[s] == '{') ++sign;
                else if((*JSONStr)[s] == '}') --sign;
                ++s;
            }
            return (s - pos + 1);
        }
    };

    CatalogManager()
    {
        Directory* newDir = new Directory("root");
        current = root = newDir;
        path = "/";
    }

    std::pair<std::string, Directory*> loadDir(const std::string& json, int& pos, int size, Directory* father = nullptr)
    {
        JSONParser jp(json, pos + size);
        jp.skip(pos);
        std::string dname = jp.getName(pos);
        Directory* newDir = new Directory(dname, father);
        if(dname.back() == '*') { newDir->name.pop_back(); current = newDir; }

        jp.skip(pos);
        while(true)
        {
            std::string fname = jp.getName(pos);
            if(fname.empty()) break;
            newDir->files.insert(fname);
        }

        int s;
        jp.skip(pos);
        while((s = jp.getDirObjectSize(pos)) != 0)
        {
            int tmp = pos;
            newDir->subDir.emplace(loadDir(json, pos, s, newDir));
            pos = tmp + s;
        }

        return {newDir->name, newDir};
    }

    void writeDir(Directory* addr, std::ostream& out, int indent = 0)
    {
        std::string indentStr(indent, ' '); 
        out << indentStr << "{\n";
        out << indentStr << "  \"name\": \"" << addr->name
            << (addr == current ? "*" : "") << "\",\n";

        bool first = true;
        out << indentStr << "  \"files\": [";
        for(const auto &a: addr->files)
        {
            if(first) first = false;
            else out << ", ";
            out << "\"" << a << "\"";
        }
        out << "],\n";

        first = true;
        out << indentStr << "  \"subDir\": [";
        for(auto [a, b]: addr->subDir)
        {
            if(first) { first = false; out << "\n"; }
            else out << ",\n";
            writeDir(b, out, indent + 4);
        }
        if(first) out << "]\n";
        else out << "\n" << indentStr << "  ]\n";

        out << indentStr << "}";
    }

    bool load(const std::string &filename)
    {
        delete root;
        current = nullptr;
        std::ifstream file(filename + ".json", std::ios::in | std::ios::binary);
        if(!file)
        {
            std::cerr << "无法打开文件！" << std::endl;
            return false;
        }

        std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        int pos = 0;
        auto tmp = loadDir(json, pos, json.size());
        root = tmp.second;
        if(current == nullptr) current = root;
        path = current->getAbsPath();
        file.close();
        return true;
    }

    bool save(const std::string &filename)
    {
        std::ofstream file(filename + ".json", std::ios::out | std::ios::binary | std::ios::trunc);
        if(!file)
        {
            std::cerr << "无法打开文件！" << std::endl;
            return false;
        }

        writeDir(root, file);
        file.close();
        return true;
    }

    /**
     * 可能的路径输入形式
     * /
     * /asjd/sadh/dds
     * ..
     * ../../sadh
     * ./asdsa
     * asdsa
     */
    Directory* parsePath(const std::string &s)
    {
        if(s.empty()) return nullptr;
        int beg, i;
        std::vector<std::string> v;
        for(beg = i = 0; i <= s.size(); ++i)
        {
            if(i == s.size() || s[i] == '/')
            {
                v.emplace_back(s.substr(beg, i - beg));
                beg = i + 1;
            }
        }

        Directory* addr = current;
        for(auto &a: v)
        {
            if(a == ".") continue;
            else if(a == "") addr = root;
            else if(a == "..")
            {
                if(addr->father != nullptr) addr = addr->father;
                // else return nullptr;
                else continue;
            }
            else
            {
                auto it = addr->subDir.find(a);
                if(it == addr->subDir.end()) return nullptr;
                addr = it->second;
            }
        }

        return addr;
    }

    //不保证addr绝对有效
    void jump(Directory* addr)
    {
        current = addr;
        path = addr->getAbsPath();
    }

    bool forward(std::string s)
    {
        auto it = current->subDir.find(s);
        if(it == current->subDir.end()) return false;
        path = path + "/" + s;
        current = it->second;
        return true;
    }

    bool back()
    {
        if(current->father == nullptr) return false;
        int i = path.size() - 1;
        for(; i >= 0 && path[i] != '/'; --i)
        path = path.substr(0, i);
        current = current->father;
        if(current->father == nullptr) path = "/";
        return false;
    }

    bool jumpWithPath(const std::string &s)
    {
        Directory* addr = parsePath(s);
        if(addr == nullptr) return false;
        jump(addr);
        return true;
    }

    void bfs(const std::string &s) const
    {
        std::queue<Directory*> q;
        q.push(current);

        while(!q.empty())
        {
            Directory* dir = q.front();
            std::vector<std::string> matches;
            q.pop();
    
            auto it = dir->files.lower_bound(s);
            while(it != dir->files.end() && it->find(s) == 0)
            {
                matches.push_back(*it + '*');
                ++it;
            }
    
            for (const auto& [a, b] : dir->subDir) {
                if (a.find(s) == 0) matches.push_back(a);
                q.push(b);
            }

            if(!matches.empty())
            {
                std::string relPath = dir->getAbsPath();
                relPath = relPath.substr(path.size(), relPath.size() - path.size());
                relPath = "/" + relPath;
                echo("--- " + relPath + " ---");
                for(const auto& a: matches)
                    echo(a, " ");
                echo();
            }
        }
    }

    void list() const
    {
        for(auto& it: current->files) echo(it + "*");
        for(auto& [a, b]: current->subDir) echo(a);
    }

    void echo(const std::string &s = "", const std::string &end = "\n") const { std::cout << s << end; }

    void getCommand()
    {
#ifdef DIRMANAGER
        echo("PS " + path + ">", " ");
#endif

        std::string op, target, source;
        std::cin >> op;
        switch (op[0])
        {
        case 'c':
            if(std::cin.peek() == '\n') echo(path);
            else if(op[1] == 'd')
            {
                std::cin >> target;
                jumpWithPath(target);
            }
            else
            {
                std::cin >> source >> target;
                Directory *td = parsePath(target);
                auto tp1 = current->copyFile(source);
                auto tp2 = current->copyDir(source);
                if(tp1.first) td->createFile(*(tp1.second));
                else if(tp2.first != nullptr)
                    td->pasteDir(tp2.first);
            }
            break;

        case 'd':
            if(op[1] == 'i') list();
            else if(op[1] == 'e')
            {
                std::cin >> target;
                current->removeFile(target);
                current->removeDir(target);
            }
            break;

        case 'l':
            std::cin >> target;
            load(target);
            break;

        case 'm':
            std::cin >> target;
            if(op[1] == 'o')
            {
                std::cin >> source >> target;
                Directory *td = parsePath(target);
                auto tp1 = current->copyFile(source);
                auto tp2 = current->copyDir(source);
                if(tp1.first && td->createFile(*(tp1.second)))
                    current->files.erase(tp1.second);
                else if(tp2.first != nullptr && td->pasteDir(tp2.first))
                    current->subDir.erase(tp2.second);
            }
            else if(op[2] == 'f') current->createFile(target);
            else if(op[2] == 'd') current->createDir(target);
            break;

        case 'q':
#ifdef DIRMANAGER
            save("data");
#endif
            delete root;
            exit(0);
            break;

        case 's':
            if(op[1] == 'a')
            {
                std::cin >> target;
                save(target);
            }
            else if(op[1] == 'e')
            {
                std::cin >> target;
                bfs(target);
            }
            break;

        default:
            echo("unknown command!");
            break;
        }
    }
};

int main()
{
    CatalogManager cm;
#ifdef DIRMANAGER
    cm.load("data");
#endif
    while (true)
        cm.getCommand();
    return 0;
}