#include "iostream"
#include "vector"
#include "queue"
#include "unordered_map"
#include "algorithm"

using namespace std;

class heap
{
public:
    heap();
    // ~heap();

    void push(int treeNode);
    void pop();

    int top() { return data[1]; }
    int size() { return data.size(); }

protected:
    vector<int> data;
};

heap::heap()
{
    data.push_back(INT32_MIN);
}

void heap::push(int treeNode)
{
    data.push_back(treeNode);
    int index = data.size() - 1;
    while (index > 1)
    {
        if (data[index] < data[index / 2])
        {
            swap(data[index], data[index / 2]);
            index /= 2;
        }
        else
        {
            break;
        }
    }
}

void heap::pop()
{
    if (data.size() == 1)
    {
        return;
    }
    int result = data[1];
    data[1] = data[data.size() - 1];
    data.pop_back();
    int index = 1;
    while (index * 2 < data.size())
    {
        int minIndex = index;
        if (data[index] > data[index * 2])
        {
            minIndex = index * 2;
        }
        if (index * 2 + 1 < data.size() && data[minIndex] > data[index * 2 + 1])
        {
            minIndex = index * 2 + 1;
        }
        if (minIndex == index)
        {
            break;
        }
        swap(data[index], data[minIndex]);
        index = minIndex;
    }
}

struct node
{
    node(int element_) : element(element_), next(nullptr) {}

    int   element;
    node *next;
};

struct headNode
{
    headNode(node* theNode) : last(theNode), next(theNode) {}
    void resort();

    node *last;
    node *next;
};

// 函数：拆分链表，返回中间节点
node* splitList(node* head) {
    if (!head || !head->next) return head;

    node* slow = head;
    node* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    node* secondHalf = slow->next;
    slow->next = nullptr;
    return secondHalf;
}

// 函数：合并两个有序链表
node* mergeLists(node* l1, node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    node* mergedHead = nullptr;

    if (l1->element < l2->element) {
        mergedHead = l1;
        mergedHead->next = mergeLists(l1->next, l2);
    } else {
        mergedHead = l2;
        mergedHead->next = mergeLists(l1, l2->next);
    }

    return mergedHead;
}

// 函数：归并排序
node* mergeSort(node* head) {
    if (!head || !head->next) return head;

    node* secondHalf = splitList(head);

    head = mergeSort(head);
    secondHalf = mergeSort(secondHalf);

    return mergeLists(head, secondHalf);
}

// resort 函数
void headNode::resort() {
    if (!next) return;

    // 进行归并排序
    next = mergeSort(next);

    last = nullptr;

    // // 更新 last 指针
    // node* current = next;
    // last = current;
    // while (current && current->next) {
    //     current = current->next;
    //     last = current;
    // }
}

class graph
{
public:
    graph(int size, int ns_, int nt_);

    void insert(int r, int t);
    void erase(int r, int t);
    void initSearch();
    void minDFS(int n, int depth);
    void minBFS(int n);

    int get_s_length() { return length[0]; }
    int get_t_length() { return length[1]; }
    int get_min_depth() { return minDepth; }

protected:
    vector<headNode*> nodes;
    heap              minIndex;
    vector<int>       reach;
    int               volume;
    int               ns, nt;
    int               minDepth;
    int               length[2];
    bool              isPathExist;
};

graph::graph(int size, int ns_, int nt_)
{
    nodes  = vector<headNode*>(size + 1, nullptr);
    reach  = vector<int>(size + 1, 0);
    volume = size;
    ns = ns_;
    nt = nt_;
    minDepth = -1;
    isPathExist = false;
}

void graph::insert(int r, int t)
{
    node *rNode = new node(r), *tNode = new node(t);
    if (nodes[r] == nullptr) nodes[r] = new headNode(tNode);
    else {
        nodes[r]->last->next = tNode;
        nodes[r]->last       = tNode;
    }
    if (nodes[t] == nullptr) nodes[t] = new headNode(rNode);
    else {
        nodes[t]->last->next = rNode;
        nodes[t]->last       = rNode;
    }
}

void graph::erase(int r, int t)
{
    if (nodes[r] == nullptr || nodes[t] == nullptr) return;

    node* start = nodes[r]->next;
    if (start->element == t) {
        if (start == nodes[r]->last) {
            delete start;
            delete nodes[r];
            nodes[r] = nullptr;
        }
        else {
            nodes[r]->next = start->next;
            delete start;
        }
    }
    else {
        while (start->next != nullptr && start->next->element != t) {
            start = start->next;
        }
        if (start->next != nullptr) {
            node* temp = start->next;
            if (nodes[r]->last == temp) nodes[r]->last = start;
            start->next = temp->next;
            delete temp;
        }
    }

    start = nodes[t]->next;
    if (start->element == r) {
        if (start == nodes[t]->last) {
            delete start;
            delete nodes[t];
            nodes[t] = nullptr;
        }
        else {
            nodes[t]->next = start->next;
            delete start;
        }
    }
    else {
        while (start->next != nullptr && start->next->element != r) {
            start = start->next;
        }
        if (start->next != nullptr) {
            node* temp = start->next;
            if (nodes[t]->last == temp) nodes[t]->last = start;
            start->next = temp->next;
            delete temp;
        }
    }
}

