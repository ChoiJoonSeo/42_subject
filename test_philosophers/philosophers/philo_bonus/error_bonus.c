/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamehri <tamehri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:16:28 by tamehri           #+#    #+#             */
/*   Updated: 2024/05/18 14:33:26 by tamehri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos_bonus.h"

void	putendl_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

int	quit(t_errors _error_type)
{
	_error(_error_type);
	exit(1);
}

int	_error(t_errors _error_type)
{
	if (_error_type == ERROR_MAL)
		putendl_fd("Error : malloc", 2);
	else if (_error_type == ERROR_ARGS)
		putendl_fd("\033[31mError : wrong number of arguments\033[0m", 2);
	else if (_error_type == ERROR_FORMAT)
		putendl_fd("\033[31mError : argument format\033[0m", 2);
	else if (_error_type == PTHREAD_CREATE)
		putendl_fd("\033[31mError : pthread_create\033[0m", 2);
	else if (_error_type == SEM_OPEN)
		putendl_fd("\033[31mError : sem_open\033[0m", 2);
	else if (_error_type == ERROR_FORK)
		putendl_fd("\033[31mError : fork\033[0m", 2);
	return (-1);
}
