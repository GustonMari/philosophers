/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:26:57 by gmary             #+#    #+#             */
/*   Updated: 2022/02/03 15:48:42 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_fork(pthread_mutex_t *fork, t_global *all)
{
	unsigned int	i;
	int error;

	i = 0;
	while (i < all->nb_phil)
	{
		//pthread_mutex_unlock(&fork[i]);
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
void	destroy_meal(t_global *all)
{
	unsigned int	i;
	int error;

	i = 0;
	while (i < all->nb_phil)
	{
		//pthread_mutex_unlock(&fork[i]);
		error = pthread_mutex_destroy(&all->philo[i].l_meal);
		//error = pthread_mutex_destroy(&fork[i]);
		if(error != 0)
		{
			fprintf(stderr, "%d\n", error);
			ft_print_error(8);
			return ;
		}
		i++;
	}
	// TRES BIZARE A CHECKER !!!!!!
	//free(&all->philo->l_meal);
	//free(fork);
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
		error = pthread_mutex_unlock(&all->philo[i].l_meal);
		if(error != 0)
		{
			fprintf(stderr, "unlock -------------- %d\n", error);
		}
		i++;
	}
}

void	ft_clean_all(t_global *all)
{
	write(1, "cleaning all\n", 13);
	sleep(1);
	unlock_all(all);
	sleep(1);
	if (all->fork)
		destroy_fork(all->fork, all);
	destroy_meal(all);
	pthread_mutex_destroy(&all->print);
	pthread_mutex_destroy(&all->check);
	//free(&all->philo->l_meal);
	free(all->philo);
	//destroy le print
	// a remplir
}