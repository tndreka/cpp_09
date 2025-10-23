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
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void parseInputFile(const std::string& filename);
    void load_data(const std::string& database);
};

