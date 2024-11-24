#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

long long query(const vector<int>& v, int l, int r) {
    vector<int> temp(v.begin() + l - 1, v.begin() + r);
    sort(temp.begin(), temp.end());
    int center = temp[temp.size() / 2];
    long long cost = 0;

    for (int num : temp) {
        cost += abs(num - center);
    }

    return cost;
}

int main() {
    int n, m, x;
    cin >> n >> m;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        cout << query(v, l, r) << endl;
    }

    return 0;
}
