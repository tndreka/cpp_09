/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:18:51 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/02 15:26:15 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <exception>
#include <string>
#include <sstream>
#include <stack>

class RPN
{
private:
    bool isNum(const std::string &token) const;
    double strToDouble(const std::string &token) const;
public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();
    double evaluate (const std::string &expression);
};

#endif