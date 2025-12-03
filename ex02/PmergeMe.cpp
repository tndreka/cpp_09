/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:03:06 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/03 16:36:16 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe& other) : _vector(other._vector), _deque(other._deque)
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe(){}

void PmergeMe::start_time()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    _timer = t.tv_sec * 1000000 + t.tv_usec;
}

double PmergeMe::measure_time() const
{
    struct timeval t;
    gettimeofday(&t, NULL);
    double now = t.tv_sec * 1000000 + t.tv_usec;
    return now - _timer;
}

int PmergeMe::isValidInput(char* av[])
{
    for(int i = 1; av[i]; ++i)
    {
        std::string str(av[i]);
        for(size_t j = 0; j < str.size(); ++j)
        {
            if(!isdigit(str[j]))
                return 1;
        }
        if(std::atoi(av[i]) <= 0)
            return 1;
    }
    return 0;
}

const std::vector<int>& PmergeMe::getVector() const
{
    return _vector;
}

void PmergeMe::sortVector(std::vector<int>& input)
{
    _vector = input;
    start_time();
    fordJohnsonVector(_vector);
    std::cout << "Time to proccess a range of " << _vector.size() << " elements with std::vector: " << measure_time() << " us\n";
}

void PmergeMe::fordJohnsonVector(std::vector<int>& v)
{
    std::sort(v.begin(), v.end());
}

