/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:09:12 by yeham             #+#    #+#             */
/*   Updated: 2024/08/31 07:06:45 by joonchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
//#include <sys/_pthread/_pthread_mutex_t.h>

int	init_data(int argc, char *argv[], t_data *table)
{
	table->must_eat = -1;
	table->philo_num = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	if (table->philo_num < 1 || table->time_to_die < 1 || \
		table->time_to_eat < 1 || table->time_to_sleep < 1 || \
			(argc == 6 && table->must_eat < 1))
	{
		printf("argument error\n");
		return (1);
	}
	table->time = get_time(0);
	table->link_philo = malloc(sizeof(t_info *) * table->philo_num);
	return (0);
}

void	init_mutex(t_data *table)
{
	int	i;

	i = 0;
	table->fork = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	while (i < table->philo_num)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->last_ate, NULL);
}

void	init_philo(int i, t_info *philo, t_data *table)
{
	philo->id = i + 1;
	philo->left_fork = i;
	philo->right_fork = (i + 1) % table->philo_num;
	philo->link_table = table;
	philo->eat_count = 0;
	philo->last_eat = get_time(0);
}

void	all_mutex_destroy(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->last_ate);
}

void	run_philo(t_data *table)
{
	t_info	**philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_info *) * table->philo_num);
	while (++i < table->philo_num)
	{
		philo[i] = malloc(sizeof(t_info));
		init_philo(i, philo[i], table);
		table->link_philo[i] = philo[i];
		pthread_create(&philo[i]->philosopher, \
			NULL, &routine, (void *) philo[i]);
	}
	monitoring(table);
	i = -1;
	while (++i < table->philo_num)
	{
		pthread_join(philo[i]->philosopher, NULL);
		free(philo[i]);
	}
	all_mutex_destroy(table);
	free(table->link_philo);
	free(table->fork);
	free(philo);
}

int	main(int argc, char *argv[])
{
	t_data	table;

	if (!(argc == 5 || argc == 6))
	{
		printf("argument error\n");
		return (0);
	}
	if (init_data(argc, argv, &table))
		return (0);
	init_mutex(&table);
	run_philo(&table);
	return (0);
}
