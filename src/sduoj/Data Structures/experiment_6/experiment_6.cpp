#include <iostream>
#include <stack>
using namespace std;

stack<char> op;
stack<double> num;

void handleOp(char o)
{
    double n, m;
    n = num.top();
    num.pop();
    m = num.top();
    num.pop();

    switch (o)
    {
    case '+':
        num.push(m + n);
        break;

    case '-':
        num.push(m - n);
        break;

    case '*':
        num.push(m * n);
        break;

    case '/':
        num.push(m / n);
        break;

    default:
        break;
    }
}

void calculate()
{
    char c;

    cin.get(c);
    while (c != '\n')
    {
        if (c >= '0')
            num.push(static_cast<double>(c - '0'));
        else
        {
            switch (c)
            {
            case '+':
            case '-':
                while (!op.empty() && op.top() != '(')
                {
                    handleOp(op.top());
                    op.pop();
                }
                op.push(c);
                break;

            case '*':
            case '/':
                while (!op.empty() && op.top() != '+' && op.top() != '-' && op.top() != '(')
                {
                    handleOp(op.top());
                    op.pop();
                }
                op.push(c);
                break;

            case '(':
                op.push(c);
                break;

            case ')':
                while (op.top() != '(')
                {
                    handleOp(op.top());
                    op.pop();
                }
                if (!op.empty())
                    op.pop();
                break;

            default:
                break;
            }
        }

        cin.get(c);
    }

    while (!op.empty())
    {
        handleOp(op.top());
        op.pop();
    }

    printf("%.2lf\n", num.top());
    num.pop();
}

int main()
{
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++)
        calculate();
    return 0;
}