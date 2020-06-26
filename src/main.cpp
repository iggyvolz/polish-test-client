#include "PolishClient.hpp"
int main()
{
    PolishClient client("/tmp/sock");
    client.Run();
    return 0;
}