#include <iostream>

using namespace std;

long long cnt = 0;

struct Node
{
    int val;
    Node *nxt;

    Node(int v = 0, Node* p = nullptr) { val = v, nxt = p; }
};

struct Chain
{
    Node *head, *tail;

    Chain()
    {
        tail = new Node(INT32_MAX, nullptr);
        head = new Node(0, tail);
    }

    ~Chain()
    {
        Node* p = head, *q;
        while(p)
        {
            q = p->nxt;
            delete p;
            p = q;
        }
    }

    bool count(int v)
    {
        Node* p = head->nxt;
        while(p->val != INT32_MAX)
        {
            if (p->val == v) return true;
            p = p->nxt;
            ++cnt;
        }
        return false;
    }

    void insert(int v)
    {
        Node* p = head;
        while(p->nxt->val < v)
        {
            p = p->nxt;
            ++cnt;
        }
        if (p->nxt->val == v) return;
        else
        {
            Node *newNode = new Node(v, p->nxt);
            p->nxt = newNode;
        }
    }

    void erase(int v)
    {
        Node* p = head;
        while(p->nxt->val < v)
        {
            p = p->nxt;
            ++cnt;
        }
        if (p->nxt->val != v) return;
        else
        {
            Node *q = p->nxt;
            p->nxt = q->nxt;
            delete q;
        }
    }

    void eraseFirst()
    {
        if (head->nxt->val == INT32_MAX) return;
        else
        {
            Node *q = head->nxt;
            head->nxt = q->nxt;
            delete q;
        }
    }

    void eraseLast()
    {
        if (head->nxt->val == INT32_MAX) return;

        Node* p = head, *q;
        while(p->nxt->val < INT32_MAX)
        {
            q = p;
            p = p->nxt;
            ++cnt;
        }
        q->nxt = p->nxt;
        delete p;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    Chain test;

    int n, m;
    cin >> n >> m;
    while(m--)
    {
        int t;
        cin >> t;
        test.insert(t);
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
            test.insert(t);
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

    return 0;
}