/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:26:57 by gmary             #+#    #+#             */
/*   Updated: 2022/02/04 10:17:55 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_fork(pthread_mutex_t *fork, t_global *all)
{
	unsigned int	i;
	int				error;

	i = 0;
	while (i < all->nb_phil)
	{
		error = pthread_mutex_destroy(&fork[i]);
		if (error != 0)
		{
			ft_print_error(4);
			return (1);
		}
		i++;
	}
	free(fork);
	return (0);
}

int	destroy_meal(t_global *all)
{
	unsigned int	i;
	int				error;

	i = 0;
	while (i < all->nb_phil)
	{
		error = pthread_mutex_destroy(&all->philo[i].l_meal);
		if (error != 0)
		{
			ft_print_error(8);
			return (1);
		}
		i++;
	}
	return (0);
}

int	unlock_all(t_global *all)
{
	unsigned int	i;
	int				error;

	i = 0;
	pthread_mutex_unlock(&all->print);
	pthread_mutex_unlock(&all->check);
	while (i < all->nb_phil)
	{
		error = pthread_mutex_unlock(&all->fork[i]);
		error = pthread_mutex_unlock(&all->philo[i].l_meal);
		if (error != 0)
		{
			write(2, "Error unlocking\n", 16);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_clean_all(t_global *all)
{
	write(1, "cleaning all\n", 13);
	usleep(1500);
	if (unlock_all(all))
		return ;
	usleep(1500);
	if (all->fork)
		if (destroy_fork(all->fork, all))
			return ;
	if (destroy_meal(all))
		return ;
	pthread_mutex_destroy(&all->print);
	pthread_mutex_destroy(&all->check);
	free(all->philo);
}
