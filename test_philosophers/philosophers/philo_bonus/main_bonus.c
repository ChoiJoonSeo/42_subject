/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:58:48 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/29 10:14:45 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

static void	clean_table(t_table *table)
{
	sem_close(table->print_s);
	sem_unlink("/print_s");
	sem_close(table->fork_s);
	sem_unlink("/forks_s");
	sem_close(table->full_s);
	sem_unlink("/full_s");
	sem_close(table->end_simu_s);
	sem_unlink("/end_simu_s");
	free(table->philos);
}

static void	*full_checker(void *param)
{
	t_table	*table;
	int		i;

	i = -1;
	table = (t_table *)param;
	while (++i < table->philos_n)
		sem_wait(table->full_s);
	sem_post(table->end_simu_s);
	return (NULL);
}

static void	kill_them(t_table *table, int pnumber)
{
	int	i;

	i = -1;
	while (++i < pnumber)
	{
		sem_post(table->full_s);
		kill((table->philos + i)->process_id, SIGKILL);
	}
}

static int	dinner_served(t_table *table)
{
	int			i;
	pthread_t	id;

	i = -1;
	if (1 == table->philos_n)
		return (one_philo(table));
	table->simu_start_time = get_current_time();
	while (++i < table->philos_n)
	{
		(table->philos + i)->process_id = fork();
		if (-1 == (table->philos + i)->process_id)
			return (kill_them(table, i), _error(ERROR_FORK));
		if (0 == (table->philos + i)->process_id)
			routine(table->philos + i);
	}
	if (0 != pthread_create(&id, NULL, &full_checker, table))
		return (kill_them(table, table->philos_n), quit(PTHREAD_CREATE));
	pthread_detach(id);
	sem_wait(table->end_simu_s);
	kill_them(table, table->philos_n);
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
