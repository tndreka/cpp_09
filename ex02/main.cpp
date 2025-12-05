/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:18:14 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/05 16:47:38 by tndreka          ###   ########.fr       */
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
        if(PmergeMe::isValidInput(av) != 0)
        {
            std::cerr << "Error : Usage ./PmergeMe <positive integer sequence>\n";
            return 1;
        }
        PmergeMe::parse_and_sort(ac, av);  
    }
    return 0;
}