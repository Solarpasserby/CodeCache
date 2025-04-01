#include<iostream>
#include<vector>
#include<cassert>
#include<map>

using namespace std;

// #define SAMPLECHECK
// #define CNTCHECK
// #define MAPCHECK

/**
 * | 数量级 | 访问次数  | $2n\log n$ |
 * |  1e3  | 21520     | 19932      |
 * |  1e4  | 324040    | 265754     |
 * |  1e5  | 3763592   | 3321928    |
 * |  1e6  | 39172477  | 39863137   |
 * |  1e7  | 393198658 | 465069933  |
 */

long long cnt = 0;

template<typename K, typename V>
struct SkiplistNode
{
    K key;
    V value;
    int level;
    SkiplistNode** forward;

    SkiplistNode(K _key, V _value, int _level, SkiplistNode<K, V>* nxt = nullptr)
    {
        key = _key;
        value = _value;
        level = _level;
        forward = new SkiplistNode* [_level];
        for(int i = 0; i < _level; i++) forward[i] = nxt;
    }

    ~SkiplistNode()
    {
        if (forward != nullptr) delete[] forward;
    }
};

template<typename K, typename V>
struct Skiplist
{
    static const int MAXL;
    static const int P;
    static const int S;

    int level;
    int length;
    V invalid;
    SkiplistNode<K, V>* head;
    SkiplistNode<K, V>* tail;

    SkiplistNode<K, V>* rb[MAXL];

    Skiplist(V _invalid = INT_MAX)
    {
        tail = new SkiplistNode<K, V>(_invalid, V(), 1);
        head = new SkiplistNode<K, V>(K(), V(), MAXL, tail);
        level = length = 0;
        invalid = _invalid;
    }

    ~Skiplist()
    {
        SkiplistNode<K, V>* p;
        SkiplistNode<K, V>* q = head;
        while(q)
        {
            p = q;
            q = q->forward[0];
            delete p;
        }
    }

    int randomLevel() {
        int lv = 1;
        while (rand() < S) ++lv;
        return min(MAXL, lv);
    }

    void rebuild()
    {
        vector<pair<K, V>> tmp;
        SkiplistNode<K, V>* p = head->forward[0];
        while(p->key != invalid)
        {
            tmp.push_back(pair<K, V>(p->key, p->value));
            p = p->forward[0];
        }
        for(const auto &it: tmp)
        {
            clear();
            push(it.first, it.second);
        }
    }

    V& find(const K &_key)
    {
        SkiplistNode<K, V>* p = head;
        for(int i = level; i >= 0; --i)
            while(p->forward[i]->key < _key)
            {
                p = p->forward[i];
                ++cnt;
            }

        p = p->forward[0];
        if(p->key == _key) return p->value;
        else return invalid;
    }

    bool count(const K &_key) { return find(_key) != invalid; }

    bool insert(const K &_key, const V &_value)
    {
        SkiplistNode<K, V>* p = head;
        SkiplistNode<K, V>* update[MAXL];

        for(int i = level; i >= 0; --i)
        {
            while(p->forward[i]->key < _key)
            {
                p = p->forward[i];
                ++cnt;
            }
            update[i] = p;
        }

        if (p->forward[0]->key == _key)
        {
            p->forward[0]->value = _value;
            return true;
        }

        int l = randomLevel();
        if (l-1 > level)
        {
            l = ++level;
            update[l] = head;
            l += 1;
        }
        SkiplistNode<K, V>* newNode = new SkiplistNode<K, V>(_key, _value, l);

        for(int i = l-1; i >= 0; --i)
        {
            p = update[i];
            newNode->forward[i] = p->forward[i];
            p->forward[i] = newNode;
        }

        ++length;
        return true;
    }

    void push(const K &_key, const V &_value)
    {
        int l = randomLevel();
        if (l-1 > level)
        {
            l = ++level;
            update[l] = head;
            l += 1;
        }
        SkiplistNode<K, V>* newNode = new SkiplistNode<K, V>(_key, _value, l);

        for(int i = l-1; i >= 0; --i)
        {
            p = update[i];
            newNode->forward[i] = p->forward[i];
            p->forward[i] = newNode;
        }

        ++length;
    }

