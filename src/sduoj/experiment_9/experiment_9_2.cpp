#include "iostream"
#include "vector"
#include "stack"

using namespace std;

class chainNode
{
public:
    int data;
    chainNode *next;
    chainNode *prev;

    chainNode(int data_, chainNode *next_ = nullptr, chainNode *prev_ = nullptr)
        : data(data_), next(next_), prev(prev_) {}
};

class chain
{
public:
    chain();
    ~chain();

    void push(int data);
    void push(chainNode *node);
    void insert(chain *chain_);
    chainNode *search(int data);

    chainNode *head;
    chainNode *tail;
};

chain::chain()
{
    head = new chainNode(INT32_MAX);
    tail = head;
}

chain::~chain()
{
    chainNode *nextNode;
    while (head != nullptr)
    {
        nextNode = head->next;
        delete head;
        head = nextNode;
    }
}

void chain::push(int data)
{
    tail->next = new chainNode(data);
    tail->next->prev = tail;
    tail = tail->next;
}

void chain::push(chainNode *node)
{
    tail->next = node;
    tail->next->prev = tail;
    tail = tail->next;
}

void chain::insert(chain *chain_)
{
    tail->prev->next = chain_->head->next;
    chain_->head->next->prev = tail->prev;
    tail->prev = chain_->tail;
    chain_->tail->next = tail;
    chain_->head = nullptr;
    delete chain_;
}

chainNode *chain::search(int data)
{
    static chainNode *current = head->next;
    while (current != nullptr)
    {
        if (current->data == data)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

chain origin;
chain result;

void handleInput(int data)
{
    static stack<chainNode *> nextStack;
    static stack<chainNode *> endStack;
    static stack<chain *> chainStack;
    static chainNode *end, *start;
    static bool isRoot = false;
    chainNode *temp = new chainNode(data);
    
    if (data == INT32_MAX)
    {
        while (chainStack.size() > 1)
        {
            chain *topChain = chainStack.top();
            chainStack.pop();
            chainStack.top()->insert(topChain);
        }
        result = *chainStack.top();
        chainStack.pop();
        return;
    }

    if (nextStack.empty())
    {
        end = origin.head->next;
        start = origin.search(data);

        endStack.push(end);
        nextStack.push(start);
        end = start->next;

        chain *tempChain = new chain();
        tempChain->push(temp);
        chainStack.push(tempChain);
        return;
    }

    if (nextStack.top() != endStack.top() && nextStack.top()->prev->data == data)
    {
        nextStack.top() = nextStack.top()->prev;
        chainStack.top()->push(temp);
    }
    else if (nextStack.top() != endStack.top())
    {
        start = origin.search(data);

        endStack.push(end);
        nextStack.push(start);
        end = start->next;

        chain *tempChain = new chain();
        tempChain->push(temp);
        chainStack.push(tempChain);
    }
    else
    {
        nextStack.pop();
        endStack.pop();
        if (nextStack.empty() && !isRoot)
        {
            isRoot = true;
        }
        if (nextStack.empty() || nextStack.top()->prev->data != data)
        {
            start = origin.search(data);

            endStack.push(end);
            nextStack.push(start);
            end = start->next;

            chain *tempChain = new chain();
            tempChain->push(temp);
            chainStack.push(tempChain);
        }
        else if(!isRoot)
        {
            while (chainStack.size() > 1 && chainStack.size() > endStack.size())
            {
                chain *topChain = chainStack.top();
                chainStack.pop();
                chainStack.top()->insert(topChain);
            }

            nextStack.top() = nextStack.top()->prev;
            chainStack.top()->push(temp);
        }
        else
        {
            while (chainStack.size() > 2 && chainStack.size() - 2 > endStack.size())
            {
                chain *topChain = chainStack.top();
                chainStack.pop();
                chainStack.top()->insert(topChain);
            }

            nextStack.top() = nextStack.top()->prev;
            chainStack.top()->push(temp);
        }
    }
}

int main()
{
    int n, data;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> data;
        origin.push(data);
    }

    for (int i = 0; i < n; i++)
    {
        cin >> data;
        handleInput(data);
    }
    handleInput(INT32_MAX);

    for (chainNode *current = result.head->next; current != nullptr; current = current->next)
    {
        cout << current->data << " ";
    }

    return 0;
}