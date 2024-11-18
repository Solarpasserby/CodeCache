#include "iostream"
#include "vector"
using namespace std;

template <typename T>
class hashingTable
{
public:
    hashingTable(int d);
    ~hashingTable()
    {
        delete[] table;
        delete[] used_space;
    }

    int hashFun(T element);
    int insert(T element);
    int search(T element);
    int erase(T element);

private:
    int division;
    T *table;
    char *used_space;
};

template <typename T>
hashingTable<T>::hashingTable(int d)
{
    division = d;
    table = new T[d]();
    used_space = new char[d]();
    for (int i = 0; i < d; i++)
    {
        used_space[i] = 0;
    }
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

    if (used_space[hashNum] == 0)
    {
        used_space[hashNum] = 1;
        table[hashNum] = element;
        return hashNum;
    }
    else if (table[hashNum] == element)
    {
        return -2;
    }
    else
    {
        int i = 0;
        for (; i < division; i++)
        {
            int tmp = hashFun(element + i);
            if (used_space[tmp] == 0)
            {
                used_space[tmp] = 1;
                table[tmp] = element;
                return tmp;
            }
        }
        return -1;
    }
}

template <typename T>
int hashingTable<T>::search(T element)
{
    int i = 0;
    for (; i < division; i++)
    {
        int tmp = hashFun(element + i);
        if (used_space[tmp] == 0)
        {
            return -1;
        }
        else if (table[tmp] == element)
        {
            return tmp;
        }
    }
    if (i == division)
    {
        return -1;
    }
}

template <typename T>
int hashingTable<T>::erase(T element)
{
    int i = 0;
    for (; i < division; i++)
    {
        int tmp = hashFun(element + i);
        if (used_space[tmp] == 0)
        {
            return -1;
        }
        else if (table[tmp] == element)
        {
            int p, q, j, res;
            q = tmp;
            res = 0;
            for (j = 1; j < division; j++)
            {
                p = hashFun(element + i + j);
                if (used_space[p] == 0)
                {
                    used_space[q] = 0;
                    return res;
                }
                else if (hashFun(table[p]) == p || q < hashFun(table[p]) && hashFun(table[p]) < p || p < q && q < hashFun(table[p]) || hashFun(table[p]) < p && p < q)
                {
                    continue;
                }
                else
                {
                    table[q] = table[p];
                    q = p;
                    res++;
                }
            }
            used_space[q] = 0;
            return res;
        }
    }
    return -1;
}

int main()
{
    int division, m, opt, x, rc;
    cin >> division >> m;
    hashingTable<int> hashing_table(division);

    for (int i = 0; i < m; i++)
    {
        cin >> opt >> x;
        switch (opt)
        {
        case 0:
            rc = hashing_table.insert(x);
            if (rc == -2)
            {
                cout << "Existed" << endl;
            }
            else if (rc == -1)
            {
                cout << "Not Found" << endl;
            }
            else
            {
                cout << rc << endl;
            }
            
            break;
        
        case 1:
            rc = hashing_table.search(x);
            cout << rc << endl;
            break;

        case 2:
            rc = hashing_table.erase(x);
            if (rc == -1)
            {
                cout << "Not Found" << endl;
            }
            else
            {
                cout << rc << endl;
            }
            break;
        
        default:
            break;
        }
    }
    return 0;
}