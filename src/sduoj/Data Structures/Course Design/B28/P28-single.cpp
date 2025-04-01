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
        value.clear();
        for (const uint8_t& val: other.value)
            value.push_back(val);
    }

    void push_back(uint8_t val) { value.push_back(val); }
    int getLength() const { return value.size(); }
    bool checkIfZero() const { return (value.size() == 1 && value.front() == 0); }
    pair<uint8_t, uint8_t> digitMul(uint8_t a, uint8_t b)
    {
        pair<uint8_t, uint8_t> res;
        res.first = a * b / 10;
        res.second = a * b % 10;
        return res;
    }

    void rmZero()
    {
        if(value.empty()) return;

        for(auto it = value.rbegin(); (it + 1) != value.rend(); ++it)
            if(*it == 0) value.pop_back();
            else break;
    }


    InfInt operator+(const InfInt& other) const
    {
        uint8_t addition = 0;
        InfInt res(max(50, max(getLength(), other.getLength()) + 1));

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

        res.rmZero();
        return res;
    }

    InfInt operator+=(const InfInt other)
    {
        uint8_t addition = 0;

        if (other.checkIfZero()) return *this;

        for(int i = getLength(); i < other.getLength(); i++)
            value.push_back(0);

        vector<uint8_t>::const_iterator it = other.value.begin();
        for(uint8_t& val: value)
        {
            val += addition;
            if (it != other.value.end()) val += *it++;
            if (val < 10) addition = 0;
            else
            {
                addition = 1;
                val -= 10;
            }
        }
        if (addition) value.push_back(addition);

        this->rmZero();
        return *this;
    }

    InfInt operator*(const InfInt other)
    {
        int times = 0, initLength = max(50, getLength() + other.getLength());
        InfInt res(initLength);

        if (other.checkIfZero() || this->checkIfZero())
        {
            res.push_back(0);
            return res;
        }

        for(uint8_t mult: other.value)
        {
            InfInt tmp(initLength);
            uint8_t addition = 0;
            for(int i = 0; i < times; i++)
                tmp.push_back(0);

            for(uint8_t val: value)
            {
                auto digit = digitMul(mult, val);
                digit.second += addition;
                if (digit.second > 10)
                {
                    digit.second -= 10;
                    digit.first += 1;
                }
                addition = digit.first;
                tmp.push_back(digit.second);
            }

            if(addition) tmp.push_back(addition);
            addition = 0;

            res += tmp;
            ++times;
        }

        res.rmZero();
        return res;
    }
};

istream& operator>>(istream& is, InfInt& num)
{
    string tmp;
    is >> tmp;
    for(auto it = tmp.rbegin(); it != tmp.rend(); ++it)
        if(*it >= '0' && *it <= '9') num.push_back(*it - '0');
        else throw invalid_argument("Invalid input: unable to read integer.");
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
    cout << a * b;

    return 0;
}