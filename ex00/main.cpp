#include "BitcoinExchange.hpp"

int main(int ac, char** av)
{
    (void)av;
    if (ac != 2)
    {
        std::cerr << "Errpr: could not open file" << std::endl;
        return 1;
    }
    else
    {
        BitcoinExchange btcExchange;
        if (btcExchange.load_data("data.csv") == false)
            return 1;
        //btcExchange.parseInputFile(av[1]); // to implement
    }
    return 0;
}