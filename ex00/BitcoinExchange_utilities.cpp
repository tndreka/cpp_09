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
    if (rate.empty())
        return false;
    for (size_t i = 0; i < rate.length(); i++)
    {
        if (rate[i] == '.')
        {
            if (dot)
                return false;
            dot = true;
        }
        else if (!isdigit(rate[i]))
            return false;
    }
    float value = atof(rate.c_str());
    if (value < 0.0f)
        return false;
    _rate = value;
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
    for (size_t i = 0; i < _month.length(); i++)
    {
        if (!isdigit(_month[i]))
        {
            std::cout << "month error\n";
            return false;
        }
    }
    for (size_t i = 0; i < _day.length(); i++)
    {
        if (!isdigit(_day[i]))
        {
            std::cout << "day error\n";
            return false;
        }
    }
    int month = atoi(_month.c_str());
    int day = atoi(_day.c_str());
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;
    return true;
}
