#include "iostream"

using namespace std;

int n;
int *preOrder, *inOrder;

void func(int l, int r, int li)
{
    if (l > r) return;

    int i = 0, root = preOrder[l];
    for (; inOrder[li + i] != root; i++);
    func(l + 1, l + i, li);
    func(l + i + 1, r, li + i + 1);
    cout << root << " ";
}

int main(){
    cin >> n;
    preOrder = new int[n];
    inOrder  = new int[n];

    for (int i = 0; i < n; i++)
    {
        cin >> preOrder[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> inOrder[i];
    }

    func(0, n - 1, 0);
    
    return 0;
}