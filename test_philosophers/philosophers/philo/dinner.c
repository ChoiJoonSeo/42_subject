/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:19:00 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/18 13:58:54 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	print_status(t_philos *philo, t_status status)
{
	long	time_stamp;

	pthread_mutex_lock(&philo->table->table_m);
	time_stamp = get_current_time() - philo->table->simu_start_time;
	pthread_mutex_unlock(&philo->table->table_m);
	pthread_mutex_lock(&philo->table->print_m);
	if (status == DIED)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "died");
	else if (status == FORK && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "has taken a fork");
	else if (status == FORK && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "has taken a fork");
	else if (status == EATING && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "is eating");
	else if (status == SLEEPING && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "is sleeping");
	else if (status == THINKING && simu_ended(philo->table) == false)
		printf("%ld\t%d\t%s\n", time_stamp, philo->tid, "is thinking");
	pthread_mutex_unlock(&philo->table->print_m);
}

bool	simu_ended(t_table *table)
{
	bool	end_simu;

	pthread_mutex_lock(&table->table_m);
	end_simu = table->end_simu;
	pthread_mutex_unlock(&table->table_m);
	return (end_simu);
}

void	eating(t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_m);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->right_fork->fork_m);
	print_status(philo, FORK);
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->philo_m);
	philo->last_eaten = get_current_time() - philo->table->simu_start_time;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_m);
	ft_usleep(philo, philo->t_eat);
	pthread_mutex_unlock(&philo->left_fork->fork_m);
	pthread_mutex_unlock(&philo->right_fork->fork_m);
}

void	*have_dinner(void *param)
{
	t_philos	*philo;

	philo = (t_philos *)param;
	if (philo->tid % 2)
		ft_usleep(philo, philo->t_eat);
	while (simu_ended(philo->table) == false)
	{
		if (philo->meals_eaten == philo->meals_nbr)
		{
			pthread_mutex_lock(&philo->table->table_m);
			philo->table->full++;
			pthread_mutex_unlock(&philo->table->table_m);
		}
		eating(philo);
		print_status(philo, SLEEPING);
		ft_usleep(philo, philo->t_sleep);
		print_status(philo, THINKING);
	}
	return (NULL);
}
