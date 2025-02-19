#include "iostream"
#include "vector"

using namespace std;

int main() 
{
    long long n, count = 0, min = 100000;
    long long r1 = 0, r2 = 0;
    const long long mod = 1000000007;
    bool flag = false;
    vector<long long> v;
    cin >> n;
    cin >> r1;
    if (r1 == 1) count++;
    else 
    {
        v.push_back(r1);
        if (r1 < min && r1 > 1) min = r1;
    }
    for (int i = 1; i < n; i++) {
        long long x;
        cin >> x;

        if (x == 1) {
            r1 += 1;
            count++;
        }
        else {
            r1 *= x;
            v.push_back(x);
        }
        if (x < min && x > 1) min = x;

        r1 %= mod;
    }
    
    if (count == 0) {
        r2 = 1;
    } else if (count == 1) {
        flag = true;
        r2 = 1 + min;
    } else {
        r2 = count;
    }
    for (int i = 0; i < v.size(); i++) {
        if (flag && v[i] == min)
        {
            flag = false;
            continue;
        }
        r2 *= v[i];
        r2 %= mod;
    }

    cout << r1 << " " << r2 << endl;

    return 0;
}