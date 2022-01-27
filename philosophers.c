/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:09:12 by gmary             #+#    #+#             */
/*   Updated: 2022/01/27 17:14:17 by gmary            ###   ########.fr       */
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

void	ft_sleep(int i)
{
	
}

void	ft_eating(int i)
{
	
}

void	*philosopher(void	*nb)
{
	(void)nb;
	while (1)
	{
		ft_sleep();
		ft_take_fork()
		ft_eating()
		ft_drop_fork()
	}
	//pthread_exit(NULL);
}

int	main(int ac, char **av)
{
	(void)ac;
	pthread_t *th;
	int nb_philo = ft_atoi(av[1]);
	int	i = 0;
	//pthread_mutex_t *fork;
	t_philo *philo;
	
	th = malloc(sizeof(pthread_t) * nb_philo);
	philo = malloc(sizeof(t_philo) * nb_philo);
	//fork = malloc(sizeof(pthread_mutex_t) * nb_philo);
	while (i < nb_philo)
	{
		philo[i].index = i;
		pthread_create(&(th[i]), NULL, philosopher, &philo[i]);
		pthread_mutex_init(&philo[i].fork, NULL);
		//pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	i = 0;
	//while (i < nb_philo)
	//{
	//	pthread_mutex_destroy(&fork[i]);
	//	i++;
	//}
	return (0);
}

int	ft_chrono(void)
{
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	usleep(15000);
	gettimeofday(&end, NULL);
	return ((end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec) / 1000));
}

/*
int	main()
{
	pthread_t *th;
	//pthread_t th[6];
	int nb_philo = ft_atoi(av[1]);
	int	i = 0;
	pthread_mutex_t *fork;
	//philo	*philo_n;
	
	th = malloc(sizeof(pthread_t) * nb_philo);
	//philo_n = malloc(sizeof(philo) * nb_philo);
	pthread_mutex_init(&fork, NULL);
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
	pthread_mutex_destroy(&fork);
	return (0);
}
*/