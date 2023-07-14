/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopezz <lopezz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:52:17 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/07/14 00:09:49 by lopezz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_found(char *str)
{
	printf("%s\n", str);
	exit (EXIT_FAILURE);
}

void	print_action(char *action, t_philo *philo)
{
	pthread_mutex_lock(philo->plock);
	if (philo->data->end_flag == FALSE)
		printf("%llums philo %d %s\n", (get_time() - philo->data->start), philo->philo_id, action);
	pthread_mutex_unlock(philo->plock);
}

long long	ft_atoi_philo(const char *str)
{
	int			i;
	long long	nb;

	i = 0;
	nb = 0;
	if (str[i] == '-')
		error_found("Error: no negative arguments allowed");
	if (str[i] < '0' || str[i] > '9')
		error_found("Error: no letters or symbols allowed");
	while (str[i] >= '0' && str[i] <= '9')
		nb = (str[i++] - '0') + (nb * 10);
	if ((str[i] < '0' || str[i] > '9') && str[i])
		error_found("Error: no letters or symbols allowed");
	// if (nb > INT_MAX || nb < INT_MIN)
	// 	error_found("Error\n");
	return (nb);
}

uint64_t	get_time(void)
{
	struct timeval	cur_time;

	//proteger gettimeofday
	gettimeofday(&cur_time, NULL);
	return ((cur_time.tv_sec * (uint64_t)1000) + (cur_time.tv_usec / 1000));
}

//es un usleep pero recibe milisegundos en vez de microsegundos
// int fzp(unsigned int time)
// {
// 	uint64_t	ref;

// 	ref = get_time() + time;
// 	while (get_time() < ref)
// 		usleep(100); 
// 	return (0);
// }

void ft_usleep(unsigned int time)
{
	long long	star_time;
	long long	act_time;

	star_time = get_time();
	act_time = star_time;
	while (star_time >= (act_time - time))
	{
		act_time = get_time();
		usleep(100);
	}
}
