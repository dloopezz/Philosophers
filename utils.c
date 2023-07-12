/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:52:17 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/07/12 12:44:00 by dlopez-s         ###   ########.fr       */
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
	if (philo->data->philo_died == 0)
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
int ft_usleep(unsigned int time)
{
	uint64_t	ref;

	ref = get_time() + time;
	while (get_time() < ref)
		usleep(100); 
	return (0);
}
