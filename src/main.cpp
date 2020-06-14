#include "PolishClient.hpp"
#include <X11/Xlib.h>
void temp();
int main()
{
    // temp();
    XInitThreads();
    PolishClient client("127.0.0.1", 53000);
    client.Run();
    return 0;
}
// #include<string>
// #include<iostream>
// void hexprints(const char* c, int len)
// {
//     for(int i=0;i<len;i++)
//     {
//         printf("%02x", (unsigned int)(unsigned char)(c[i]));
//     }
// }
// void temp()
// {
//     char x[] = {1,2,3};
//     std::string str(x, 3);
//     hexprints(x, 3);
//     std::cout << std::endl;
//     hexprints(std::string({1, 2, 3}).c_str(), 3);
//     std::cout << std::endl;
// }