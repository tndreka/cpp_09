/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:02:52 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/05 14:06:55 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMEREGEME_HPP
#define PMEREGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sys/time.h>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include <cctype>

class PmergeMe
{
private:
    double              _timer;
    //vector
    std::vector<int>    _vector;
    //deque
    std::deque<int>     _deque;
    void                start_time();
    double              measure_time() const;
    void                fordJohnsonVector(std::vector<int>& v);
    void                fordJohnsonDeque(std::deque<int>& d);
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();
    static int                 isValidInput(char *av[]);
    template<typename T>
    static void                  print_stack_(T& container)
    {
        for (size_t i = 0; i < container.size(); ++i)
        {
            std::cout << container[i] << " ";
        }
        std::cout<< "\n";
    }
    int                 isDup_vec() const;
    void sortVector(std::vector<int>& input);
    void sortDeque(std::deque<int>& input);
    const std::vector <int>& getVector() const;
    const std::deque <int>& getDeque() const;
    static void parse_and_sort(int ac, char* av[]);
};


#endif