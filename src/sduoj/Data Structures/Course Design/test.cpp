/**
 * 试图完成大数字的加减乘
 * 相比已经成熟的高精度办法必然有所欠缺
 * 只是简单的思考与测试
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

class Infint
{
protected:
    vector<ll> value;
    static const int WIDTH = 9;
    static const int LIMIT = 1000000000;

public:
    Infint() { value.reserve(8); }

    void plus(const Infint &other);

    friend istream &operator>>(istream &is, Infint &infint);
    friend ostream &operator<<(ostream &os, const Infint &infint);

    Infint operator+=(const Infint &other)
    {
        plus(other);
        return *this;
    }
};

void Infint::plus(const Infint &other)
{
    ll addition = 0;
    auto sit = this->value.begin();
    vector<ll>::const_iterator oit = other.value.begin();

    while (sit != this->value.end() && oit != other.value.end())
    {
        *sit = *sit + *oit + addition;
        addition = *sit / Infint::LIMIT;
        *sit %= Infint::LIMIT;

        ++sit, ++oit;
    }

    if (sit == this->value.end())
    {
        while (oit != other.value.end())
        {
            ll tmp = *oit + addition;
            addition = tmp / Infint::LIMIT;
            tmp %= Infint::LIMIT;
            this->value.push_back(tmp);

            ++oit;
        }
    }
    else
    {
        while (sit != this->value.end())
        {
            *sit += addition;
            addition = *sit / Infint::LIMIT;
            *sit %= Infint::LIMIT;

            ++sit;
        }
    }

    if (addition)
        this->value.push_back(addition);
}

istream &operator>>(istream &is, Infint &infint)
{
    string input;
    is >> input;

    infint.value.clear();
    for (int i = input.length(); i > 0; i -= Infint::WIDTH)
    {
        int start = max(0, i - Infint::WIDTH);
        int len = i - start;
        ll part = stoll(input.substr(start, len));
        infint.value.push_back(part);
    }

    return is;
}

ostream &operator<<(ostream &os, const Infint &infint)
{
    os << infint.value.back(); // 输出最高位
    for (int i = infint.value.size() - 2; i >= 0; --i) {
        os << setw(Infint::WIDTH) << setfill('0') << infint.value[i]; // 输出其他位，补零
    }
    return os;
}

int main()
{
    Infint a, b;
    cin >> a >> b;
    a += b;
    cout << a << '\n';

    return 0;
}