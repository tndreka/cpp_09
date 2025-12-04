/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:03:06 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/04 15:32:34 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _timer(0)
{}

PmergeMe::PmergeMe(const PmergeMe& other) : _vector(other._vector), _deque(other._deque)
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _timer = other._timer;
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

const std::vector<int>& PmergeMe::getVector() const
{
    return _vector;
}

const std::deque<int>& PmergeMe::getDeque() const
{
    return _deque;
}
int PmergeMe::isValidInput(char* av[])
{
    for(int i = 1; av[i]; ++i)
    {
        std::string str(av[i]);
        for(size_t j = 0; j < str.size(); ++j)
        {
            if(!std::isdigit(str[j]))
                return 1;
        }
        long num = std::atoi(av[i]);
        if(num <= 0 || num > 2147483647)
            return 1;
    }
    return 0;
}

int PmergeMe::isDup_vec() const
{
    for (size_t i = 0; i + 1 < _vector.size(); ++i)
    {
        for (size_t j = i + 1; j < _vector.size(); ++j)
        {
            if (_vector[i] == _vector[j])
                return 1;
        }
    }
    return 0;
}


static int jacobsthal(int n)
{
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i)
    {
        int next = b + 2 * a;
        a = b;
        b = next;
    }
    return b;
}

void PmergeMe::sortVector(std::vector<int>& input)
{
    _vector = input;
    if (isDup_vec() == 1)
    {
        std::cerr << "Error: duplicate in vector\n";
        exit(EXIT_FAILURE);
    }
    start_time();
    fordJohnsonVector(_vector);
    std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector: " << measure_time() << " us\n";
}

void PmergeMe::fordJohnsonVector(std::vector<int>& v)
{
    const size_t n = v.size();
    if(v.size() <= 1)
        return;
    /* create pairs small and large */
    std::vector<std::pair<int, int>> pairs;
    pairs.reserve(n/2);
    for(size_t i = 0; i + 1 < n; i += 2)
    {
        if(v[i] < v[i + 1])
            pairs.push_back(std::make_pair(v[i], v[i + 1]));
        else 
            pairs.push_back(std::make_pair(v[i + 1], v[i]));
    }
    /* to handle odd num*/
    bool has_odd = (n & 1);
    int odd = 0;
    if (has_odd)
        odd = v.back();
}   


void PmergeMe::sortDeque(std::deque<int>& input)
{
    _deque = input;
    if (isDup_vec() == 1)
    {
        std::cerr << "Error: duplicate in vector\n";
        exit(EXIT_FAILURE);
    }
    start_time();
    fordJohnsonDeque(_deque);
    std::cout << "Time to proccess a range of " << _deque.size() << " elements with std::deque: " << measure_time() << " us\n";
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& d)
{

}
