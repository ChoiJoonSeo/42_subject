/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:52:13 by yeham             #+#    #+#             */
/*   Updated: 2023/03/02 19:46:04 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	monitoring(t_data *table)
{
	int	i;

	i = table->philo_num;
	while (1)
	{
		if (++i >= table->philo_num)
			i = 0;
		pthread_mutex_lock(&table->last_ate);
		if (get_time(table->link_philo[i]->last_eat) >= table->time_to_die)
		{
			if (table->link_philo[i]->eat_count != table->must_eat)
			{
				pthread_mutex_lock(&table->print);
				table->stop_flag = 1;
				printf("%ld %d died\n", get_time \
					(table->time), table->link_philo[i]->id);
				if (table->philo_num == 1)
					pthread_mutex_unlock(&table->fork[0]);
				pthread_mutex_unlock(&table->print);
			}
			pthread_mutex_unlock(&table->last_ate);
			break ;
		}
		pthread_mutex_unlock(&table->last_ate);
	}
}

void	*routine(void *argument)
{
	t_info	*philo;

	philo = argument;
	if (!(philo->id & 1))
		usleep(1000);
	while (1)
		if (ft_operate(philo) == 0)
			break ;
	return (0);
}
