/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:09:12 by gmary             #+#    #+#             */
/*   Updated: 2022/02/04 10:11:34 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
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
	all->nb_phil = ft_atoi(av[1]);
	all->t_die = ft_atoi(av[2]);
	all->t_eat = ft_atoi(av[3]);
	all->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		all->nb_eat = ft_atoi(av[5]);
	return (all);
}

int	init_philo(t_global *all, unsigned int i)
{
	int				start;

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
	t_global	all;
	int			result;

	if (ac < 5 || ac > 6 || !check(ac, av))
	{
		write(1, "No no no, not good arguments\n", 29);
		return (0);
	}
	result = start(pars_info(ac, av, &all));
	if (result == 2)
		write(1, "end\n", 4);
	if (result == 1)
		write(1, "Problem append\n", 16);
	ft_clean_all(&all);
	return (0);
}