void graph::initSearch()
{
    vector<int> Path;
    queue<int>  toReach;
    int label = 0;
    node *start = nodes[nt]->next;
    int   min   = nt;
    int   len   = 1;


    /* bfs */
    reach[nt] = ++label;
    Path.push_back(nt);
    while (start != nullptr || !toReach.empty()) {
        if (start != nullptr && reach[start->element] == 0) {
            if (start->element < min) min = start->element;

            if (!isPathExist && start->element == ns) isPathExist = true;
            Path.push_back(start->element);

            reach[start->element] = label;
            toReach.push(start->element);
            start = start->next;
            ++len;
        }
        else if (start == nullptr) {
            start = nodes[toReach.front()]->next;
            toReach.pop();
        }
        else {
            start = start->next;
        }
    }
    minIndex.push(min);
    length[0] = length[1] = len;

    /* 遍历Path，重排nodes[i] */
    for (int i = 0; i < Path.size(); i++) {
        nodes[Path[i]]->resort();
    }
    Path.clear();

    if (!isPathExist) {
        start = nodes[ns]->next;
        min   = ns;
        len   = 1;

        /* bfs */
        reach[ns] = ++label;
        while (start != nullptr || !toReach.empty()) {
            if (start != nullptr && reach[start->element] == 0) {
                if (start->element < min) min = start->element;

                Path.push_back(start->element);

                reach[start->element] = label;
                toReach.push(start->element);
                start = start->next;
                ++len;
            }
            else if (start == nullptr) {
                start = nodes[toReach.front()]->next;
                toReach.pop();
            }
            else {
                start = start->next;
            }
        }
        minIndex.push(min);
        length[1] = len;

        /* 遍历Path，重排nodes[i] */
        for (int i = 0; i < Path.size(); i++) {
            nodes[Path[i]]->resort();
        }
        Path.clear();
    }

    /* 遍历剩余连通分量 */
    for (int i = 1; i <= volume; i++) {
        if (reach[i] == 0) {
            start = nodes[i]->next;
            min   = i;
            reach[i] = ++label;

            /* bfs */
            while (start != nullptr || !toReach.empty()) {
                if (start != nullptr && reach[start->element] == 0) {
                    if (start->element < min) min = start->element;

                    reach[start->element] = label;
                    toReach.push(start->element);
                    start = start->next;
                }
                else if (start == nullptr) {
                    start = nodes[toReach.front()]->next;
                    toReach.pop();
                }
                else {
                    start = start->next;
                }
            }

            minIndex.push(min);
        }
    }

    cout << label << endl;
    while (minIndex.size() > 1) {
        cout << minIndex.top() << " ";
        minIndex.pop();
    }
    cout << endl;
}

void graph::minDFS(int n, int depth)
{
    node *start = nodes[n]->next;
    int   dp    = depth + 1;
    reach[n] = -1;

    cout << n << " ";

    while (start != nullptr) {
        if (reach[start->element] != -1) {
            minDFS(start->element, dp);
        }
        if (isPathExist && start->element == nt) {
            if (minDepth = -1) minDepth = dp;
            else if (dp < minDepth) minDepth = dp;
        } 
        start = start->next;
    }

    if (n == ns) cout << endl;
}

void graph::minBFS(int n)
{
    queue<int> toReach;
    node *start = nodes[n]->next;
    reach[n] = -2;
    cout << n << " ";

    /* bfs */
    while (start != nullptr || !toReach.empty()) {
        if (start != nullptr && reach[start->element] != -2) {
            cout << start->element << " ";
            reach[start->element] = -2;
            toReach.push(start->element);
            start = start->next;
        }
        else if (start == nullptr) {
            start = nodes[toReach.front()]->next;
            toReach.pop();
        }
        else {
            start = start->next;
        }
    }

    if (n == nt) cout << endl;
}

int main()
{
    int n, m, s, t;
    int op, u, v;
    cin >> n >> m >> s >> t;
    graph gp(n, s, t);

    for (int i = 0; i < m; i++) {
        cin >> op >> u >> v;
        switch (op)
        {
        case 0:
            gp.insert(u, v);
            break;

        case 1:
            gp.erase(u, v);
            break;
        
        default:
            break;
        }
    }

    gp.initSearch();
    cout << gp.get_s_length() << endl;
    gp.minDFS(s, 0);
    cout << gp.get_t_length() << endl;
    gp.minBFS(t);
    cout << gp.get_min_depth() << endl;

    return 0;
}