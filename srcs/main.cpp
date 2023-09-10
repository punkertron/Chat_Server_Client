#include <iostream>

#include "Server.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./server <port>\n";
        return 1;
    }

    Server s(argv[1]);
    s.run();

    return 0;
}
