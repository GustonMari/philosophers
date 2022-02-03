/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:09:12 by gmary             #+#    #+#             */
/*   Updated: 2022/02/03 13:50:58 by gmary            ###   ########.fr       */
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

//void	ft_sleep(int i)
//{
//	
//}
//
//void	ft_eating(int i)
//{
//	
//}
//
//void	*philosopher(void	*nb)
//{
//	(void)nb;
//	while (1)
//	{
//		ft_sleep();
//		ft_take_fork()
//		ft_eating()
//		ft_drop_fork()
//	}
//	//pthread_exit(NULL);
//}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	else
		return (1);
}

int	check(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while(av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_global	*pars_info(int ac, char **av, t_global *all)
{
	//t_info *info = NULL;

	all->nb_phil = ft_atoi(av[1]);
	all->t_die = ft_atoi(av[2]);
	all->t_eat = ft_atoi(av[3]);
	all->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		all->nb_eat = ft_atoi(av[5]);
	return (all);
}

//t_global	init_philo(t_info info, t_global *all)
void	init_philo(t_global *all)
{
	unsigned int	i;
	int	start;

	i = 0;
	all->philo = malloc(sizeof(t_global) * all->nb_phil);
	if (!all->philo)
		ft_print_error(3);
	all->fork = malloc(sizeof(pthread_mutex_t) * all->nb_phil);
	if (!all->fork)
		ft_print_error(3);
	start = ft_time();
	while (i < all->nb_phil)
	{
		all->philo[i].index = i + 1;
		all->dead = 0;
		all->philo[i].count = 0;
		if ((pthread_mutex_init(&all->fork[i], NULL)) != 0)
			ft_print_error(1);
		if ((pthread_mutex_init(&all->philo[i].l_meal, NULL)) != 0)
			ft_print_error(2);
		all->philo[i].start = start;
		all->philo[i].all = all;
		all->philo[i].t_lmeal = ft_time();
		i++;
	}
	if (pthread_mutex_init(&all->print, NULL) != 0)
		ft_print_error(6);
}

int	start(t_global *all)
{
	init_philo(all);
	ft_dispatch(all);
	//NE PAS OUBLIER DE FREE ALL
	return (2);
}

void	destroy_fork(pthread_mutex_t *fork, t_global *all)
{
	unsigned int	i;
	int error;

	i = 0;
	while (i < all->nb_phil)
	{
		pthread_mutex_unlock(&fork[i]);
		error = pthread_mutex_destroy(&fork[i]);
		if(error != 0)
		{
			fprintf(stderr, "%d\n", error);
			ft_print_error(4);
		}
		i++;
	}
	free(fork);
}

void	unlock_all(t_global *all)
{
	unsigned int	i;
	int error;

	i = 0;
	pthread_mutex_unlock(&all->print);
	pthread_mutex_unlock(&all->check);
	while (i < all->nb_phil)
	{
		error = pthread_mutex_unlock(&all->fork[i]);
		if(error != 0)
		{
			fprintf(stderr, "unlock -------------- %d\n", error);
		}
		i++;
	}
}

void	ft_clean_all(t_global *all)
{
	unsigned int	i;

	i = 0;
	write(1, "cleaning all\n", 13);
	sleep(1);
	unlock_all(all);
	if (all->fork)
		destroy_fork(all->fork, all);
	//destroy_fork(all->fork, all);
		//while (i < all->nb_phil)
		//{
			//pthread_mutex_destroy(&all->fork[i]);
			//i++;
		//}
	//i = 0;
	//while (i < all->nb_phil)
	//{
	//	pthread_mutex_destroy(&all->philo[i].l_meal);
	//	i++;
	//}
	//free(all->fork);
	//free(&all->philo->l_meal);
	free(all->philo);
	//destroy le print
	// a remplir
}

int	main(int ac, char **av)
{
	t_global	all;

	if (ac < 5 || ac > 6 || !check(ac, av))
	{
		write(1, "No no no, not good arguments\n", 29);
		return (0);
	}
	if(start(pars_info(ac, av, &all)) == 2)
		write(1, "end", 3);
	ft_clean_all(&all);
	return (0);
}
