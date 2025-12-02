/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:20:04 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/02 15:27:34 by tndreka          ###   ########.fr       */
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
    std::istringstream iss(token);
    double val;
    char c;
    
    if (!(iss >> val))
        return false;
    if (iss >> c)
        return false;
    return true;
}

double RPN::strToDouble(const std::string &token) const
{
    std::istringstream iss(token);
    double val;
    iss >> val;
    if (iss.fail())
        throw std::runtime_error("Error: runtime error\"" + token + "\"");
    return val; 
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