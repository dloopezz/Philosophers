/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:33:36 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/05/19 17:46:56 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *dataa)
{
	t_data *data = dataa;
	printf("--Thread: %lluHello!\n", data->time_die);
	return (NULL);
}

int main (int argc, char **argv)
{
	t_data data;

	if (argc == 5 || argc == 6)
	{
		data.nb_philos = ft_atoi_philo(argv[1]);		
		if (data.nb_philos >= 1 && data.nb_philos <= 200)
			printf("Number of philos: %i\n", data.nb_philos);
		else
			error_found("Error: no negative arguments allowed");
		
		data.time_die = ft_atoi_philo(argv[2]);
		printf("Time to die: %llu\n", data.time_die);
		data.time_sleep = ft_atoi_philo(argv[3]);
		printf("Time to sleep: %llu\n", data.time_sleep);
		data.time_eat = ft_atoi_philo(argv[4]);
		printf("Time to eat: %llu\n", data.time_eat);
		data.min_meals = ft_atoi_philo(argv[5]);
		printf("Number of meals: %i\n", data.min_meals);
		printf("%llu\n", get_time());

		pthread_t si;
		int i = -1;
		while (++i < data.nb_philos)
		{
			// pthread_create(&(data.tid[i]), NULL, routine, &data);
			pthread_create(&si, NULL, routine, &data);
		}
		
		// i = 0;
		// while (data.tid[i])
		// {
		// 	printf("%d\n")
		// }

		
	}
	else
		error_found("Error: invalid number of arguments");
	return 0;
}
 