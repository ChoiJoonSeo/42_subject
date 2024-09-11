/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:58:21 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/29 10:14:53 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

static int	init_semaphores(t_table *table)
{
	sem_unlink("/print_s");
	table->print_s = sem_open("/print_s", O_CREAT, 0644, 1);
	if (table->print_s == SEM_FAILED)
		return (_error(SEM_OPEN));
	sem_unlink("/forks_s");
	table->fork_s = sem_open("/forks_s", O_CREAT, 0644, table->philos_n);
	if (table->fork_s == SEM_FAILED)
		return (_error(SEM_OPEN));
	sem_unlink("/full_s");
	table->full_s = sem_open("/full_s", O_CREAT, 0644, 0);
	if (table->full_s == SEM_FAILED)
		return (_error(SEM_OPEN));
	sem_unlink("/end_simu_s");
	table->end_simu_s = sem_open("/end_simu_s", O_CREAT, 0644, 0);
	if (table->end_simu_s == SEM_FAILED)
		return (_error(SEM_OPEN));
	return (0);
}

static int	init_philos(t_table *table)
{
	t_philos	*philo;
	int			i;

	i = -1;
	while (++i < table->philos_n)
	{
		philo = table->philos + i;
		philo->table = table;
		philo->philo_id = i + 1;
	}
	return (0);
}

int	fill_table(t_table *table)
{
	table->meals_eaten = 0;
	table->philos = malloc(sizeof(t_philos) * table->philos_n);
	if (!table->philos)
		return (_error(ERROR_MAL));
	if (-1 == init_philos(table))
		return (free(table->philos), _error(-1));
	if (-1 == init_semaphores(table))
		return (free(table->philos), _error(-1));
	return (0);
}
