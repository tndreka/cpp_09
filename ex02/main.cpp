/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:18:14 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/03 16:37:51 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char* av[])
{
    if (ac < 2)
    {
        std::cerr << "Error : Usage ./PmergeMe <positive integer sequence>\n";
        return 1;
    }
    else
    {
        std::cout << "Start Sorting\n";
        if(PmergeMe::isValidInput(av) != 0)
        {
            std::cerr << "Error : Usage ./PmergeMe <positive integer sequence\n>";
            return 1;
        }
        std::vector<int> input;
        for (int i = 1; i < ac; ++i)
        {
            input.push_back(std::atoi(av[i]));
        }
        std::cout << "Before: ";
        PmergeMe::print_stack_(input);
        PmergeMe lets_sort;
        //here sort on vector
         // --> mergesort algo
        lets_sort.sortVector(input);
        //here sort on deque
        const std::vector<int>& sorted_vec = lets_sort.getVector();
        std::cout << "After: ";
        PmergeMe::print_stack_(sorted_vec);
    }
    return 0;
}