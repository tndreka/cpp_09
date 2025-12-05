/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:20:04 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/05 16:39:47 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RPN.hpp"

RPN::RPN(){}

RPN::RPN(const RPN& other){
  (void)other;
}

RPN& RPN::operator=(const RPN& other)
{
    if(this != &other)
        return *this;
    return *this;    
}

RPN::~RPN(){}


bool RPN::isNum(const std::string &token) const
{
    if (token.length() != 1)
        return false;
    if (token[0] >= '0' && token[0] <= '9')
        return true;
    return false;
}

double RPN::strToDouble(const std::string &token) const
{
    return token[0] - '0';
}

double RPN::evaluate(const std::string &expression)
{
    std::istringstream iss(expression);
    std::string token;
    std::stack<double>st;

    while (iss >> token)
    {
        if (isNum(token))
        {
            double v = strToDouble(token);
            st.push(v);
        }
        else if(token == "+" || token == "-" || token == "*" || token == "/")
        {
            if(st.size() < 2)
                throw std::runtime_error("Error: insufficient operand for operator\"" + token + "\"");
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();
            double result;
            if(token == "+")
                result = a + b;
            else if (token == "-")
                result = a - b;
            else if (token == "*")
                result = a * b;
            else
            {
                if(b == 0.0)
                    throw std::runtime_error("Error: devision by 0");
                result = a / b;
            }
            st.push(result);
        }
        else
        {
                throw std::runtime_error("Error: INVALID TOKEN");
        }
    }
    if (st.size() != 1)
            throw std::runtime_error("Error: malformd RPN expression");
    return st.top();
    
}