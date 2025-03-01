#include<iostream>
#include<string>
#include<vector>

using namespace std;

typedef unsigned char uint8_t;

struct InfInt
{
    vector<uint8_t> value;

    InfInt(int n = 50) { value.reserve(n); }
    InfInt(const InfInt& other)
    {
        for (uint8_t val: other.value)
            value.push_back(val);
    }

    void push_back(uint8_t val) { value.push_back(val); }
    int getLength() const { return value.size(); }

    InfInt operator+(const InfInt& other) const
    {
        uint8_t addition = 0;
        InfInt res(max(getLength(), other.getLength()));

        vector<uint8_t>::const_iterator sit = value.begin(), oit = other.value.begin();
        while(sit != value.end() || oit != other.value.end())
        {
            uint8_t tmp = addition;
            if (sit != value.end()) tmp += *sit++;
            if (oit != other.value.end()) tmp += *oit++;
            if (tmp < 10)
            {
                addition = 0;
                res.push_back(tmp);
            }
            else
            {
                addition = 1;
                res.push_back(tmp - 10);
            }
        }

        if (addition) res.push_back(addition);
        return res;
    }
};

istream& operator>>(istream& is, InfInt& num)
{
    string tmp;
    is >> tmp;
    for(auto it = tmp.rbegin(); it != tmp.rend(); ++it)
        num.push_back(*it - '0');
    return is;
}

ostream& operator<<(ostream& os, const InfInt& num)
{
    for(vector<uint8_t>::const_reverse_iterator it = num.value.rbegin(); it != num.value.rend(); ++it)
        os << (char)(*it + 48);
    return os;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    InfInt a, b;
    cin >> a >> b;
    cout << a + b;

    return 0;
}