    bool erase(const K &_key)
    {
        SkiplistNode<K, V>* p = head;
        SkiplistNode<K, V>* update[MAXL];

        for(int i = level; i >= 0; --i)
        {
            while(p->forward[i]->key < _key)
            {
                p = p->forward[i];
                ++cnt;
            }
            update[i] = p;
        }

        p = p->forward[0];
        if (p->key != _key)
            return false;

        for(int i = 0; i < p->level; ++i)
        {
            if (update[i]->forward[i] != p) break;
            update[i]->forward[i] = p->forward[i];
        }

        delete p;
        while(level > 0 && head->forward[level] == nullptr) --level;

        --length;
        return true;
    }

    K eraseFirst()
    {
        K res = head->forward[0]->key;
        if (length < 1) return invalid;
        erase(head->forward[0]->key);
        return res;
    }

    K eraseLast()
    {
        if (length < 1) return false;

        K res;
        SkiplistNode<K, V>* p = head;
        for(int i = level; i >= 0; --i)
            while(p->forward[i]->key < invalid)
                p = p->forward[i];
        res = p->key;
        erase(p->key);
        return res;
    }

    K xorSum()
    {
        SkiplistNode<K, V>* p = head->forward[0];
        K res = K();
        while(p->key != invalid)
        {
            res ^= p->key;
            p = p->forward[0];
        }
        return res;
    }

    void clear()
    {
        SkiplistNode<K, V>* p;
        SkiplistNode<K, V>* q = head->forward[0];
        while(q->key < invalid)
        {
            p = q;
            q = q->forward[0];
            delete p;
        }
    }
};

template<typename K, typename V>
const int Skiplist<K, V>::MAXL = 32;

template<typename K, typename V>
const int Skiplist<K, V>::P = 4;

template<typename K, typename V>
const int Skiplist<K, V>::S = RAND_MAX / Skiplist<K, V>::P;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    Skiplist<int, int> test;

#ifdef SAMPLECHECK
    int n, m;
    cin >> n >> m;
    while(m--)
    {
        int t;
        cin >> t;
        test.insert(t, t);
    }
    while(n--)
    {
        int op, t;
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> t;
            if (test.count(t)) cout << "YES\n";
            else cout << "NO\n";
            break;

        case 2:
            cin >> t;
            test.insert(t, t);
            cout << test.xorSum() << '\n';
            break;

        case 3:
            cin >> t;
            test.erase(t);
            cout << test.xorSum() << '\n';
            break;

        case 4:
            cout << test.eraseFirst() << '\n';
            break;

        case 5:
            cout << test.eraseLast() << '\n';
            break;
        
        default:
            break;
        }
    }
#endif

#ifdef CNTCHECK
    int n, m;
    cin >> n >> m;
    while(m--)
    {
        int t;
        cin >> t;
        test.insert(t, t);
    }
    while(n--)
    {
        int op, t;
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> t;
            test.count(t);
            break;

        case 2:
            cin >> t;
            test.insert(t, t);
            break;

        case 3:
            cin >> t;
            test.erase(t);
            break;

        case 4:
            test.eraseFirst();
            break;

        case 5:
            test.eraseLast();
            break;
        
        default:
            break;
        }
    }

    cout << cnt << '\n';
#endif

#ifdef MAPCHECK
    map<int, int> mp;
    for (int i = 0; i < 1e5; ++i)
    {
        int a = rand();
        int b = rand();
        mp.insert(pair<int, int>(a, b));
        test.insert(a, b);
    }

    for (int i = 0; i < 1e5; ++i)
    {
        int a = rand();
        if (a & 1)
        {
            mp.erase(a);
            test.erase(a);
        }
        else
        {
            assert(mp.count(a) == test.count(a));
        }
    }

    cout << cnt << '\n';
#endif

    return 0;
}