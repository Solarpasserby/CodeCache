#include "iostream"
#include "vector"

using namespace std;

template <typename T>
class heap
{
public:
    heap();
    // ~heap();

    void push(T treeNode);
    void pop();

    T top() { return data[1]; }

protected:
    vector<T> data;
};

template <typename T>
heap<T>::heap()
{
    data.push_back(INT32_MIN);
}

template <typename T>
void heap<T>::push(T treeNode)
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

template <typename T>
void heap<T>::pop()
{
    if (data.size() == 1)
    {
        return;
    }
    T result = data[1];
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

void heapSort()
{
    int n, data;
    cin >> n;
    heap<int> sortHeap;
    for (int i = 0; i < n; i++)
    {
        cin >> data;
        sortHeap.push(data);
    }
    for (int i = 0; i < n; i++)
    {
        cout << sortHeap.top() << " ";
        sortHeap.pop();
    }

    return;
}

int main()
{
    int n, m, data;
    cin >> n;
    heap<int> opHeap;
    for (int i = 0; i < n; i++)
    {
        cin >> data;
        opHeap.push(data);
    }
    cout << opHeap.top() << endl;

    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int op;
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> data;
            opHeap.push(data);
            cout << opHeap.top() << endl;
            break;
        case 2:
            opHeap.pop();
            cout << opHeap.top() << endl;
            break;
        case 3:
            heapSort();
            break;
        }
    }

    return 0;
}