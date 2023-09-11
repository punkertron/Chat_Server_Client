#include <iostream>

#include "Client.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: lient  <port>\n";
        return 1;
    }
    Client c(argv[1]);
    return 0;
}