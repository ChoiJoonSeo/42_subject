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


long	get_time(long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - time);
}

void	msleep(int time)
{
	long	temp;

	temp = get_time(0);
	while (get_time(0) - temp < time)
		usleep(100);
}

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

#include <unistd.h>

void	monitoring(t_data *table)
{
	int	i;

	i = table->philo_num;
	while (1)
	{
		if (++i >= table->philo_num)
			i = 0;
		pthread_mutex_lock(&table->last_ate);
		if (get_time(table->link_philo[i]->last_eat) >= table->time_to_die)
		{
			if (table->link_philo[i]->eat_count != table->must_eat)
			{
				pthread_mutex_lock(&table->print);
				table->stop_flag = 1;
				printf("%ld %d died\n", get_time \
					(table->time), table->link_philo[i]->id);
				if (table->philo_num == 1)
					pthread_mutex_unlock(&table->fork[0]);
				pthread_mutex_unlock(&table->print);
			}
			pthread_mutex_unlock(&table->last_ate);
			break ;
		}
		pthread_mutex_unlock(&table->last_ate);
	}
}

void	*routine(void *argument)
{
	t_info	*philo;

	philo = argument;
	if (!(philo->id & 1))
		usleep(1000);
	while (1)
		if (ft_operate(philo) == 0)
			break ;
	return (0);
}

int	check_stop_flag(t_info *philo)
{
	pthread_mutex_lock(&philo->link_table->print);
	if (philo->link_table->stop_flag == 1)
	{
		pthread_mutex_unlock(&philo->link_table->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->link_table->print);
	return (0);
}

void	get_fork(t_info *philo, int fork)
{
	pthread_mutex_lock(&philo->link_table->fork[fork]);
	mutex_printf("has taken a fork", philo, 2);
}

void	mutex_printf(char *string, t_info *philo, int color)
{
	if (check_stop_flag(philo))
		return ;
	pthread_mutex_lock(&philo->link_table->print);
	printf("%ld %d \033[0;3%dm%s\033[0m\n", get_time \
		(philo->link_table->time), philo->id, color, string);
	pthread_mutex_unlock(&philo->link_table->print);
}



int	take_fork(t_info *philo)
{
	int	index;

	index = 0;
	while (index < 2)
	{
		if (check_stop_flag(philo))
			return (0);
		if (index == 0)
		{
			if (philo->id & 1)
				get_fork(philo, philo->left_fork);
			else
				get_fork(philo, philo->right_fork);
		}
		else if (index == 1)
		{
			if (philo->id & 1)
				get_fork(philo, philo->right_fork);
			else
				get_fork(philo, philo->left_fork);
		}
		index++;
	}
	return (1);
}

int	eating(t_info *philo)
{
	int	result;

	result = 1;
	if (check_stop_flag(philo))
	{
		pthread_mutex_unlock(&philo->link_table->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->link_table->fork[philo->right_fork]);
		return (0);
	}
	mutex_printf("is eating", philo, 1);
	pthread_mutex_lock(&philo->link_table->last_ate);
	philo->last_eat = get_time(0);
	philo->eat_count++;
	if (philo->eat_count == philo->link_table->must_eat)
		result = 0;
	pthread_mutex_unlock(&philo->link_table->last_ate);
	msleep(philo->link_table->time_to_eat);
	pthread_mutex_unlock(&philo->link_table->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->link_table->fork[philo->right_fork]);
	return (result);
}

int	sleeping(t_info *philo)
{
	if (check_stop_flag(philo))
		return (0);
	mutex_printf("is sleeping", philo, 4);
	msleep(philo->link_table->time_to_sleep);
	return (1);
}

int	thinking(t_info *philo)
{
	if (check_stop_flag(philo))
		return (0);
	mutex_printf("is thinking", philo, 8);
	usleep(500);
	return (1);
}

int	ft_operate(t_info *philo)
{
	if (take_fork(philo))
		if (eating(philo))
			if (sleeping(philo))
				if (thinking(philo))
					return (1);
	return (0);
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
