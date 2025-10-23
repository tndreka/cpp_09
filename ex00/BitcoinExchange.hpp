# pragma once

#include <map>
#include <string>
#include <iostream>


class BitcoinExchange
{
private:
    std::map<std::string, float> _db;
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void parseInputFile(const std::string& filename);
};

