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

bool BitcoinExchange::load_data(const std::string& database)
{
    std::ifstream file(database.c_str());
    if (!file.is_open()) 
    {
        std::cerr << "Error: database not loaded\n";
        return false;
    }
    std::cout << "database opened successfully\n";
    std::string line;
    std::getline(file, line); // Skip header line

    while (std::getline(file, line))
    {
        _isvalid = true;
        size_t sep = line.find(',');
        if(sep == std::string::npos)
        {
            std::cerr << "Error: not a valid line on database\n";
            _isvalid = false;
        }
        if (_isvalid)
        {
            std::string date = trim(line.substr(0, sep));
            _fulldate = date;
            if (!isValidDate(_fulldate))
            {
                _isvalid = false;
                std::cerr << "Bad date format\n";
            }
            else 
                std::cout << "full date: " << _fulldate << std::endl;
        }
    }
    file.close();
    return true;
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
    //bad format
    if(date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    _year = date.substr(0, 4);
    _month = date.substr(5, 2);
    _day = date.substr(8, 2);

    for (size_t i = 0; i < _year.length(); i++)
    {
        if (!isdigit(_year[i]))
        {
            std::cout << "year error\n";
            return false;
        }
    } 
    return true;
}

std::string BitcoinExchange::trim(const std::string& line)
{
    size_t start = 0;
    size_t end = line.length();
    while (start < end && isspace(static_cast<unsigned char>(line[start])))
        start++;
    while (end > start && isspace(static_cast<unsigned char>(line[end - 1])))
        end--;
    return line.substr(start, end - start);
}