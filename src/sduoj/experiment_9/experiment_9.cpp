#include "iostream"
#include "vector"

using namespace std;

struct treeNode
{
    int data;
    treeNode *parent;
    treeNode *left;
    treeNode *right;

    treeNode(int d)
    {
        this->data  = d;
        this->parent = nullptr;
        this->left   = nullptr;
        this->right  = nullptr;
    }
};

struct chainNode
{
    treeNode *element;
    chainNode *next;

    chainNode()
    {
        this->element = nullptr;
        this->next    = nullptr;
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

class queue
{
public:
    queue();
    ~queue();

    void push(treeNode *treeNode);
    treeNode* pop();

    int len() { return this->length; }

protected:
    chainNode *front;
    chainNode *rear;
    int length;
};

queue::queue()
{
    front = new chainNode();
    rear  = front;
    length = 0;
}

queue::~queue()
{
    chainNode *nextNode;
    while (front != nullptr)
    {
        nextNode = front->next;
        delete front;
        front = nextNode;
    }
}

void queue::push(treeNode *treeNode)
{
    rear->next = new chainNode();
    rear->next->element = treeNode;
    rear = rear->next;
    length++;
}

treeNode* queue::pop()
{
    if (length == 0)
    {
        return nullptr;
    }
    chainNode *firstNode = front->next;
    treeNode *result = firstNode->element;
    front->next = firstNode->next;
    if (rear == firstNode)
    {
        rear = front;
    }
    delete firstNode;
    length--;
    return result;
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

    void preOrder(treeNode *r);
    void inOrder(treeNode *r = nullptr);
    void postOrder(treeNode *r = nullptr);
    void levelOrder(treeNode *r = nullptr);

protected:
    static treeNode *root;
    heap<treeNode> treeHeap;
};

template <typename T>
binaryTree<T>::binaryTree()
{
    root = new treeNode(1);
    treeHeap.push(root);
}

template <typename T>
void binaryTree<T>::lineInsert(T l, T r)
{
    treeNode* target = treeHeap.pop();
    treeNode *left_ = nullptr;
    treeNode *right_ = nullptr;

    if (l != -1)
    {
        left_ = new treeNode(l);
        treeHeap.push(left_);
    }
    if (r != -1)
    {
        right_ = new treeNode(r);
        treeHeap.push(right_);
    }

    target->left  = left_;
    target->right = right_;
}

template <typename T>
void binaryTree<T>::preOrder(treeNode* r)
{
    cout << r->data << ' ';
    if (r->left != nullptr)
        preOrder(r->left);
    if (r->right != nullptr)
        preOrder(r->right);
}

template <typename T>
void binaryTree<T>::inOrder(treeNode *r)
{
    if (r == nullptr)
        r = root;

    int i = 0;
    vector<treeNode*> stack;
    treeNode *currentNode = r;
    while (currentNode)
    {
        if (r->left != nullptr && (i == 0 || stack[i] != currentNode))
        {
            stack[i++] = currentNode;
            currentNode = r->left;
            continue;
        }
        cout << currentNode->data << ' ';
        if (r->right != nullptr)
        {
            currentNode = r->right;
            continue;
        }
        if (i != 0)
            currentNode = stack[--i];
        else
            break;
    }
}

template <typename T>
void binaryTree<T>::postOrder(treeNode *r)
{
    if (r == nullptr)
        r = root;

    int i = 0;
    vector<treeNode*> left_stack;
    vector<treeNode*> right_stack;
    treeNode *currentNode = r;
    while (currentNode)
    {
        if (r->left != nullptr && (i == 0 || left_stack[i] != currentNode))
        {
            left_stack[i] = currentNode;
            right_stack[i++] = nullptr;
            currentNode = r->left;
            continue;
        }
        if (r->right != nullptr && (i == 0 || right_stack[i] != currentNode))
        {
            if (left_stack[i] != currentNode)
                left_stack[i] = nullptr;
            right_stack[i++] = currentNode;
            currentNode = r->right;
            continue;
        }
        cout << currentNode->data << ' ';
        if (i != 0)
            currentNode = left_stack[--i] == nullptr ? right_stack[i] : left_stack[i];
        else
            break;
    }
}

template <typename T>
void binaryTree<T>::levelOrder(treeNode *r)
{
    if (r == nullptr)
        r = root;

    queue q;
    q.push(r);

    treeNode *currentNode;
    while (q.len() != 0)
    {
        currentNode = q.pop();
        cout << currentNode->data << ' ';
        if (currentNode->left != nullptr)
            q.push(currentNode->left);
        if (currentNode->right != nullptr)
            q.push(currentNode->right);
    }
}


int main()
{
    return 0;
}