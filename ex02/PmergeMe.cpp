/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:03:06 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/05 14:08:41 by tndreka          ###   ########.fr       */
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

void PmergeMe::parse_and_sort(int ac, char* av[])
{
        std::vector<int> vec_input;
        for (int i = 1; i < ac; ++i)
        {
            vec_input.push_back(std::atoi(av[i]));
        }
        
        std::deque<int> deq_input;
        for (int i = 1; i < ac; ++i)
        {
            deq_input.push_back(std::atoi(av[i]));
        }
        
        std::cout << "Before: ";
        PmergeMe::print_stack_(vec_input);
        
        PmergeMe lets_sort;
        lets_sort.sortVector(vec_input);
        
        //here sort on deque
        lets_sort.sortDeque(deq_input);
        
        std::cout << "After: ";
        PmergeMe::print_stack_(lets_sort.getVector());
        std::cout << "After: ";
        PmergeMe::print_stack_(lets_sort.getDeque());
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
    /*
        PAIR CREATION
        smaller value first , larger second;
    */
    std::vector<std::pair<int, int> > pairs;
    pairs.reserve(n/2);
    for (size_t i = 0; i +1 < n; i += 2)
    {
        if(v[i] < v[i + 1])
            pairs.push_back(std::make_pair(v[i], v[i + 1]));
        else
            pairs.push_back(std::make_pair(v[i + 1], v[i]));
    }
    /* handle ODD*/
    bool has_odd = (n & 1);
    int  odd = 0;
    if(has_odd)
        odd = v.back();
    if(pairs.size() > 1)
    {
        std::vector<int>    main;
        main.reserve(pairs.size());
        for (size_t i = 0; i < pairs.size(); ++i)
        {
            main.push_back(pairs[i].second);
        }
        fordJohnsonVector(main);
        std::vector<std::pair<int, int>> sorted_pairs;
        sorted_pairs.reserve(pairs.size());
        for (size_t i = 0; i < main.size(); ++i)
        {
            for (size_t j = 0; i < pairs.size(); ++j)
            {
                if (pairs[j].second == main[i])
                {
                    sorted_pairs.push_back(pairs[j]);
                    pairs[j].second = -1;
                    break;   
                }
            }
        }
        pairs = sorted_pairs;
    }    
    std::vector<int>    res;
    res.reserve(n);
    
    if(!pairs.empty())
        res.push_back(pairs[0].first);
    
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        res.push_back(pairs[i].second);
    }
    if(pairs.size() > 1)
    {
        std::vector<int> pend;
        for (size_t i = 1; i < pairs.size(); ++i)
        {
            pend.push_back(pairs[i].first);
        }
        std::vector<size_t> jacob_indices;
        size_t pos = 0;
        int k = 3;
        while (pos < pend.size())
        {
            size_t j_idx = static_cast<size_t>(jacobsthal(k));
            if(j_idx > pend.size())
                j_idx = pend.size();
            for (size_t i = j_idx; i > pos; --i)
            {
                jacob_indices.push_back(i -1);
            }
            pos = j_idx;
            ++k;
        }
        for (size_t i = 0; i < jacob_indices.size(); ++i)
        {
            int val = pend[jacob_indices[i]];
            std::vector<int>::iterator it = std::lower_bound(res.begin(), res.end(), val);
            res.insert(it, val);
        }
    }
    if(has_odd)
        res.insert(std::lower_bound(res.begin(), res.end(), odd), odd);
    v.swap(res);
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
    //todo
    const size_t n = d.size();
    if(d.size() <= 1)
        return;
    /* create pairs small and large */
    std::deque<std::pair<int, int> > pairs;
    // pairs.reserve(d / 2);
    for(size_t i = 0; i + 1 < n; i += 2)
        {
        if(d[i] < d[i + 1])
            pairs.push_back(std::make_pair(d[i], d[i + 1]));
        else 
            pairs.push_back(std::make_pair(d[i + 1], d[i]));
    }
    /* to handle odd num*/
    bool hasodd = (n & 1);
    int odd_n = 0;
    if (hasodd)
        odd_n = d.back();
    /*sort  the largest pairs*/
    if (pairs.size() > 1)
    {
        std::deque<int> large_pairs;
        //large_pairs.reserve(pairs.size());
        for(size_t i = 0; i < pairs.size(); ++i)
        {
            large_pairs.push_back(pairs[i].second);
        }
        fordJohnsonDeque(large_pairs);
        std::deque<std::pair<int, int>> sorted_pairs;
        //deque_sorted_pairs.reserve(pairs.size());
        for(size_t i = 0; i < large_pairs.size(); i++)
        {
            for(size_t j = 0; j < pairs.size(); j++)
            {
                if(pairs[j].second == large_pairs[i])
                {
                    sorted_pairs.push_back(pairs[j]);
                    pairs[j].second = -1;
                    break;
                }
            }
        }
        pairs = sorted_pairs;
    }
    std::deque<int> deque_res;
    // deque_res.reserve(s);
    if(!pairs.empty())
        deque_res.push_back(pairs[0].first);
    for(size_t i = 0; i < pairs.size(); ++i)
    {
        deque_res.push_back(pairs[i].second);
    }
    if(pairs.size() > 1)
    {
        std::deque<int> deque_pend;
        for(size_t i = 1 ; i  < pairs.size(); ++i)
        {
            deque_pend.push_back(pairs[i].first);
        }
        std::deque<size_t> deque_jb_indicies;
        size_t deque_pos = 0;;
        int k = 3;
        while(deque_pos < deque_pend.size())
        {
            size_t idx = static_cast<size_t>(jacobsthal(k));
            if(idx > deque_pend.size())
                idx = deque_pend.size();
            for(size_t i = idx; i > deque_pos;  --i)
            {
                deque_jb_indicies.push_back(i - 1);
            }
            deque_pos = idx;
            ++k;
        }
        for(size_t i = 0; i < deque_jb_indicies.size(); ++i)
        {
            int deque_val = deque_pend[deque_jb_indicies[i]];
            std::deque<int>::iterator it1 = std::lower_bound(deque_res.begin(), deque_res.end(), deque_val);
            deque_res.insert(it1, deque_val);
        }
    }
    if(hasodd)
    {
        std::deque<int>::iterator it2 = std::lower_bound(deque_res.begin(), deque_res.end(), odd_n);
        deque_res.insert(it2, odd_n);
    }
    d.swap(deque_res);
}
