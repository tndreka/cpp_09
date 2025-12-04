/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:03:06 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/04 15:14:45 by tndreka          ###   ########.fr       */
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
    //std::vector<std::pair<int, int>> pairs;
    _pairs.clear();
    _pairs.reserve(n/2);
    for (size_t i = 0; i + 1< n; i+= 2)
    {
        if(v[i] < v[i+1])
            _pairs.emplace_back(v[i], v[i+1]);
        else
            _pairs.emplace_back(v[i+1], v[i]);
    }
    //handle odd element
    _has_odd = (n & 1);
    _oddElem = 0;
    if (_oddElem)
        _oddElem = v.back();
    _main.clear();
    _main.reserve(_pairs.size());
    for (size_t i = 0; i < _pairs.size(); ++i)
    {
        _main.push_back(_pairs[i].second);
    }
    fordJohnsonVector(_main);
    _res.clear();
    _res.reserve(n);
    _res.push_back(_pairs[0].first);
    _res.insert(std::lower_bound(_res.begin(), _res.end(), _main[0]), _main[0]);
    //insert remaining batch
    _index = 1;
    _js = 1;    
    while (_index < _pairs.size())
    {
        dist = jacobsthal(_js + 1) - jacobsthal(_js);
        last = _index + dist;
        if (last > _pairs.size())
            last = _pairs.size();
        for(size_t j = last; j-- > _index;)
        {
            val = _pairs[j].first;
            _res.insert(std::lower_bound(_res.begin(), _res.end(), val), val);
        }
        _index = last;
        ++_js;
    }
    //append the rest
    for (size_t i = 1; i < _main.size(); ++i)
    {
         _res.insert(std::lower_bound(_res.begin(), _res.end(), _main[i]), _main[i]);
    }
    if(has)
         _res.insert(std::lower_bound(_res.begin(), _res.end(), _oddElem), _oddElem);
    v.swap(_res);
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
    std::cout << "same code commented out \n";
    (void)v;
    // const size_t n = v.size();
    // if (n <= 1)
    //     return;
    // //pair compare
    // //std::vector<std::pair<int, int>> pairs;
    // d_pairs.clear();
    // d_pairs.reserve(n/2);
    // for (size_t i = 0; i + 1< n; i+= 2)
    // {
    //     if(v[i] < v[i+1])
    //         d_pairs.emplace_back(v[i], v[i+1]);
    //     else
    //         d_pairs.emplace_back(v[i+1], v[i]);
    // }
    // //handle odd element
    // d_has_odd = (n & 1);
    // d_oddElem = 0;
    // if (d_oddElem)
    //     d_oddElem = v.back();
    // d_main.clear();
    // d_main.reserve(_pairs.size());
    // for (size_t i = 0; i < d_pairs.size(); ++i)
    // {
    //     d_main.push_back(d_pairs[i].second);
    // }
    // fordJohnsonVector(d_main);
    // d_res.clear();
    // d_res.reserve(n);
    // d_res.push_back(_pairs[0].first);
    // d_res.insert(std::lower_bound(d_res.begin(),d_res.end(), d_main[0]), d_main[0]);
    // //insert remaining batch
    // d_index = 1;
    // d_js = 1;    
    // while (d_index < d_pairs.size())
    // {
    //     _dist = jacobsthal(d_js + 1) - jacobsthal(d_js);
    //     _last = d_index + _dist;
    //     if (_last > d_pairs.size())
    //         _last = d_pairs.size();
    //     for(size_t j = last; j-- > _index;)
    //     {
    //         val = _pairs[j].first;
    //         _res.insert(std::lower_bound(_res.begin(), _res.end(), val), val);
    //     }
    //     _index = last;
    //     ++_js;
    // }
    // //append the rest
    // for (size_t i = 1; i < _main.size(); ++i)
    // {
    //      _res.insert(std::lower_bound(_res.begin(), _res.end(), _main[i]), _main[i]);
    // }
    // if(_oddElem)
    //      _res.insert(std::lower_bound(_res.begin(), _res.end(), _oddElem), _oddElem);
    // v.swap(_res);
}
