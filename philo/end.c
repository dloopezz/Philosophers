/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:45:15 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/07/17 16:21:31 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_time(t_data *data, int i)
{
	if ((((get_time() - data->philos[i].start) - data->philos[i].last_meal)
			> data->philos[i].time_to_die))
	{
		print_action("died", &(data->philos[i]));
		pthread_mutex_lock(data->plock);
		data->end_flag = TRUE;
		pthread_mutex_unlock(data->plock);
		pthread_mutex_unlock(data->philos[i].left_fork);
		return (1);
	}
	return (0);
}

int	check_meals(t_data *data, int i)
{
	if (data->philos[i].min_meals == data->philos[i].eat_cont
		&& data->philos[i].is_fat == FALSE)
	{
		data->philos[i].is_fat = TRUE;
		data->nb_fat++;
		if (data->nb_fat == data->nb_philos)
		{
			pthread_mutex_lock(data->plock);
			data->end_flag = TRUE;
			pthread_mutex_unlock(data->plock);
			return (1);
		}
	}
	return (0);
}

void	ft_death(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			pthread_mutex_lock(data->philos[i].lock);
			if (check_death_time(data, i) || check_meals(data, i))
				return ;
			pthread_mutex_unlock(data->philos[i].lock);
		}
	}
}

void	free_data(t_data *data)
{
	free(data->philos);
	free(data->tid);
	free(data->forks);
	free(data->lock);
	free(data->plock);
}

void	end_threads(t_data *data)
{
	int	i;

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
