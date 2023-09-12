#include <iostream>

#include "Client.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: client <host> <port>\n";
        return 1;
    }
    Client c(argv[1], argv[2]);
    c.run();
    return 0;
}