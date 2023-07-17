/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:52:17 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/07/17 16:11:29 by dlopez-s         ###   ########.fr       */
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
	uint64_t	time_ms;

	pthread_mutex_lock(philo->plock);
	time_ms = (get_time() - philo->data->start);
	if (philo->data->end_flag == FALSE)
		printf("%llums philo %d %s\n", time_ms, philo->philo_id, action);
	pthread_mutex_unlock(philo->plock);
}

long long	ft_atoi_philo(const char *str)
{
	int			i;
	long long	nb;

	i = 0;
	nb = 0;
	if (str[i] == '-')
		error_found("Invalid input");
	if (str[i] < '1' || str[i] > '9')
		error_found("Invalid input");
	while (str[i] >= '0' && str[i] <= '9')
		nb = (str[i++] - '0') + (nb * 10);
	if ((str[i] < '1' || str[i] > '9') && str[i])
		error_found("Invalid input");
	if (nb > INT_MAX || nb < INT_MIN)
		error_found("Invalid input\n");
	return (nb);
}

uint64_t	get_time(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return ((cur_time.tv_sec * (uint64_t)1000) + (cur_time.tv_usec / 1000));
}

int	ft_usleep(unsigned int time)
{
	uint64_t	ref;

	ref = get_time() + time;
	while (get_time() < ref)
		usleep(100);
	return (0);
}
