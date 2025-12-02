/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:18:14 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/02 15:23:32 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char *av[])
{
    if(ac != 2)
    {
        std::cerr << "Error\n";
        return 1;
    }
    try
    {
        RPN calculator;
        double res = calculator.evaluate(av[1]);
        std::cout << res << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }   
    return 0;
}