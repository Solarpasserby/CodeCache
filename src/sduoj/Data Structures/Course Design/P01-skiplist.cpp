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

    SkiplistNode(K _key, V _value, int _level, const SkiplistNode* &nxt = nullptr)
    {
        key = _key;
        value = _value;
        level = _level;
        forward = new SkiplistNode* [_level + 1];
        for(SkiplistNode* f: forward) f = nxt;
    }

    ~SkiplistNode()
    {
        if (forward != nullptr) delete[] forward;
    }
};

template<typename K, typename V>
struct Skiplist
{
    int level;
    SkiplistNode* head;

    Skiplist(SkiplistNode* p = nullptr)
    {
        level = p.level;
    }

    V& find(const K &_key)
    {
        SkiplistNode* p;
        for()
    }
};

int main()
{
    return 0;
}