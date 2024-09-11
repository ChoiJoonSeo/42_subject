/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:00 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/29 10:13:34 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

void	print_status(t_philos *philo, t_status status)
{
	long	time;

	time = get_current_time() - philo->table->simu_start_time;
	sem_wait(philo->table->print_s);
	if (status == DIED)
		printf("%zu\t%d\tdied\n", time, philo->philo_id);
	else if (status == FORK)
		printf("%zu\t%d\thas taken a fork\n", time, philo->philo_id);
	else if (status == EATING)
		printf("%zu\t%d\tis eating\n", time, philo->philo_id);
	else if (status == SLEEPING)
		printf("%zu\t%d\tis sleeping\n", time, philo->philo_id);
	else if (status == THINKING)
		printf("%zu\t%d\tis thinking\n", time, philo->philo_id);
	if (status != DIED)
		sem_post(philo->table->print_s);
}

void	*checker(void *param)
{
	t_philos	*philo;
	t_table		*table;

	philo = (t_philos *)param;
	table = philo->table;
	while (1)
	{
		if (get_current_time() - table->last_eaten > table->t_die)
		{
			print_status(philo, DIED);
			sem_post(table->end_simu_s);
			break ;
		}
	}
	return (NULL);
}

static void	eat(t_philos *philo)
{
	sem_wait(philo->table->fork_s);
	print_status(philo, FORK);
	sem_wait(philo->table->fork_s);
	print_status(philo, FORK);
	print_status(philo, EATING);
	philo->table->last_eaten = get_current_time();
	philo->table->meals_eaten++;
	if (philo->table->meals_eaten == philo->table->meals_nbr)
		sem_post(philo->table->full_s);
	ft_usleep(philo->table->t_eat);
	sem_post(philo->table->fork_s);
	sem_post(philo->table->fork_s);
}

int	routine(t_philos *philo)
{
	t_table		*table;
	pthread_t	tid;

	table = philo->table;
	table->last_eaten = get_current_time();
	if (0 != pthread_create(&tid, NULL, &checker, philo))
		return (quit(ERROR));
	pthread_detach(tid);
	while (1)
	{
		eat(philo);
		print_status(philo, SLEEPING);
		ft_usleep(table->t_sleep);
		print_status(philo, THINKING);
	}
	return (0);
}
