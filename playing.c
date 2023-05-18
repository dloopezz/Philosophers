/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:14:27 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/05/18 12:47:32 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int cont = 0;
pthread_mutex_t lock;

void  *routine()
{
  int i;

  i = -1;
  while (++i < 1000000)
  {
    pthread_mutex_lock(&lock);
  	  cont++;
    pthread_mutex_unlock(&lock);
  }
  return (NULL);
}

int main()
{
  pthread_t tid1, tid2;

  pthread_mutex_init(&lock, NULL);
  pthread_create(&tid1, NULL, &routine, NULL);
  pthread_create(&tid2, NULL, &routine, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_mutex_destroy(&lock);
  printf("cont: %d\n", cont);
}

// // thread_routine is the function the thread invokes right after its
// // creation. The thread ends at the end of this function.
// void	*thread_routine(void *data)
// {
// 	printf("--Thread: Hello!\n");
// 	return (data); // The thread ends here.
// }

// int	main()
// {
// 	pthread_t	tid1;	// First thread's ID
// 	pthread_t	tid2;	// Second thread's ID

// 	// Creating the first thread that will go
// 	// execute its thread_routine function.
// 	pthread_create(&tid1, NULL, thread_routine, NULL);
// 	printf("Main: Created first thread\n");
// 	// Creating the second thread that will also execute thread_routine.
// 	pthread_create(&tid2, NULL, thread_routine, NULL);
// 	printf("Main: Created second thread\n");
// 	// The main thread waits for the new threads to end
// 	// with pthread_join.
// 	pthread_join(tid1, NULL);
// 	printf("Main: Joining first thread\n");
// 	pthread_join(tid2, NULL);
// 	printf("Main: Joining second thread\n");
// 	return (0);
// }
