# pragma once

#include <map>
#include <string>
#include <iostream>
#include <fstream>


class BitcoinExchange
{
private:
    std::map<std::string, float> _db;
    bool _isvalid;
    std::string _month;
    std::string _year;
    std::string _day;
    std::string _fulldate;
    float _rate;
    bool isValidDate(const std::string& date);
    bool isValidRate(const std::string& rate);
    std::string trim(const std::string& line);
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    bool parseInputFile(const std::string& filename);
    bool load_data(const std::string& database);
    //void printDatabase() const;
};

