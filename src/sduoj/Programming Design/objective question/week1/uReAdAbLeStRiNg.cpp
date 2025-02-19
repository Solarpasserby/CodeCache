// #include<cstdio>

// int main()
// {
//     bool ch = true;
//     char c;
//     int l = 0;

//     while((c = getchar()) != '\n')
//     {
//         ++l;
//         if (l % 2 == 1 && c >= 'a' && c <= 'z') continue;
//         else if (l % 2 == 0 && c >= 'A' && c <= 'Z') continue;
//         else ch = false;
//     }

//     if (ch) printf("%s", "Yes\n");
//     else printf("%s", "No\n");

//     return 0;
// }

#include<string>

int main()
{
    std::string s = std::getline();

    return 0;
}