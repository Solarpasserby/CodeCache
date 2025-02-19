#include <iostream>
using namespace std;

void strcpy(char *p, const char *q)
{
    while (*q)
    {
        *p = *q;
        q++;
        p++;
    }
    *p = '\0';
}

bool strcmp(const char *p, const char *q)
{
    while (*p || *q)
    {
        if (*p != *q)
            return false;
        p++;
        q++;
    }
    return true;
}

int min(int a, int b)
{
    if (a > b)
        return b;
    else
        return a;
}

template <class T>
void changeArrayLength(T *&oldArray, int oldLength, int newLength)
{
    T *temp = new T[newLength];
    int cpyLength = min(oldLength, newLength);
    for (int i = 0; i < cpyLength; i++)
        temp[i] = oldArray[i];
    delete[] oldArray;
    oldArray = temp;
}

class student
{
public:
    student(char *name, char *phoneNum, int classNum, int dormNum);
    student(const student &theStudent);

    char name[20];
    char phoneNum[12];
    int classNum;
    int dormNum;
};

student::student(char *inputName, char *inputPhoneNum, int inputClassNum, int inputDormNum)
{
    strcpy(name, inputName);
    strcpy(phoneNum, inputPhoneNum);
    classNum = inputClassNum;
    dormNum = inputDormNum;
}

student::student(const student &theStudent)
{
    strcpy(name, theStudent.name);
    strcpy(phoneNum, theStudent.phoneNum);
    classNum = theStudent.classNum;
    dormNum = theStudent.dormNum;
}

template <class T>
class arrayList
{
public:
    arrayList(int initialCapacity = 8);
    arrayList(const arrayList<T> &);
    ~arrayList() { delete[] element; }

    void input();
    void insert();
    void erase();
    void update();
    void search();
    void uniqueOutput();

    int checkName(char *inputName);

protected:
    T *element;
    int arrayLength;
    int listSize;
};

template <class T>
arrayList<T>::arrayList(int initialCapacity)
{
    if (initialCapacity < 1)
        throw "initialCapacity should be > 0!";
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T> &theList)
{
    arrayLength = theList.arrayLength;
    element = new T[arrayLength];
    listSize = theList.listSize;
    for (int i = 0; i < arrayLength; i++)
        element[i] = theList.element[i];
}

template <class T>
void arrayList<T>::input()
{
    int operateNum;
    cin >> operateNum;
    switch (operateNum)
    {
    case 0:
        insert();
        break;

    case 1:
        erase();
        break;

    case 2:
        update();
        break;

    case 3:
        search();
        break;
        
    case 4:
        uniqueOutput();
        break;
    
    default:
        throw "operation must in (0, 1, 2, 3, 4)!";
        break;
    }
}

template <class T>
void arrayList<T>::insert()
{
    char name[20], phoneNum[12];
    int classNum, dormNum;
    cin >> name >> phoneNum >> classNum >> dormNum;
    student *theStudent = new student(name, phoneNum, classNum, dormNum);

    if (listSize == arrayLength)
    {
        changeArrayLength(element, arrayLength, arrayLength * 2);
        arrayLength *= 2;
    }

    element[listSize++] = theStudent;
}

template <class T>
void arrayList<T>::erase()
{
    char name[20];
    cin >> name;

    int eraseIndex = checkName(name);
    if (eraseIndex == -1)
        throw "the name isn't exist!";
    else
    {
        delete element[eraseIndex];
        for (int i = eraseIndex; i < listSize - 1; i++)
            element[i] = element[i + 1];
        listSize--;
    }
}

template <class T>
void arrayList<T>::update()
{
    char name[20];
    cin >> name;

    int updateIndex = checkName(name);
    if (updateIndex == -1)
        throw "the name isn't exist!";
    else
    {
        int item;
        cin >> item;
        if (item == 1)
            cin >> element[updateIndex]->phoneNum;
        else if (item == 2)
            cin >> element[updateIndex]->classNum;
        else if (item == 3)
            cin >> element[updateIndex]->dormNum;
        else
            throw "item must in (1, 2, 3)!";
    }
}

template <class T>
void arrayList<T>::uniqueOutput()
{
    int classNum, res = 0;
    cin >> classNum;

    for (int i = 0; i < listSize; i++)
        if (element[i]->classNum == classNum)
            res ^= element[i]->dormNum;

    cout << res << endl;
}

template <class T>
void arrayList<T>::search()
{
    char name[20];
    cin >> name;

    int isExist = checkName(name) == -1 ? 0 : 1;
    cout << isExist << endl;
}

template <class T>
int arrayList<T>::checkName(char *inputName)
{
    int i = 0;
    for (; i < listSize; i++)
        if (strcmp(element[i]->name, inputName))
            return i;
    return -1;
}

int main()
{
    int n;
    cin >> n;
    arrayList<student *> lst(8);
    for (; n > 0; n--)
        lst.input();
    return 0;
}