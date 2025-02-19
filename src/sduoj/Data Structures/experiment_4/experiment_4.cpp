#include <iostream>
using namespace std;

template <class T>
struct chainNode
{
    T element;
    chainNode<T> *next;

    chainNode() {}
    chainNode(const T &element)
    {
        this->element = element;
    }
    chainNode(const T &element, chainNode<T> *next)
    {
        this->element = element;
        this->next = next;
    }
};

template <class T>
class chainIterater
{
public:
    chainIterater(chainNode<T> *theNode = NULL) { node = theNode; }

    T &operator*() const { return node->element; }

    chainIterater &operator++()
    {
        node = node->next;
        return *this;
    }

    bool operator!=(const chainIterater right) const { return node != right.node; }
    bool operator==(const chainIterater right) const { return node == right.node; }

protected:
    chainNode<T> *node;
};

template <class T>
class chain
{
public:
    chain();
    chain(const chain<T> &);
    ~chain();

    int indexOf(const T &theElement) const;
    void insert(int theIndex, const T &theElement);
    void push(const T &theElement);
    void erase(int theIndex);
    void reverse();
    void set(int theIndex, const T &theElement);
    void output(ostream &out) const;

    T sumxor() const;
    int indexOfSeq(const T &theElement) const;
    void handleInput();

    chainIterater<T> begin() const { return chainIterater<T>(firstNode); }
    chainIterater<T> end() const { return chainIterater<T>(NULL); }

protected:
    chainNode<T> *firstNode;
    int listSize;
};

template <class T>
chain<T>::chain()
{
    firstNode = NULL;
    listSize = 0;
}

template <class T>
chain<T>::chain(const chain<T> &theChain)
{
    listSize = theChain.listSize;

    if (listSize == 0)
    {
        firstNode = NULL;
        return;
    }

    chainNode<T> *sourceNode = theChain.firstNode;
    firstNode = new chainNode<T>(sourceNode->element);
    sourceNode = sourceNode->next;
    chainNode<T> *targetNode = firstNode;

    while (sourceNode != NULL)
    {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }

    targetNode->next = NULL;
}

