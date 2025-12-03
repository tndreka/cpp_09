/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:03:06 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/03 18:33:57 by tndreka          ###   ########.fr       */
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

const std::vector<int>& PmergeMe::getVector() const
{
    return _vector;
}

const std::deque<int>& PmergeMe::getDeque() const
{
    return _deque;
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

static int jacobsthal(int n)
{
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    int a = 0, b = 1;
    for (int i = 2; i < n; ++i)
    {
        int next = b + 2 * a;
        a = b;
        b = next;
    }
    return b;
}

void PmergeMe::fordJohnsonVector(std::vector<int>& v)
{
    const size_t n = v.size();
    if (n <= 1)
        return;
    //pair compare
    std::vector<std::pair<int, int>> pairs;
    pairs.reserve(n/2);
    for (size_t i = 0; i + 1< n; i+= 2)
    {
        if(v[i] < v[i+1])
            pairs.emplace_back(v[i], v[i+1]);
        else
            pairs.emplace_back(v[i+1], v[i]);
    }
    //handle odd element
    bool has_odd = (n & 1);
    int odd_elem = 0;
    if (odd_elem)
        odd_elem = v.back();
    std::vector<int> main;
    main.reserve(pairs.size());
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        main.push_back(pairs[i].second);
    }
    fordJohnsonVector(main);
    std::vector<int>res;
    res.reserve(n);
    res.push_back(pairs[0].first);
    res.insert(std::lower_bound(res.begin(), res.end(), main[0]), main[0]);
    //insert remaining batch
    size_t index = 1;
    int    js = 1;    
    while (index < pairs.size())
    {
        int dist = jacobsthal(js + 1) - jacobsthal(js);
        size_t last = index + dist;
        if (last > pairs.size())
            last = pairs.size();
        for(size_t j = last; j-- > index;)
        {
            int val = pairs[j].first;
            res.insert(std::lower_bound(res.begin(), res.end(), val), val);
        }
        index = last;
        ++js;
    }
      
}


void PmergeMe::sortDeque(std::deque<int>& input)
{
    _deque = input;
    start_time();
    fordJohnsonDeque(_deque);
    std::cout << "Time to proccess a range of " << _deque.size() << " elements with std::deque: " << measure_time() << " us\n";
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& v)
{
    std::sort(v.begin(), v.end());
}
