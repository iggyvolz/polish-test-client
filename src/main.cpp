#include "PolishClient.hpp"
int main()
{
    PolishClient client("127.0.0.1", 53000);
    client.Run();
    return 0;
}