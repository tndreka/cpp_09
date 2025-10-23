#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    _db = other._db;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        _db = other._db;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{}

// void BitcoinExchange::parseInputFile(const std::string& filename)
// {
// }

void BitcoinExchange::load_data(const std::string& database)
{
    std::ifstream file(database.c_str());
    if(file.is_open() == false) 
    {
        std::cerr << "Error: database not loaded\n";
    }
    std::cout << "database opened successfully\n";
    std::string line;
    std::getline(file, line); // Skip header line


}