/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:04:46 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/29 10:11:57 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long long	res;
	int			i;

	i = 0;
	res = 0;
	if (*(str + i) == '-')
		return (-1);
	else if (*(str + i) == '+')
		i++;
	if (ft_strlen(str + i) > 10)
		return (-1);
	while (*(str + i) && *(str + i) >= '0' && *(str + i) <= '9')
		res = res * 10 + *(str + i++) - '0';
	if (*(str + i) != '\0' || res > INT_MAX || res < INT_MIN)
		return (-1);
	return ((int)res);
}
