/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:09:12 by gmary             #+#    #+#             */
/*   Updated: 2022/03/21 09:47:25 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_global	*pars_info(int ac, char **av, t_global *all)
{
	all->nb_phil = ft_atoi(av[1]);
	all->t_die = ft_atoi(av[2]);
	all->t_eat = ft_atoi(av[3]);
	all->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		all->nb_eat = ft_atoi(av[5]);
	pthread_mutex_init(&all->check, NULL);
	return (all);
}

int	init_philo(t_global *all, unsigned int i)
{
	int	start;

	all->philo = malloc(sizeof(t_global) * all->nb_phil);
	if (!all->philo)
		return (ft_print_error(3));
	all->fork = malloc(sizeof(pthread_mutex_t) * all->nb_phil);
	if (!all->fork)
		return (ft_print_error(3));
	start = ft_time();
	while (++i < all->nb_phil)
	{
		all->philo[i].index = i + 1;
		all->dead = 0;
		all->philo[i].count = 0;
		if ((pthread_mutex_init(&all->fork[i], NULL)) != 0
			|| (pthread_mutex_init(&all->philo[i].l_meal, NULL)) != 0)
			return (ft_print_error(1));
		all->philo[i].start = start;
		all->philo[i].all = all;
		all->philo[i].t_lmeal = ft_time();
	}
	if (pthread_mutex_init(&all->print, NULL) != 0)
		return (ft_print_error(6));
	return (0);
}

int	start(t_global *all)
{
	unsigned int	i;

	i = -1;
	if (init_philo(all, i))
		return (1);
	if (ft_dispatch(all))
		return (1);
	return (2);
}

int	main(int ac, char **av)
{
	t_global	*all;
	int			result;

	if (ac < 5 || ac > 6 || !check(ac, av))
	{
		printf("No no no, not good arguments\n");
		return (0);
	}
	all = malloc(sizeof(t_global));
	if (!all)
		return (0);
	memset(all, 0, sizeof(t_global));
	result = start(pars_info(ac, av, all));
	if (result == 2)
		printf("end\n");
	if (result == 1)
		printf("Problem append\n");
	ft_clean_all(&all);
	free(all->philo);
	free(all->fork);
	free(all);
	return (0);
}
