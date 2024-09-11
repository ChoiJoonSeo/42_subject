/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:04:04 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/18 14:01:24 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static bool	death_checker(t_philos *philo)
{
	long	passed;
	long	t_die;

	pthread_mutex_lock(&philo->philo_m);
	passed = get_current_time() - philo->last_eaten \
		- philo->table->simu_start_time;
	pthread_mutex_unlock(&philo->philo_m);
	t_die = philo->table->t_die;
	if (passed > t_die)
		return (true);
	return (false);
}

static bool	full_checker(t_table *table)
{
	int	res;

	pthread_mutex_lock(&table->table_m);
	res = table->full;
	pthread_mutex_unlock(&table->table_m);
	if (res == table->philos_n)
	{
		pthread_mutex_lock(&table->table_m);
		table->end_simu = true;
		pthread_mutex_unlock(&table->table_m);
		return (true);
	}
	return (false);
}

void	*monitor(void *param)
{
	int		i;
	t_table	*table;

	table = (t_table *)param;
	while (simu_ended(table) == false && full_checker(table) == false)
	{
		i = -1;
		while (++i < table->philos_n && simu_ended(table) == false)
		{
			if (death_checker(table->philos + i))
			{
				pthread_mutex_lock(&table->table_m);
				table->end_simu = true;
				pthread_mutex_unlock(&table->table_m);
				print_status(table->philos + i, DIED);
			}
		}
	}
	return (NULL);
}
