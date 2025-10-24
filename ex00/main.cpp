#include "BitcoinExchange.hpp"

int main(int ac, char** av)
{
    if (ac != 2)
    {
        std::cerr << "Error: invalid arguments" << std::endl;
        return 1;
    }
    else
    {
        BitcoinExchange btcExchange;
        if (btcExchange.load_data("data.csv") == false)
            return 1;
        if (btcExchange.parseInputFile(av[1]) == false)
            return 1;
    }
    return 0;
}