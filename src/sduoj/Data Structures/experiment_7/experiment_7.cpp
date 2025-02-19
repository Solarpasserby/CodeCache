#include "iostream"
using namespace std;

unsigned int func(unsigned int n)
{
    unsigned int m = 1;
    while (m < n) {
        m *= 2;
    }
    return m;
}

int main()
{
    unsigned int n;
    cin >> n;
    cout << (2 * n - func(n)) << endl;
    return 0;
}