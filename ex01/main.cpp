/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 22:18:14 by tndreka           #+#    #+#             */
/*   Updated: 2025/12/02 14:58:42 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(int ac, char *av[])
{
    if(ac != 2)
    {
        std::cerr << "Error\n";
        return 1;
    }
    try
    {}
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }   
    return 0;
}