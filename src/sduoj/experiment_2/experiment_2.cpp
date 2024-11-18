#include <iostream>
using namespace std;

template<class T>
class arrayList
{
    public:
        arrayList(int initialLen = 10);
        arrayList(const arrayList<T>&);
        ~arrayList() {delete [] element;}

        void push(const T& theElement);
        void rankSort();
        void selectionSort();
        void bubbleSort();
        void insertionSort();
        void output(ostream& out) const;
    
    protected:        
        T* element;
        int length;
        int size;
};

template<class T>
arrayList<T>::arrayList(int initialLen)
{
    if (initialLen < 1) throw "initialLen should be > 0!";
    length = initialLen;
    element = new T[length];
    size = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
    length = theList.length;
    element = new T[length];
    size = theList.size;
    for (int i = 0; i < length; i++)
        element[i] = theList.element[i];
}

template<class T>
void arrayList<T>::push(const T& theElement)
    {element[size++] = theElement;}

template<class T>
void arrayList<T>::rankSort()
{
    int *rank = new int[size]();
    T *res = new T[size]();
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (element[i] <= element[j]) rank[j] += 1;
            else rank[i] += 1;
    for (int i = 0; i < size; i++)
        res[rank[i]] = element[i];
    for (int i = 0; i < size; i++)
        element[i] = res[i];
    delete rank;
    delete res;
}

template<class T>
void arrayList<T>::selectionSort()
{
    T *max, tmp;
    bool isSort = false;
    for (int i = 1; i < size && !isSort; i++)
    {
        max = &element[0];
        isSort = true;
        for (int j = 1; j < size - i + 1; j++)
            if (element[j] > *max) max = &element[j];
            else isSort = false;
        tmp = element[size - i];
        element[size - i] = *max;
        *max = tmp;
    }
}

template<class T>
void arrayList<T>::bubbleSort()
{
    T tmp;
    bool isSort = false;
    for (int i = 1; i < size && !isSort; i++)
    {
        isSort = true;
        for (int j = 0; j < size - i; j++)
            if (element[j] > element[j + 1])
            {
                tmp = element[j + 1];
                element[j + 1] = element[j];
                element[j] = tmp;
                isSort = false;
            }
    }
}

template<class T>
void arrayList<T>::insertionSort()
{
    T *tmp = new T[size]();
    int tmpSize = 1;
    tmp[0] = element[0];
    for (int i = 1; i < size; i++, tmpSize++)
    {
        int j = 0;
        for (; j < tmpSize; j++)
            if (element[i] < tmp[j])
            {
                for (int k = tmpSize; k > j; k--)
                    tmp[k] = tmp[k - 1];
                tmp[j] = element[i];
                break;
            }
        if (j == tmpSize) tmp[tmpSize] = element[i];
    }            
    for (int i = 0; i < size; i++)
        element[i] = tmp[i];             
}

template<class T>
void arrayList<T>::output(ostream& out) const
{
    for (int i = 0; i < size; i++)
        out << element[i] << ' ';
}

template<class T>
ostream& operator<<(ostream& out, const arrayList<T>& lst)
    {lst.output(out); return out;}

int main()
{
    int n, tmp;
    cin >> n;
    arrayList<int> lst(n);
    for (; n > 0; n--)
    {
        cin >> tmp;
        lst.push(tmp);
    }
    // lst.rankSort();
    // lst.selectionSort();
    // lst.bubbleSort();
    lst.insertionSort();
    cout << lst << endl;
    return 0;
}