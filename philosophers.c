/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:09:12 by gmary             #+#    #+#             */
/*   Updated: 2022/01/26 17:06:51 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*
number_of_philosophers 
time_to_die =>ms since last meal or begin
time_to_eat =>ms hold 2 fork
time_to_sleep =>ms sleep
[number_of_times_each_philosopher_must_eat] => (simulation stop)

philo must be:
- timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died

A displayed state message should not be mixed up with another message

A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.
*/
////////////////////////////////////////////////////////////////////////
/*
exit on y mets null car on part du principe que create a marcher
son second paramètre, un pointeur, 
permet de récupérer la valeur retournée par la fonction dans laquelle s'exécute le thread

*/
pthread_mutex_t lock;

void	*print(void	*nb)
{
	//(void)nb;
	pthread_mutex_lock(&lock);
	printf("i = %d\n", *(int *)nb);
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
	//return NULL;
}

int	main()
{
	pthread_t *th;
	//pthread_t th[6];
	int nb_philo = 6;
	int	i = 0;
	//philo	*philo_n;
	
	th = malloc(sizeof(pthread_t) * nb_philo);
	//philo_n = malloc(sizeof(philo) * nb_philo);
	pthread_mutex_init(&lock, NULL);
	while (i < nb_philo)
	{
		//philo_n->var = i;
		pthread_create(&(th[i]), NULL, print, &i);
		printf("in 1------------ =%d\n", i);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		pthread_join(th[i], NULL);
		printf("in 2---------------------------- =%d\n", i);
		i++;
	}
	pthread_mutex_destroy(&lock);
	return (0);
}

