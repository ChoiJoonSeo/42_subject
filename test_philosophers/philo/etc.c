/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:55:46 by yeham             #+#    #+#             */
/*   Updated: 2023/02/28 13:51:28 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop_flag(t_info *philo)
{
	pthread_mutex_lock(&philo->link_table->print);
	if (philo->link_table->stop_flag == 1)
	{
		pthread_mutex_unlock(&philo->link_table->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->link_table->print);
	return (0);
}

void	get_fork(t_info *philo, int fork)
{
	pthread_mutex_lock(&philo->link_table->fork[fork]);
	mutex_printf("has taken a fork", philo, 2);
}

void	mutex_printf(char *string, t_info *philo, int color)
{
	if (check_stop_flag(philo))
		return ;
	pthread_mutex_lock(&philo->link_table->print);
	printf("%ld %d \033[0;3%dm%s\033[0m\n", get_time \
		(philo->link_table->time), philo->id, color, string);
	pthread_mutex_unlock(&philo->link_table->print);
}
