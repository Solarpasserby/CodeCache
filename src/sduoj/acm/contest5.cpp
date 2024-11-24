#include "iostream"
#include "vector"

using namespace std;

int main()
{
    int t, n;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        cin >> n;
        int temp, count = 0;
        for (int j = 0; j < n; j++)
        {
            cin >> temp;
            if (temp == 1) count++;
        }
        if (count == n)
        {
            if (n % 2 == 0)
            {
                cout << "Student" << endl;
            }
            else
            {
                cout << "Cxlian" << endl;
            }
        }
        else
        {
            if (count % 2 == 0)
            {
                cout << "Cxlian" << endl;
            }
            else
            {
                cout << "Student" << endl;
            }
        }
    }
    return 0;
}