#include<bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    set<string> notebook;

    cin >> n;
    for(;n--;)
    {
        int op;
        string word;
        cin >> op;
        
        switch (op)
        {
        case 1:
            cin >> word;
            if (notebook.find(word) != notebook.end())
                cout << "found" << '\n';
            else
            {
                notebook.insert(word);
                cout << "write" << '\n';
            }
            break;

        case 2:
            cin >> word;
            if (notebook.find(word) == notebook.end())
                cout << "not found" << '\n';
            else
            {
                notebook.erase(word);
                cout << "erased" << '\n';
            }
            break;

        case 3:
            for(auto it = notebook.begin(); it != notebook.end(); ++it)
                cout << *it << ' ';
            cout << '\n';
            break;
        
        default:
            break;
        }
    }

    return 0;
}