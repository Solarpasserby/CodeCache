#include "iostream"
#include "vector"

using namespace std;

// vector<int> digit;

// void process(long long n)
// {
//     digit.clear();
//     digit.push_back(0);
//     for (int i = 1; i <= n; i++)
//     {
//         digit.push_back(i);
//     }

//     for (int i = 2; i <= n; i++)
//     {
//         if (digit[i] == i)
//         {
//             for (int j = i; j <= n; j += i)
//             {
//                 digit[j] = digit[j] / i * (i - 1);
//             }
//         }
//     }
// }

int main()
{
    long long L, R, result = 0;
    cin >> L >> R;

    result = (R + L) * (R - L + 1) / 2;
    if (L == 1) result += 1;

    cout << result << endl;
}