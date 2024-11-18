#include "iostream"
#include "vector"
#include "stack"

using namespace std;

struct treeNode
{
    int data;
    int height;
    int nodes;
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
    // ~heap();

    void push(T treeNode);
    T pop();

    T* get(int i);

protected:
    vector<T> data;
};

template <typename T>
heap<T>::heap()
{
    data.push_back(nullptr);
}

template <typename T>
void heap<T>::push(T treeNode)
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
    T result = data[1];
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
T* heap<T>::get(int i)
{
    if (i < data.size() && data.size() > 1)
    {
        return data[i];
    }
    return nullptr;
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
class binaryTree
{
public:
    binaryTree();
    // ~binaryTree();

    void lineInsert(T l, T r);

    void preOrder(treeNode *r = nullptr);
    void inOrder(treeNode *r = nullptr);
    void postOrder(treeNode *r = nullptr);
    void levelOrder(treeNode *r = nullptr);
    void printHeight(treeNode *r = nullptr);
    void printKids(treeNode *r = nullptr);

protected:
    treeNode *root;
    heap<treeNode*> treeHeap;
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
        left_->parent = target;
        treeHeap.push(left_);
    }
    if (r != -1)
    {
        right_ = new treeNode(r);
        right_->parent = target;
        treeHeap.push(right_);
    }

    target->left  = left_;
    target->right = right_;
}

template <typename T>
void binaryTree<T>::preOrder(treeNode* r)
{
    if (r == nullptr)
        r = root;

    cout << r->data << " ";
    if (r->left != nullptr)
        preOrder(r->left);
    if (r->right != nullptr)
        preOrder(r->right);

    if (r->left != nullptr && r->right != nullptr)
    {
        r->height = max(r->left->height, r->right->height) + 1;
        r->nodes = r->left->nodes + r->right->nodes + 1;
    }
    else if (r->left != nullptr)
    {
        r->height = r->left->height + 1;
        r->nodes = r->left->nodes + 1;
    }
    else if (r->right != nullptr)
    {
        r->height = r->right->height + 1;
        r->nodes = r->right->nodes + 1;
    }
    else
    {
        r->height = 1;
        r->nodes = 1;
    }
}

// template <typename T>
// void binaryTree<T>::inOrder(treeNode *r)
// {
//     if (r == nullptr)
//         r = root;
    
//     if (r->left != nullptr)
//         inOrder(r->left);
//     cout << r->data << " ";
//     if (r->right != nullptr)
//         inOrder(r->right);
// }

// template <typename T>
// void binaryTree<T>::postOrder(treeNode *r)
// {
//     if (r == nullptr)
//         r = root;

//     if (r->left != nullptr)
//         postOrder(r->left);
//     if (r->right != nullptr)
//         postOrder(r->right);
//     cout << r->data << " ";
// }

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
        if (currentNode->left != nullptr && (stack.empty() || stack[i] != currentNode))
        {
            if (i == stack.size())
                stack.push_back(nullptr);
            stack[i++] = currentNode;
            currentNode = currentNode->left;
            continue;
        }
        cout << currentNode->data << " ";
        if (currentNode->right != nullptr)
        {
            currentNode = currentNode->right;
            continue;
        }
        if (i != 0)
            currentNode = stack[--i];
        else
            break;
    }
}

// template <typename T>
// void binaryTree<T>::postOrder(treeNode *r)
// {
//     if (r == nullptr)
//         r = root;

//     int i = 0;
//     vector<treeNode*> left_stack;
//     vector<treeNode*> right_stack;
//     treeNode *currentNode = r;
//     while (currentNode)
//     {
//         if (currentNode->left != nullptr && (left_stack.empty() || left_stack[i] != currentNode))
//         {
//             if (i == left_stack.size())
//             {
//                 left_stack.push_back(nullptr);
//                 right_stack.push_back(nullptr);
//             }
//             left_stack[i] = currentNode;
//             right_stack[i++] = nullptr;
//             currentNode = currentNode->left;
//             continue;
//         }
//         if (currentNode->right != nullptr && (right_stack.empty() || right_stack[i] != currentNode))
//         {
//             if (i == right_stack.size())
//             {
//                 left_stack.push_back(nullptr);
//                 right_stack.push_back(nullptr);
//             }
//             if (left_stack[i] != currentNode)
//                 left_stack[i] = nullptr;
//             right_stack[i++] = currentNode;
//             currentNode = currentNode->right;
//             continue;
//         }
//         cout << currentNode->data << " ";
//         if (i != 0)
//             currentNode = left_stack[--i] == nullptr ? right_stack[i] : left_stack[i];
//         else
//             break;
//     }
// }

template <typename T>
void binaryTree<T>::postOrder(treeNode *r)
{
    if (r == nullptr)
        r = root;

    std::stack<treeNode*> s;
    treeNode *currentNode = r;
    treeNode *lastVisitedNode = nullptr;

    while (!s.empty() || currentNode != nullptr)
    {
        if (currentNode != nullptr)
        {
            s.push(currentNode);
            currentNode = currentNode->left;
        }
        else
        {
            treeNode *peekNode = s.top();
            if (peekNode->right != nullptr && lastVisitedNode != peekNode->right)
            {
                currentNode = peekNode->right;
            }
            else
            {
                std::cout << peekNode->data << " ";
                lastVisitedNode = s.top();
                s.pop();
            }
        }
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
        cout << currentNode->data << " ";
        if (currentNode->left != nullptr)
            q.push(currentNode->left);
        if (currentNode->right != nullptr)
            q.push(currentNode->right);
    }
}

template <typename T>
void binaryTree<T>::printHeight(treeNode *r)
{
    if (r == nullptr)
        r = root;

    treeHeap.push(r);
    treeNode *currentNode;
    currentNode = treeHeap.pop();

    while (currentNode != nullptr)
    {
        cout << currentNode->height << " ";
        if (currentNode->left != nullptr)
            treeHeap.push(currentNode->left);
        if (currentNode->right != nullptr)
            treeHeap.push(currentNode->right);
        currentNode = treeHeap.pop();
    }
}

template <typename T>
void binaryTree<T>::printKids(treeNode *r)
{
    if (r == nullptr)
        r = root;

    treeHeap.push(r);
    treeNode *currentNode;
    currentNode = treeHeap.pop();

    while (currentNode != nullptr)
    {
        cout << currentNode->nodes << " ";
        if (currentNode->left != nullptr)
            treeHeap.push(currentNode->left);
        if (currentNode->right != nullptr)
            treeHeap.push(currentNode->right);
        currentNode = treeHeap.pop();
    }
}


int main()
{
    int n;
    binaryTree<int> tree;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;
        tree.lineInsert(l, r);
    }
    tree.preOrder();
    cout << endl;
    tree.inOrder();
    cout << endl;
    tree.postOrder();
    cout << endl;
    tree.levelOrder();
    cout << endl;
    tree.printKids();
    cout << endl;
    tree.printHeight();
    cout << endl;

    return 0;
}