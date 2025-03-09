/**
 * 尝试写一个简单的跳表
 */

#include<iostream>

using namespace std;

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
    static const int MAXL = 32;
    static const int P = 4;
    static const int S = RAND_MAX / P;

    int level;
    int length;
    V invalid;
    SkiplistNode<K, V>* head;

    Skiplist(V _invalid = INT_MAX)
    {
        head = new SkiplistNode<K, V>(K(), V(), MAXL);
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

    V& find(const K &_key)
    {
        SkiplistNode<K, V>* p = head;
        for(int i = level; i >= 0; --i)
            while(p->forward[i]->key < _key)
                p = p->forward[i];

        p = p->forward[0];
        if(p->key == _key) return p->value;
        else return invalid;
    }

    bool insert(const K &_key, const V &_value)
    {
        SkiplistNode<K, V>* p = head;
        SkiplistNode<K, V>* update[MAXL];

        for(int i = level; i >= 0; --i)
        {
            while(p->forward[i]->key < _key)
                p = p->forward[i];
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

    bool erase(const K &_key)
    {
        SkiplistNode<K, V>* p = head;
        SkiplistNode<K, V>* update[MAXL];

        for(int i = level; i >= 0; --i)
        {
            while(p->forward[i]->key < _key)
                p = p->forward[i];
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

    void display()
    {
        SkiplistNode<K, V>* p = head->forward[0];
        while(p != nullptr)
        {
            cout << p->key << ' ' << p->value << ' ' << p->level << '\n';
            p = p->forward[0];
        }
    }
};

int main()
{
    Skiplist<int, int> test;
    test.insert(1, 1);
    test.insert(2, 2);
    test.insert(3, 3);
    test.display();
    test.erase(1);
    test.display();

    return 0;
}