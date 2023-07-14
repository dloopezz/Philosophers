/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopezz <lopezz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:33:36 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/07/14 12:00:03 by lopezz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_data)
{
	t_philo *philo;

	philo = philo_data;

	pthread_mutex_lock(philo->plock);
	pthread_mutex_unlock(philo->plock);

	if (philo->philo_id % 2 == 0)
 		ft_usleep(200);

	pthread_mutex_lock(philo->plock);
	while (*(philo->end_flag) == FALSE)
	{
		pthread_mutex_unlock(philo->plock);
 
		pthread_mutex_lock(philo->left_fork);
		print_action("has taken his left fork", philo);

		pthread_mutex_lock(philo->right_fork);
		print_action("has taken his right fork", philo);

		// print_action("is eating", philo);
		// pthread_mutex_lock(philo->lock);
		// philo->eat_cont++;
		// pthread_mutex_unlock(philo->lock);
		// ft_usleep(philo->time_eat);
		// pthread_mutex_lock(philo->lock);
		// philo->last_meal = get_time() - philo->start;
		// pthread_mutex_unlock(philo->lock);

		pthread_mutex_lock(philo->lock);
		philo->last_meal = get_time() - philo->start;
		print_action("is eating", philo);
		if (philo->min_meals != -1)
			philo->eat_cont++;
		pthread_mutex_unlock(philo->lock);
		ft_usleep(philo->time_eat); //uauauau

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		print_action("is sleeping", philo);
		ft_usleep(philo->time_sleep);

		print_action("is thinking", philo);

		pthread_mutex_lock(philo->plock);
	}
	pthread_mutex_unlock(philo->plock);
	return (NULL);
}
 
void ft_death(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			pthread_mutex_lock(data->philos[i].lock);
			if ((((get_time() - data->philos[i].start) - data->philos[i].last_meal) > data->philos[i].time_to_die))
			{
				print_action("died", &(data->philos[i]));
				pthread_mutex_lock(data->plock);
	            data->end_flag = TRUE;
				pthread_mutex_unlock(data->plock);
				pthread_mutex_unlock(data->philos[i].left_fork);
				return ;
			}

			if (data->philos[i].min_meals == data->philos[i].eat_cont && data->philos[i].is_fat == FALSE)
			{
				data->philos[i].is_fat = TRUE;
				data->nb_fat++;
				
				if (data->nb_fat == data->nb_philos)
				{
					pthread_mutex_lock(data->plock);
					data->end_flag = TRUE;
					pthread_mutex_unlock(data->plock);
					return ;
				}
				// pthread_mutex_unlock(data->plock);
			}
			pthread_mutex_unlock(data->philos[i].lock);
		}
	}
}

// void ft_leaks()
// {
// 	system("leaks philo");
// }

void ft_atomaporculo(t_data *data)
{
	int i;
	
	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_unlock(data->philos[i].lock);
		pthread_join(data->tid[i], NULL);  
	}
	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_destroy(&(data->lock[i]));
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutex_destroy(&(data->plock[i]));
	}
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		// atexit(ft_leaks);
		alloc_memory(&data, argv);
		if (data.nb_philos >= 1 && data.nb_philos <= 200)
		{
			pthread_mutex_lock(data.plock);
			philo_init(&data, argc, argv);
			pthread_mutex_unlock(data.plock);
			ft_death(&data);
			ft_atomaporculo(&data);
			
			// free(data.philos);
			// free(data.tid);
			// free(data.forks);
			// free(data.lock);
			// free(data.plock);
		}
		return (0);
	}
	else
		error_found("Error: invalid number of arguments");
	return (0);
}

