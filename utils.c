/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:52:17 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/05/18 13:14:38 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi_philo(const char *str)
{
	int			i;
	int			sign;
	long long	nb;

	i = 0;
	sign = 1;
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

int	error_found(char *str)
{
	printf("%s\n", str);
	exit (EXIT_FAILURE);
}