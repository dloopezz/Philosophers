/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:14:27 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/05/02 12:19:40 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *write_msg(void *txt)
{
	char *msg;
	msg = (char *)txt;
	while (1)
	{
		printf("%s\n", msg);
		sleep(1);
	}
}

int main(void)
{
	pthread_t	process1;
	pthread_t	process2;

	pthread_create(&process2, NULL, &write_msg, "21");
	pthread_create(&process1, NULL, &write_msg, "42");
	printf("aqui\n");
	// pthread_join(process1, NULL);
	// pthread_join(process2, NULL);
	return 0;
}
