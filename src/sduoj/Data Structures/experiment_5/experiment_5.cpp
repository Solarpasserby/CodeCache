#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct matrixTerm
{
    int col;
    int row;
    T value;
};

template <typename T>
class sparseMatrix
{
public:
    void transpose();
    void add();
    void multiply();
    void output(ostream &out) const;
    void input(istream &in);

protected:
    int cols;
    int rows;
    vector<matrixTerm<T>> terms;
};

template <typename T>
void sparseMatrix<T>::transpose()
{
    vector<matrixTerm<T>> cpyMatrix(terms);
    matrixTerm<T> tmp;

    int *colSize = new int[cols + 1]{};
    int *rowNext = new int[cols + 1]{};

    for (typename ::vector<matrixTerm<T>>::iterator it = terms.begin(); it != terms.end(); ++it)
        colSize[it->col]++;
    for (int i = 2; i <= cols; i++)
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];

    for (typename ::vector<matrixTerm<T>>::iterator it = cpyMatrix.begin(); it != cpyMatrix.end(); ++it)
    {
        tmp.row = it->col;
        tmp.col = it->row;
        tmp.value = it->value;
        terms[rowNext[it->col]++] = tmp;
    }

    delete []colSize;
    delete []rowNext;
    swap(rows, cols);
}

template <typename T>
void sparseMatrix<T>::add()
{
    int m, n, t;
    cin >> m >> n >> t;
    if (m != rows || n != cols)
    {
        rows = m;
        cols = n;
        terms.clear();

        matrixTerm<T> tmp;
        for (; t > 0; t--)
        {
            cin >> tmp.row >> tmp.col >> tmp.value;
            terms.push_back(tmp);
        }

        // 题目需求
        cout << -1 << endl;
    }
    else
    {
        matrixTerm<T> tmp;
        typename ::vector<matrixTerm<T>>::iterator it = terms.begin();

        for (; t > 0; t--)
        {
            cin >> tmp.row >> tmp.col >> tmp.value;
            for (; it != terms.end() && tmp.row * cols + tmp.col > it->row * cols + it->col; ++it)
                ;

            if (tmp.row == it->row && tmp.col == it->col && (it->value + tmp.value) != 0)
                it->value += tmp.value;
            else if (tmp.row == it->row && tmp.col == it->col)
                it = terms.erase(it);
            else if (it != terms.end())
                it = terms.insert(it, tmp);
            else
                terms.push_back(tmp);
        }
    }
}

template <typename T>
void sparseMatrix<T>::multiply()
{
    int m, n, t;
    cin >> m >> n >> t;
    if (m != cols)
    {
        rows = m;
        cols = n;
        terms.clear();

        matrixTerm<T> tmp;
        for (; t > 0; t--)
        {
            cin >> tmp.row >> tmp.col >> tmp.value;
            terms.push_back(tmp);
        }

        // 题目需求
        cout << -1 << endl;
    }
    else
    {
        sparseMatrix<T> factorMatrix;
        vector<matrixTerm<T>> cpyTerms(terms);
        matrixTerm<T> tmp;
        factorMatrix.rows = m;
        cols = factorMatrix.cols = n;

        for (; t > 0; t--)
        {
            cin >> tmp.row >> tmp.col >> tmp.value;
            factorMatrix.terms.push_back(tmp);
        }

        factorMatrix.transpose();
        terms.clear();

        vector<T> colVal(m + 1, 0);
        vector<T> rowVal(m + 1, 0);
        for (typename ::vector<matrixTerm<T>>::iterator it = factorMatrix.terms.begin(); it != factorMatrix.terms.end(); ++it)
        {
            colVal[it->col] = it->value;
            if (it->row != (it + 1)->row)
            {
                for (typename ::vector<matrixTerm<T>>::iterator jt = cpyTerms.begin(); jt != cpyTerms.end(); ++jt)
                {
                    rowVal[jt->col] = jt->value;
                    if (jt->row != (jt + 1)->row)
                    {
                        tmp.row = it->row;
                        tmp.col = jt->row;
                        tmp.value = 0;
                        for (int k = 1; k <= m; k++)
                            if (colVal[k] && rowVal[k])
                                tmp.value += colVal[k] * rowVal[k];
                        if (tmp.value)
                            terms.push_back(tmp);

                        for (int x = 1; x <= m; x++)
                            rowVal[x] = 0;
                    }
                }
                for (int x = 1; x <= m; x++)
                    colVal[x] = 0;
            }
        }
        swap(rows, cols);
        this->transpose();
    }
}

template <typename T>
void sparseMatrix<T>::output(ostream &out) const
{
    out << rows << " " << cols << endl;

    int i = 1, j = 1;
    typename ::vector<matrixTerm<T>>::const_iterator it = terms.begin();

    for (; it != terms.end(); ++it)
    {
        for (; i < it->row; i++)
        {
            for (; j <= cols; j++)
                out << 0 << ' ';
            out << endl;
            j = 1;
        }

        for (; j < it->col; j++)
            out << 0 << ' ';

        out << it->value << ' ';
        j++;
    }

    for (; i <= rows; i++)
    {
        for (; j <= cols; j++)
            out << 0 << ' ';
        out << endl;
        j = 1;
    }
}

template <typename T>
ostream &operator<<(ostream &out, const sparseMatrix<T> &x)
{
    x.output(out);
    return out;
}

template <typename T>
void sparseMatrix<T>::input(istream &in)
{
    int m, n;
    matrixTerm<T> theTerm;
    T val;

    in >> m >> n;
    rows = m;
    cols = n;

    terms.clear();
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            in >> val;
            if (val != 0)
            {
                theTerm.row = i;
                theTerm.col = j;
                theTerm.value = val;
                terms.push_back(theTerm);
            }
        }
    }
}

template <typename T>
istream &operator>>(istream &in, sparseMatrix<T> &x)
{
    x.input(in);
    return in;
}

int main()
{
    int w, opNum;
    sparseMatrix<int> test;
    cin >> w;
    for (int i = 0; i < w; i++)
    {
        cin >> opNum;
        switch (opNum)
        {
        case 1:
            cin >> test;
            break;

        case 2:
            test.multiply();
            break;

        case 3:
            test.add();
            break;

        case 4:
            cout << test;
            break;

        case 5:
            test.transpose();
            break;

        default:
            break;
        }
    }
    return 0;
}