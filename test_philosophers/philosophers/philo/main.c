/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/18 14:22:42 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	clean_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philos_n)
	{
		if (0 != pthread_mutex_destroy(&table->forks[i].fork_m))
			return (_error(PTHREAD_MUTEX_DESTROY));
		if (0 != pthread_mutex_destroy(&table->philos[i].philo_m))
			return (_error(PTHREAD_MUTEX_DESTROY));
	}
	if (0 != pthread_mutex_destroy(&table->print_m))
		return (_error(PTHREAD_MUTEX_DESTROY));
	if (0 != pthread_mutex_destroy(&table->table_m))
		return (_error(PTHREAD_MUTEX_DESTROY));
	return (0);
}

int	dinner_served(t_table *table)
{
	pthread_t	id;
	int			i;

	i = -1;
	if (table->philos_n == 1)
		return (single_philo(table));
	table->simu_start_time = get_current_time();
	while (++i < table->philos_n)
	{
		if (0 != pthread_create(&table->philos[i].thread_id, \
			NULL, &have_dinner, table->philos + i))
			return (_error(PTHREAD_CREATE));
	}
	if (0 != pthread_create(&id, NULL, &monitor, table))
		return (_error(PTHREAD_CREATE));
	if (0 != pthread_join(id, NULL))
		return (_error(PTHREAD_CREATE));
	i = -1;
	while (++i < table->philos_n)
	{
		if (0 != pthread_join(table->philos[i].thread_id, NULL))
			return (_error(PTHREAD_JOIN));
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (_error(ERROR_ARGS));
	if (-1 == parsing(&table, av + 1))
		return (1);
	if (0 == fill_table(&table))
		dinner_served(&table);
	clean_table(&table);
}
