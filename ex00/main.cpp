#include "BitcoinExchange.hpp"

int main(int ac, char** av)
{
    BitcoinExchange btcExchange;
    if (ac != 2)
    {
        std::cerr << "Usage: " << av[0] << " <input_file>" << std::endl;
        return 1;
    }
    else
    {
        // Future implementation will go here
    }
    
    return 0;
}