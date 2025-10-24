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
        if(!line.empty())
        {
            size_t separator = line.find('|');
            if(separator != std::string::npos)
            {
                std::string date = trim(line.substr(0, separator));
                std::string rate_value = trim(line.substr(separator + 1));
                if(isValidDate(date))
                {
                    if (isValidRate(rate_value))
                    {
                        float exchange_rate = findClosestRate(date);
                        if (exchange_rate >= 0)
                        {
                            float res = _rate * exchange_rate;
                            std::cout << date << " => " << _rate << " = " << res << std::endl;
                        }
                    }
                    
                }
            }
            else
                std::cerr << "Error: bad input => " << line << std::endl;
        }
    }
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
    std::string line;
    std::getline(file, line); // Skip header line

    while (std::getline(file, line))
    {
        if(!line.empty())
        {
            size_t sep = line.find(',');
            if(sep != std::string::npos)
            {
                std::string date = trim(line.substr(0, sep));
                std::string rate = trim(line.substr(sep + 1));
                try
                {
                    float rate_val = std::stof(rate.c_str());
                    _db[date] = rate_val;
                    
                }
                catch(const std::exception& e)
                {
                    std::cerr << "Error: Invalid exchange rate in DB"<< '\n';
                }
            }
            else
            {
                _isvalid = false;
                std::cerr << "Error: invalid line format in DB\n";
            }
        }
    }
    file.close();
    if(_db.empty())
    {
        std::cerr << "Error: DataBase is empty\n";
        return false;
    }
    return true;
}
