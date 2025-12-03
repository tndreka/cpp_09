/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:02:52 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/03 15:50:59 by tndreka          ###   ########.fr       */
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

class PmergeMe
{
private:
    std::vector<int>    _vector;
    std::deque<int>     _deque;
    double              _timer;
    void                start_time();
    double              measure_time() const;
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();
    static int                 isValidInput(char *av[]);
    template<typename T>
    static void                  print_stack_before(T& container)
    {
        std::cout << "Before: ";
        for (size_t i = 0; i < container.size(); ++i)
        {
            std::cout << container[i] << " ";
        }
        std::cout<< "\n";
    }
};


#endif