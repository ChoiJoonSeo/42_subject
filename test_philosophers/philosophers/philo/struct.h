/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:01:55 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/18 14:33:35 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_philos	t_philos;
typedef struct s_table	t_table;
typedef struct s_fork	t_fork;
typedef enum e_status	t_status;
typedef enum e_errors	t_errors;

struct s_philos
{
	int				tid;
	long			last_eaten;
	long			meals_eaten;
	long			t_eat;
	long			t_sleep;
	long			meals_nbr;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_table			*table;
	pthread_t		thread_id;
	pthread_mutex_t	philo_m;
};

struct s_fork
{
	pthread_mutex_t	fork_m;
};

struct s_table
{
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			meals_nbr;
	long			simu_start_time;
	bool			end_simu;
	int				philos_n;
	int				full;
	t_fork			*forks;
	t_philos		*philos;
	pthread_mutex_t	print_m;
	pthread_mutex_t	table_m;
};

enum e_status
{
	DIED,
	FORK,
	EATING,
	SLEEPING,
	THINKING,
};

enum e_errors
{
	ERR_DEF,
	ERROR_MAL,
	ERROR_ARGS,
	ERROR_FORMAT,
	PTHREAD_JOIN,
	PTHREAD_CREATE,
	PTHREAD_MUTEX_INIT,
	PTHREAD_MUTEX_DESTROY,
};

#endif
