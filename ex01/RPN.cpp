/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:20:04 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/02 14:46:58 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RPN.hpp"

RPN::RPN(){}

RPN::RPN(const RPN& other){}

RPN& RPN::operator=(const RPN& other)
{
    if(this != &other)
        return *this;
    return *this;    
}

RPN::~RPN(){}


static bool isFloatToken(const std::string &s)
{
    std::istringstream iss(s);
    double tmp;
    return (iss >> tmp) && (iss.eof());
}

bool RPN::isNum(const std::string &token) const
{
    
}
