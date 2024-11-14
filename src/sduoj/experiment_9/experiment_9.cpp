#include "iostream"
#include "vector"

using namespace std;

struct treeNode
{
    int data;
    treeNode *left;
    treeNode *right;

    treeNode(int d)
    {
        this->data  = d;
        this->left  = nullptr;
        this->right = nullptr;
    }
};

template <typename T>
class heap
{
public:
    heap();
    ~heap();

    void push(T *treeNode);
    T pop();

    T* get(int i) { return data[i]; }

protected:
    vector<T*> data;
};

template <typename T>
heap<T>::heap()
{
    data.push_back(nullptr);
}

template <typename T>
void heap<T>::push(T *treeNode)
{
    data.push_back(treeNode);
    int index = data.size() - 1;
    while (index > 1)
    {
        if (data[index]->data < data[index / 2]->data)
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
T heap<T>::pop()
{
    if (data.size() == 1)
    {
        return nullptr;
    }
    T *result = data[1];
    data[1] = data[data.size() - 1];
    data.pop_back();
    int index = 1;
    while (index * 2 < data.size())
    {
        int minIndex = index;
        if (data[index]->data > data[index * 2]->data)
        {
            minIndex = index * 2;
        }
        if (index * 2 + 1 < data.size() && data[minIndex]->data > data[index * 2 + 1]->data)
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
    return result;
}

template <typename T>
class binaryTree
{
public:
    binaryTree();
    ~binaryTree();

    void lineInsert(T l, T r);
    void remove(T data);

    void preOrder();
    void inOrder();
    void postOrder();
    void levelOrder();

protected:
    treeNode *root;
    typename heap<treeNode> treeHeap();
};

template <typename T>
binaryTree<T>::binaryTree()
{
    root = new treeNode(1);
    treeHeap.push(root);
}

template <typename T>
binaryTree<T>::lineInsert(T l, T r)
{
    treeNode* target = treeHeap.pop();

    if (l != -1)
    {
        treeNode *left_ = new treeNode(l);
        treeHeap.push(left_);
    }
    else
        treeNode *left_ = nullptr;
    if (r != -1)
    {
        treeNode *right_ = new treeNode(r);
        treeHeap.push(right_);
    }
    else
        treeNode *right_ = nullptr;

    target->left  = left_;
    target->right = right_;
}

int main()
{
    return 0;
}