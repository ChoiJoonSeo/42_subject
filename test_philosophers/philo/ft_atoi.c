/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:58:09 by yeham             #+#    #+#             */
/*   Updated: 2023/02/23 16:22:54 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	num_error(unsigned long long int num, int buho, int c)
{
	if (num > 922337203685477580)
	{
		if (buho == -1)
			return (0);
		else
			return (-1);
	}
	if (buho == -1 && num == 922337203685477580 && c > 8)
		return (0);
	if (buho == 1 && num == 922337203685477580 && c > 7)
		return (-1);
	return (1);
}

int	ft_atoi(const char *str)
{
	int						buho;
	int						i;
	unsigned long long int	num;

	num = 0;
	buho = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
	if (str[i] == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
	{	
		buho *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num_error(num, buho, (str[i] - '0')) != 1)
			return (num_error(num, buho, (str[i] - '0')));
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * buho);
}

int	num_error(unsigned long long int num, int buho, int c)
{
	if (num > 922337203685477580)
	{
		if (buho == -1)
			return (0);
		else
			return (-1);
	}
	if (buho == -1 && num == 922337203685477580 && c > 8)
		return (0);
	if (buho == 1 && num == 922337203685477580 && c > 7)
		return (-1);
	return (1);
}

int	ft_atoi(const char *str)
{
	int						buho;
	int						i;
	unsigned long long int	num;

	num = 0;
	buho = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
	if (str[i] == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
	{	
		buho *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num_error(num, buho, (str[i] - '0')) != 1)
			return (num_error(num, buho, (str[i] - '0')));
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * buho);
}
