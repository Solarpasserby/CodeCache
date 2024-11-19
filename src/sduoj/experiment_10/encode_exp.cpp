#include "iostream"
#include "string"
#include "vector"

using namespace std;

class heap
{
public:
    heap();
    // ~heap();

    void heapify(const vector<int> &freq);
    void push(int treeNode);
    void pop();

    int top() { return data[1]; }
    int size() { return data.size(); }

protected:
    vector<int> data;
};

heap::heap()
{
    data.push_back(INT32_MIN);
}

void heap::heapify(const vector<int> &freq)
{
    for (int i = 0; i < freq.size(); i++)
    {
        data.push_back(freq[i]);
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
}

void heap::push(int treeNode)
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

void heap::pop()
{
    if (data.size() == 1)
    {
        return;
    }
    int result = data[1];
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

int main()
{
    heap h;
    string str;
    int a[26] = {0};
    int result = 0;
    vector<int> freq;
    cin >> str;

    for (char c : str)
    {
        a[c - 'a']++;
    }

    for (int i = 0; i < 26; i++)
    {
        if (a[i] != 0)
        {
            freq.push_back(a[i]);
        }
    }

    h.heapify(freq);

    while (h.size() > 2)
    {
        int x = h.top(); h.pop();
        int y = h.top(); h.pop();
        int z = x + y;
        h.push(z);

        result += z;
    }

    cout << result << endl;

    return 0;
}