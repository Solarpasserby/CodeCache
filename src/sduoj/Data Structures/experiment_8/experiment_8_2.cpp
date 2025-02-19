#include "iostream"
using namespace std;

template <typename T>
class hashingNode
{
public:
    hashingNode(T theElement, hashingNode *theNext = nullptr) : element(theElement), next(theNext) {}
    ~hashingNode() {}

    T element;
    hashingNode<T> *next;
};

template <typename T>
class hashingHeadNode : public hashingNode<T>
{
public:
    hashingHeadNode() : hashingNode<T>(0, nullptr), length(0) {}
    ~hashingHeadNode() {}

    int length;
};

template <typename T>
class hashingTable
{

public:
    hashingTable(int d);
    ~hashingTable();

    int hashFun(T element);
    int insert(T element);
    int search(T element);
    int erase(T element);

    void clear();

private:
    int division;
    hashingNode<T> **table;
};

template <typename T>
hashingTable<T>::hashingTable(int d)
{

    division = d;
    table = new hashingNode<T> *[d];
    for (int i = 0; i < d; i++)
        table[i] = new hashingHeadNode<T>;
}

template <typename T>
hashingTable<T>::~hashingTable()
{
    clear();
    delete[] table;
}

template <typename T>
int hashingTable<T>::hashFun(T element)
{
    return (element % division);
}

template <typename T>
int hashingTable<T>::insert(T element)
{
    int hashNum = hashFun(element);
    hashingNode<T> *newNode = new hashingNode<T>(element);

    hashingNode<T> *lastNode = table[hashNum];
    while (lastNode->next != nullptr)
    {
        lastNode = lastNode->next;
        if (lastNode->element == element)
        {
            delete newNode;
            return -1;
        }
    }
    lastNode->next = newNode;

    (static_cast <hashingHeadNode<T> *>(table[hashNum]))->length++;
    return 0;
}

template <typename T>
int hashingTable<T>::search(T element)
{
    int hashNum = hashFun(element);
    hashingNode<T> *lastNode = table[hashNum];
    while (lastNode->next != nullptr)
    {
        lastNode = lastNode->next;
        if (lastNode->element == element)
            return (static_cast <hashingHeadNode<T> *>(table[hashNum]))->length;
    }
    return -1;
}

template <typename T>
int hashingTable<T>::erase(T element)
{
    int hashNum = hashFun(element);
    hashingNode<T> *lastNode = table[hashNum];
    hashingNode<T> *tempNode = lastNode->next;
    while (tempNode != nullptr)
    {
        if (tempNode->element == element)
        {
            lastNode->next = tempNode->next;
            delete tempNode;
            return --(static_cast <hashingHeadNode<T> *>(table[hashNum]))->length;
        }
        lastNode = tempNode;
        tempNode = tempNode->next;
    }
    return -1;
}

template <typename T>
void hashingTable<T>::clear()
{
    for (int i = 0; i < division; i++)
    {
        hashingNode<T> *lastNode = table[i];
        hashingNode<T> *tempNode = lastNode->next;
        while (tempNode != nullptr)
        {
            lastNode->next = tempNode->next;
            delete tempNode;
            tempNode = lastNode->next;
        }
    }
}


int main()
{
    int division, m, opt, element;
    cin >> division >> m;
    hashingTable<int> table(division);

    int rc;
    for (int i = 0; i < m; i++)
    {
        cin >> opt >> element;
        switch (opt)
        {
        case 0:
            rc = table.insert(element);
            if (rc == -1)
                cout << "Existed" << endl;
            break;
        case 1:
            rc = table.search(element);
            if (rc == -1)
                cout << "Not Found" << endl;
            else
                cout << rc << endl;
            break;
        case 2:
            rc = table.erase(element);
            if (rc == -1)
                cout << "Delete Failed" << endl;
            else
                cout << rc << endl;
            break;
        }
    }
    return 0;
}