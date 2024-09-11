/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 13:42:27 by tamehri           #+#    #+#             */
/*   Updated: 2024/04/24 10:53:23 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*dinner(void *param)
{
	t_table	*table;

	table = (t_table *)param;
	print_status(table->philos, FORK);
	ft_usleep(table->philos, table->t_die);
	print_status(table->philos, DIED);
	return (NULL);
}

int	single_philo(t_table *table)
{
	table->simu_start_time = get_current_time();
	if (0 != pthread_create(&table->philos->thread_id, \
		NULL, &dinner, table))
		return (_error(PTHREAD_CREATE));
	if (0 != pthread_join(table->philos->thread_id, NULL))
		return (_error(PTHREAD_CREATE));
	return (0);
}