template <class T>
chain<T>::~chain()
{
    while (firstNode)
    {
        chainNode<T> *nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template <class T>
int chain<T>::indexOf(const T &theElement) const
{
    chainNode<T> *targetNode = firstNode;
    for (int i = 0; i < listSize; i++)
    {
        if (targetNode->element == theElement)
            return i;
        targetNode = targetNode->next;
    }
    return -1;
}

template <class T>
void chain<T>::insert(int theIndex, const T &theElement)
{
    if (theIndex == 0)
        firstNode = new chainNode<T>(theElement, firstNode);
    else
    {
        chainNode<T> *preNode = firstNode;
        for (int i = 1; i < theIndex; i++)
            preNode = preNode->next;
        preNode->next = new chainNode<T>(theElement, preNode->next);
    }

    listSize++;
}

template <class T>
void chain<T>::push(const T &theElement)
{
    static chainNode<T> *lastNode;

    if (listSize == 0)
    {
        firstNode = new chainNode<T>(theElement, firstNode);
        lastNode = firstNode;
    }
    else
    {
        while (lastNode->next)
        {
            lastNode = lastNode->next;
        }

        lastNode->next = new chainNode<T>(theElement, lastNode->next);
        lastNode = lastNode->next;
    }

    listSize++;
}

template <class T>
void chain<T>::erase(int theIndex)
{
    chainNode<T> *targetNode;

    if (theIndex == 0)
    {
        targetNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        chainNode<T> *preNode = firstNode;
        for (int i = 1; i < theIndex; i++)
            preNode = preNode->next;
        targetNode = preNode->next;
        preNode->next = preNode->next->next;
    }

    delete targetNode;
    listSize--;
}

template <class T>
void chain<T>::reverse()
{
    chainNode<T> *targetNode, *p, *q, *tmp1, *tmp2;
    p = firstNode;
    targetNode = q = firstNode->next;

    for (int i = 1; i < listSize; i++)
    {
        if (i % 2 == 1)
        {
            tmp1 = targetNode->next;
            targetNode->next = p;
            targetNode = p = tmp1;
        }
        else
        {
            tmp2 = targetNode->next;
            targetNode->next = q;
            targetNode = q = tmp2;
        }
    }

    firstNode->next = NULL;
    firstNode = p == NULL ? q : p;
}

template <class T>
void chain<T>::set(int theIndex, const T &theElement)
{
    // 检查索引theIndex
    if (theIndex < 0 || theIndex >= listSize)
        throw "the index that you input is invalid!";

    chainNode<T> *targetNode = firstNode;
    for (int i = 0; i < theIndex; i++)
        targetNode = targetNode->next;
    targetNode->element = theElement;
}

template <class T>
void chain<T>::output(ostream &out) const
{
    for (chainNode<T> *currentNode = firstNode; currentNode; currentNode = currentNode->next)
        out << currentNode->element << " -> ";
}

template <class T>
ostream &operator<<(ostream &out, const chain<T> &thechain)
{
    thechain.output(out);
    out << "nullptr";
    return out;
}

template <class T>
T chain<T>::sumxor() const
{
    int i = 0;
    T res = 0;
    for (chainIterater<T> it = begin(); it != end(); ++it)
        res += i++ ^ *it;
    return res;
}

template <class T>
int chain<T>::indexOfSeq(const T &theElement) const
{
    if (listSize == 0)
        return 0;
    chainNode<T> *targetNode = firstNode;
    for (int i = 0; i < listSize; i++)
    {
        if (targetNode->element > theElement)
            return i;
        targetNode = targetNode->next;
    }
    return listSize;
}

template <class T>
void chain<T>::handleInput()
{
    int opNum;
    cin >> opNum;
    if (opNum == 1)
    {
        int theIndex;
        T theElement;
        cin >> theIndex >> theElement;
        insert(theIndex, theElement);
    }
    else if (opNum == 2)
    {
        int theIndex;
        T theElement;
        cin >> theElement;
        theIndex = indexOf(theElement);
        if (theIndex == -1)
            cout << theIndex << endl;
        else
            erase(theIndex);
    }
    else if (opNum == 3)
        reverse();
    else if (opNum == 4)
    {
        T theElement;
        cin >> theElement;
        cout << indexOf(theElement) << endl;
    }
    else if (opNum == 5)
        cout << sumxor() << endl;
}

template <class T>
chain<T> chainCombine(const chain<T> &chainA, const chain<T> &chainB)
{
    chain<T> chainRes;
    chainIterater<T> a = chainA.begin(), b = chainB.begin();
    while (a != chainA.end() && b != chainB.end())
    {
        if (*a < *b)
        {
            chainRes.push(*a);
            ++a;
        }
        else
        {
            chainRes.push(*b);
            ++b;
        }
    }
    while (a != chainA.end())
    {
        chainRes.push(*a);
        ++a;
    }
    while (b != chainB.end())
    {
        chainRes.push(*b);
        ++b;
    }

    return chainRes;
}

int main()
{
    // // 题目一
    // int N, Q;
    // long long element;
    // chain<long long> chainList;
    // cin >> N >> Q;
    // for (int i = 0; i < N; i++)
    // {
    //     cin >> element;
    //     chainList.insert(i, element);
    // }
    // for (int j = 0; j < Q; j++)
    //     chainList.handleInput();

    // 题目二
    int N, M;
    chain<long long> chainN, chainM;
    long long element;

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        cin >> element;
        chainN.insert(chainN.indexOfSeq(element), element);
    }
    for (int j = 0; j < M; j++)
    {
        cin >> element;
        chainM.insert(chainM.indexOfSeq(element), element);
    }
    chain<long long> chainNM = chainCombine(chainN, chainM);
    cout << chainN.sumxor() << endl;
    cout << chainM.sumxor() << endl;
    cout << chainNM.sumxor() << endl;
    return 0;

    // // DEBUG
    // long long a;
    // chain<long long> chainTest1, chainTest2;
    // for (int i = 0; i < 4; i++)
    //     chainTest1.push(5 + i);
    // for (int i = 0; i < 3; i++)
    //     chainTest2.push(4);

    // chain<long long> chainTest = chainCombine(chainTest1, chainTest2);
    // cout << chainTest1 << endl;
}