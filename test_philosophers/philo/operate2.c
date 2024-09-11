/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:50:38 by yeham             #+#    #+#             */
/*   Updated: 2023/03/02 19:47:18 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_info *philo)
{
	int	index;

	index = 0;
	while (index < 2)
	{
		if (check_stop_flag(philo))
			return (0);
		if (index == 0)
		{
			if (philo->id & 1)
				get_fork(philo, philo->left_fork);
			else
				get_fork(philo, philo->right_fork);
		}
		else if (index == 1)
		{
			if (philo->id & 1)
				get_fork(philo, philo->right_fork);
			else
				get_fork(philo, philo->left_fork);
		}
		index++;
	}
	return (1);
}

int	eating(t_info *philo)
{
	int	result;

	result = 1;
	if (check_stop_flag(philo))
	{
		pthread_mutex_unlock(&philo->link_table->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->link_table->fork[philo->right_fork]);
		return (0);
	}
	mutex_printf("is eating", philo, 1);
	pthread_mutex_lock(&philo->link_table->last_ate);
	philo->last_eat = get_time(0);
	philo->eat_count++;
	if (philo->eat_count == philo->link_table->must_eat)
		result = 0;
	pthread_mutex_unlock(&philo->link_table->last_ate);
	msleep(philo->link_table->time_to_eat);
	pthread_mutex_unlock(&philo->link_table->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->link_table->fork[philo->right_fork]);
	return (result);
}

int	sleeping(t_info *philo)
{
	if (check_stop_flag(philo))
		return (0);
	mutex_printf("is sleeping", philo, 4);
	msleep(philo->link_table->time_to_sleep);
	return (1);
}

int	thinking(t_info *philo)
{
	if (check_stop_flag(philo))
		return (0);
	mutex_printf("is thinking", philo, 8);
	usleep(500);
	return (1);
}

int	ft_operate(t_info *philo)
{
	if (take_fork(philo))
		if (eating(philo))
			if (sleeping(philo))
				if (thinking(philo))
					return (1);
	return (0);
}
