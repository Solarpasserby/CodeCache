#include "iostream"
#include "string"
#include "vector"

using namespace std;

vector<char> fourCard;
vector<char> tripleCard;
vector<char> doubleCard;
vector<char> singleCard;
vector<int> freq(14, 0);

int checkcard(const string &str)
{
    if(!fourCard.empty())
    {
        if (!tripleCard.empty())
        {
            string temp = str;
            for (int i = 0; i < str.size(); i++)
            {
                if (fourCard[0] == str[i])
                {
                    temp.erase(i, 1);
                }
            }
        }
    }
}

int main()
{
    int n;
    string str;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        for (int j = 0; j < str.size(); j++)
        {
            if (str[j] > '1' && str[j] <= '9')
            {
                freq[str[j] - '0']++;
            }
            else
            {
                if (str[j] == 'A')
                {
                    freq[1]++;
                }
                else if (str[j] == 'J')
                {
                    freq[11]++;
                }
                else if (str[j] == 'Q')
                {
                    freq[12]++;
                }
                else if (str[j] == 'K')
                {
                    freq[13]++;
                }
                else if (str[j] == 'X')
                {
                    freq[10]++;
                }
            }    
        }
        for (int j = 1; j <= 13; j++)
        {
            if (freq[j] == 4)
            {
                fourCard.push_back(j);
            }
            else if (freq[j] == 3)
            {
                tripleCard.push_back(j);
            }
            else if (freq[j] == 2)
            {
                doubleCard.push_back(j);
            }
            else if (freq[j] == 1)
            {
                singleCard.push_back(j);
            }
        }

        // if (checkcard(str))
        // {
        //     cout << "YES" << endl;
        // }
        // else
        // {
        //     cout << "NO" << endl;
        // }
    }
    return 0;
}