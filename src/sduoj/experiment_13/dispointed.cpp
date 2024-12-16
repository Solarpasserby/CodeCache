#include "iostream"
#include "vector"

using namespace std;

struct Edge
{
    int to, weight;
    Edge(int to_ = 0, int weight_ = 0) : to(to_), weight(weight_) {}
};

struct Node
{
    int data;
    int weight;
    Node* next;
    Node(int data_, int weight_) : data(data_), weight(weight_), next(nullptr) {}
};

struct Chain
{
    Node* head;
    Node* last;
    Chain() : head(nullptr), last(nullptr) {}
};

template <typename T>
class Heap
{
public:
    Heap();
    // ~heap();

    void heapify();
    void push(T node);
    void push_back(T node);
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
        if (container[index].weight < container[index / 2].weight)
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
        if (container[index].weight > container[index * 2].weight)
        {
            minIndex = index * 2;
        }
        if (index * 2 + 1 < container.size() && container[minIndex].weight > container[index * 2 + 1].weight)
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

class Graph
{
public:
    Graph(int size);

    void addEdge(int from, int to, int weight);
    long long prim();

private:
    vector<Chain> chains;
};

Graph::Graph(int size)
{
    chains.resize(size + 1);
}

void Graph::addEdge(int from, int to, int weight)
{
    Node* node = new Node(to, weight);
    if (chains[from].head == nullptr)
    {
        chains[from].head = node;
        chains[from].last = node;
    }
    else
    {
        chains[from].last->next = node;
        chains[from].last = node;
    }
    node = new Node(from, weight);
    if (chains[to].head == nullptr)
    {
        chains[to].head = node;
        chains[to].last = node;
    }
    else
    {
        chains[to].last->next = node;
        chains[to].last = node;
    }
}

long long Graph::prim()
{
    Heap<Edge> heap;
    vector<bool> visited(chains.size(), false);
    int n = chains.size() - 1;
    long long result = 0;
    Chain chain = chains[1];
    visited[1] = true;

    while (n > 1) {
        Node* node = chain.head;
        while (node != nullptr) {
            heap.push(Edge(node->data, node->weight));
            node = node->next;
        }
        while (!heap.empty()) {
            Edge edge = heap.top();
            heap.pop();
            
            if (!visited[edge.to]) {
                visited[edge.to] = true;
                chain = chains[edge.to];
                result += edge.weight;
                n--;
                break;
            }
        }
    }

    return result;
}

int main()
{
    int n, e;
    cin >> n >> e;
    Graph graph(n);
    for (int i = 0; i < e; i++)
    {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph.addEdge(from, to, weight);
    }
    cout << graph.prim() << endl;
    return 0;
}