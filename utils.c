/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopezz <lopezz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:52:17 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/06/05 18:02:42 by lopezz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_found(char *str)
{
	printf("%s\n", str);
	exit (EXIT_FAILURE);
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
	gettimeofday(&cur_time,  NULL);
	
	// printf("Time in sec: %ld\nTime in usec: %d\n", cur_time.tv_sec, cur_time.tv_usec);
	return ((cur_time.tv_sec * (uint64_t)1000) + (cur_time.tv_usec / 1000));
}

//es un usleep pero recibe milisegundos en vez de microsegundos
int ft_usleep(unsigned int time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10); 
	//dividir por 10 por buena praxis, no es bueno bloquear el programa tanto tiempo
	//mejor hacer ese sleep de time en 10 iteraciones con menos tiempo de espera cada una
	return (0);
}
