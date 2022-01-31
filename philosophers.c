/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:09:12 by gmary             #+#    #+#             */
/*   Updated: 2022/01/31 10:05:28 by gmary            ###   ########.fr       */
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

t_info	pars_info(int ac, char **av)
{
	t_info info;

	info.nb_phil = ft_atoi(av[1]);
	info.t_die = ft_atoi(av[2]);
	info.t_eat = ft_atoi(av[3]);
	info.t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info.nb_eat = ft_atoi(av[5]);
	return (info);
}

t_global	init_philo(t_info info, t_global all)
{
	unsigned int	i;
	int	start;
	//struct timeval start;

	//gettimeofday(&start, NULL);
	i = 0;
	all.philo->fork = malloc(sizeof(pthread_mutex_t) * info.nb_phil);
	start = ft_time();
	while (i < info.nb_phil)
	{
		all.philo[i].info->nb_phil = info.nb_phil;
		all.philo[i].info->t_die = info.t_die;
		all.philo[i].info->t_eat = info.t_eat;
		all.philo[i].info->t_sleep = info.t_sleep;
		all.philo[i].info->nb_eat = info.nb_eat;
		all.philo[i].info->f_left = i;
		all.philo[i].info->f_right = (i + 1) % info.nb_phil;
		all.philo[i].index = i + 1;
		all.dead = 0;
		all.count_eat = 0;
		//all.philo[i].dead = 0;
		//philo[i].begin = start;
		all.philo[i].start = start;
		//pthread_mutex_init(&philo[i].fork[i] ,NULL);
		i++;
	}
	return (all);
}

int	start(t_info info)
{
	t_global all;
	//t_philo	*philo;
	//pthread_mutex_

	all.philo = malloc(sizeof(t_philo) * info.nb_phil);

	//philo[i]
	//philo = init_philo(info, philo);
	init_philo(info, all);
	ft_dispatch(all);
	return (0);
}

void	ft_clean_all(void)
{
	write(1, "cleaning all\n", 13);
	// a remplir
}

int	main(int ac, char **av)
{
	//t_info info;

	if (ac < 5 || ac > 6 || !check(ac, av))
	{
		write(1, "No no no, not good arguments\n", 29);
		return (0);
	}
	if(start(pars_info(ac, av)) == 2)
		ft_clean_all();
	return (0);
}
