#include "iostream"
#include "vector"

using namespace std;

class UnionFind
{
public:
    UnionFind(int size);

    int findSet(int x);
    void unionSet(int x, int y);

private:
    vector<int> parent;
    vector<int> rank;
};

UnionFind::UnionFind(int size)
{
    ++size;
    parent.resize(size);
    rank.resize(size, 1);
    for (int i = 0; i < size; i++)
    {
        parent[i] = i;
    }
}

int UnionFind::findSet(int x)
{
    if (parent[x] != x)
    {
        parent[x] = findSet(parent[x]);
    }
    return parent[x];
}

void UnionFind::unionSet(int x, int y)
{
    int rootX = findSet(x);
    int rootY = findSet(y);
    if (rootX == rootY)
    {
        return;
    }
    if (rank[rootX] < rank[rootY])
    {
        swap(rootX, rootY);
    }
    parent[rootY] = rootX;
    if (rank[rootX] == rank[rootY])
    {
        rank[rootX]++;
    }
}

struct treeNode
{
    treeNode(int data_ = 0, int left_ = 0, int right_ = 0) : data(data_), left(left_), right(right_) {}

    int data;
    int left, right;
};

template <typename T>
class Heap
{
public:
    Heap();
    // ~heap();

    void heapify();
    void push(T treeNode);
    void push_back(T treeNode);
    void pop();
    bool empty() { return container.size() == 1; }

    T top() { return container[1]; }

protected:
    vector<T> container;
};

template <typename T>
Heap<T>::Heap()
{
    container.push_back(T());
}

template <typename T>
void Heap<T>::heapify()
{
    for (int i = container.size() / 2; i > 0; i--)
    {
        int index = i;
        while (index * 2 < container.size())
        {
            int minIndex = index;
            if (container[index].data > container[index * 2].data)
            {
                minIndex = index * 2;
            }
            if (index * 2 + 1 < container.size() && container[minIndex].data > container[index * 2 + 1].data)
            {
                minIndex = index * 2 + 1;
            }
            if (minIndex == index)
            {
                break;
            }
            swap(container[index], container[minIndex]);
            index = minIndex;
        }
    }
}

template <typename T>
void Heap<T>::push(T node)
{
    container.push_back(node);
    int index = container.size() - 1;
    while (index > 1)
    {
        if (container[index].data < container[index / 2].data)
        {
            swap(container[index], container[index / 2]);
            index /= 2;
        }
        else
        {
            break;
        }
    }
}

template <typename T>
void Heap<T>::push_back(T node)
{
    container.push_back(node);
}

template <typename T>
void Heap<T>::pop()
{
    if (container.size() == 1)
    {
        return;
    }
    T result = container[1];
    container[1] = container[container.size() - 1];
    container.pop_back();
    int index = 1;
    while (index * 2 < container.size())
    {
        int minIndex = index;
        if (container[index].data > container[index * 2].data)
        {
            minIndex = index * 2;
        }
        if (index * 2 + 1 < container.size() && container[minIndex].data > container[index * 2 + 1].data)
        {
            minIndex = index * 2 + 1;
        }
        if (minIndex == index)
        {
            break;
        }
        swap(container[index], container[minIndex]);
        index = minIndex;
    }
}

int main()
{
    int n, e;
    long long res = 0;
    cin >> n >> e;
    UnionFind uf(n);
    Heap<treeNode> heap;
    for (int i = 0; i < e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        heap.push_back(treeNode(w, u, v));
    }
    heap.heapify();
    while (!heap.empty() && n > 1) {
        treeNode node = heap.top();
        heap.pop();
        if (uf.findSet(node.left) != uf.findSet(node.right)) {
            uf.unionSet(node.left, node.right);
            res += node.data;
            n--;
        }
    }
    cout << res << endl;
    return 0;
}