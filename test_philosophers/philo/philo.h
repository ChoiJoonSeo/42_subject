/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:37:39 by yeham             #+#    #+#             */
/*   Updated: 2023/02/24 15:55:54 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_info
{
	pthread_t		philosopher;
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	long			last_eat;
	t_data			*link_table;
}	t_info;

struct s_data
{
	t_info			**link_philo;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				stop_flag;
	long			time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	last_ate;
};

int		ft_atoi(const char *str);
void	monitoring(t_data *table);
int		ft_operate(t_info *philo);
int		check_stop_flag(t_info *philo);
long	get_time(long time);
void	msleep(int time);
void	mutex_printf(char *string, t_info *philo, int color);
void	*routine(void *argument);
void	one_die(t_data *table);
void	get_fork(t_info *philo, int fork);

#endif
