/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:02:52 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/03 18:55:09 by tndreka          ###   ########.fr       */
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
    double              _timer;
    //vector
    std::vector<int>    _vector;
    std::vector<std::pair<int, int>> _pairs;
    std::vector<int>    _main;
    std::vector<int>    _res;
    int                 _oddElem;
    bool                _has_odd;
    size_t              _index;
    int                 _js;
    int                 dist;
    size_t              last;
    int                 val;
    //deque
    std::deque<int>     _deque;
    std::deque<std::pair<int, int>> d_pairs;
    std::deque<int>    d_main;
    std::deque<int>    d_res;
    int                d_oddElem;
    bool               d_has_odd;
    size_t             d_index;
    int                d_js;
    int                 _dist;
    size_t              _last;
    int                 _val;
    void                start_time();
    double              measure_time() const;
    void                fordJohnsonVector(std::vector<int>& v);
    void                fordJohnsonDeque(std::deque<int>& v);
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
};


#endif