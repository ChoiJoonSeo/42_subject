/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:58:21 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/18 14:22:25 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static void	init_philos(t_table *table)
{
	int			i;
	t_philos	*philos;

	i = -1;
	while (++i < table->philos_n)
	{
		philos = table->philos + i;
		philos->tid = i + 1;
		philos->table = table;
		philos->meals_eaten = 0;
		philos->t_eat = table->t_eat;
		philos->t_sleep = table->t_sleep;
		philos->meals_nbr = table->meals_nbr;
		philos->left_fork = table->forks + i;
		if (i == table->philos_n - 1)
			philos->right_fork = table->forks;
		else
			philos->right_fork = table->forks + i + 1;
	}
}

static int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	if (0 != pthread_mutex_init(&table->print_m, NULL))
		return (_error(PTHREAD_MUTEX_INIT));
	if (0 != pthread_mutex_init(&table->table_m, NULL))
		return (_error(PTHREAD_MUTEX_INIT));
	while (++i < table->philos_n)
	{
		if (0 != pthread_mutex_init(&table->philos[i].philo_m, NULL))
			return (_error(PTHREAD_MUTEX_INIT));
		if (0 != pthread_mutex_init(&table->forks[i].fork_m, NULL))
			return (_error(PTHREAD_MUTEX_INIT));
	}
	return (0);
}

int	fill_table(t_table *table)
{
	table->full = 0;
	table->end_simu = false;
	table->philos = malloc(sizeof(t_philos) * table->philos_n);
	if (!table->philos)
		return (_error(ERROR_MAL));
	table->forks = malloc(sizeof(t_fork) * table->philos_n);
	if (!table->forks)
		return (free(table->philos), _error(ERROR_MAL));
	if (-1 == init_mutex(table))
		return (-1);
	init_philos(table);
	return (0);
}
