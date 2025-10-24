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

bool BitcoinExchange::parseInputFile(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open the file." << std::endl;
        return false;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        _isvalid = true;
        if(line.empty())
            continue;
        size_t separator = line.find('|');
        std::string date = trim(line.substr(0, separator));
        if(!isValidDate(date))
        {
            std::cerr << "Error: bad input =>  " << date << std::endl;
            _isvalid = false;
            continue;
        }
    }
    file.close();
    
    return true;
}

bool BitcoinExchange::load_data(const std::string& database)
{
    std::ifstream file(database.c_str());
    if (!file.is_open()) 
    {
        std::cerr << "Error: database not loaded\n";
        return false;
    }
    //std::cout << "database opened successfully\n";
    std::string line;
    std::getline(file, line); // Skip header line

    while (std::getline(file, line))
    {
        _isvalid = true;
        if(line.empty())
            _isvalid = false;
        size_t sep = line.find(',');
        if(sep == std::string::npos)
        {
            std::cerr << "Error: not a valid line on database\n";
            _isvalid = false;
        }
        if (_isvalid)
        {
            std::string date = trim(line.substr(0, sep));
            std::string rate = trim(line.substr(sep + 1));
            _fulldate = date;
            if (!isValidDate(_fulldate))
            {
                _isvalid = false;
                std::cerr << "Bad date format\n";
            }
            if (_isvalid && !isValidRate(rate))
            {
                _isvalid = false;
                std::cerr << "Bad rate format\n";
            }
            if (_isvalid)
                _db[_fulldate] = _rate;
        }
    }
    file.close();
    return true;
}




// void BitcoinExchange::printDatabase() const
// {
//     for (std::map<std::string, float>::const_iterator it = _db.begin(); it != _db.end(); ++it)
//     {
//         std::cout << "Date: " << it->first << " Rate: " << it->second << std::endl;
//     }
// }