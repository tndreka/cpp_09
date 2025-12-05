#include "BitcoinExchange.hpp"

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

bool BitcoinExchange::isValidRate(const std::string& rate)
{
    bool dot = false;
    size_t i = 0;
    
    if (rate.empty())
        return false;
    
    if(rate[0] == '-' || rate[0] == '+')
        i = 1;
    for (size_t j = i; j < rate.length(); j++)
    {
        if (rate[j] == '.')
        {
            if (dot)
                return false;
            dot = true;
        }
        else if (!isdigit(rate[j]))
            return false;
    }
    try
    {
        float value = std::stof(rate.c_str());
        if (value < 0.0f)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            return false;
        }
        if (value > 1000.f)
        {
            std::cerr << "Error: too large a number." << std::endl;
            return false;
        }
        
        _rate = value;
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: invalid rate value\n";
        return false;
    }
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
    //bad format
    if(date.length() != 10 || date[4] != '-' || date[7] != '-')
    {
        std::cerr << "Error: bad input => " << date << std::endl;
        return false;
    }
    _year = date.substr(0, 4);
    _month = date.substr(5, 2);
    _day = date.substr(8, 2);

    for (size_t i = 0; i < _year.length(); i++)
    {
        if (!isdigit(_year[i]))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            return false;
        }
    }
    for (size_t i = 0; i < _month.length(); i++)
    {
        if (!isdigit(_month[i]))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            return false;
        }
    }
    for (size_t i = 0; i < _day.length(); i++)
    {
        if (!isdigit(_day[i]))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            return false;
        }
    }
    int year = atoi(_year.c_str());
    int month = atoi(_month.c_str());
    int day = atoi(_day.c_str());
    if (month < 1 || month > 12 || day < 1 || day > 31)
    {
        std::cerr << "Error: bad input =>  " << date << std::endl;
        return false;
    }
    if(month == 2 && day > 29)
    {
        std::cerr << "Error: bad input =>  " << date << std::endl;
        return false;
    }
    if(month == 2 && day == 29 && year % 4 != 0)
    {
       std::cerr << "Error: bad input =>  " << date << std::endl;
        return false; 
    }

    return true;
}

float BitcoinExchange::findClosestRate(const std::string& date) const
{
    std::map<std::string, float>::const_iterator it = _db.lower_bound(date);

    if(it != _db.end() && it->first == date)
        return it->second;
    if (it == _db.begin())
    {
        std::cerr << "Error: date is before database range\n";
        return -1;
    }
    --it;
    return it->second;
}