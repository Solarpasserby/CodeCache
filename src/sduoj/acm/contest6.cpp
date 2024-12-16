#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

long long fast_pow(long long base, int exp) {
    long long result = 1;
    while (exp) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

int main() {
    int n, m;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cin >> m;
    vector<int> ks(m);
    for (int i = 0; i < m; i++) {
        cin >> ks[i];
    }

    for (int l = 0; l < m; l++) {
        int k = ks[l];
        unordered_map<long long, int> power_map;

        vector<long long> powers(n);
        for (int i = 0; i < n; i++) {
            powers[i] = fast_pow(a[i], k);
            if (power_map.find(powers[i]) == power_map.end()) {
                power_map[powers[i]] = 1;
            } else {
                power_map[powers[i]]++;
            }
        }

        long long count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                long long sum = powers[i] + powers[j];
                if (power_map.find(sum) != power_map.end()) {
                    if (i == j) {
                        count += power_map[sum];
                    } else {
                        count += 2 * power_map[sum];
                    }
                }
            }
        }

        cout << count << endl;
    }

    return 0;
}
