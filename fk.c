/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fk.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:55:10 by gmary             #+#    #+#             */
/*   Updated: 2022/04/19 13:10:03 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_fk_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->fork[philo->index - 1]);
	pthread_mutex_lock(&philo->all->check);
	if (philo->all->dead == DEAD || (philo->all->nb_eat <= philo->count
			&& philo->all->nb_eat > 0))
	{
		pthread_mutex_unlock(&philo->all->check);
		pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->check);
	return (0);
}

int	ft_fk_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->fork[(philo->index)
		% philo->all->nb_phil]);
	pthread_mutex_lock(&philo->all->check);
	if (philo->all->dead == DEAD || (philo->all->nb_eat <= philo->count
			&& philo->all->nb_eat > 0))
	{
		pthread_mutex_unlock(&philo->all->check);
		pthread_mutex_unlock(&philo->all->fork[(philo->index)
			% philo->all->nb_phil]);
		pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->check);
	return (0);
}

/* int	ft_fk_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->fork[philo->index - 1]);
	pthread_mutex_lock(&philo->all->check);
	if (philo->all->dead == DEAD || (philo->all->nb_eat <= philo->count
			&& philo->all->nb_eat > 0))
	{
		pthread_mutex_unlock(&philo->all->check);
		pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->check);
	return (0);
} */

/* int	ft_fk_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->fork[(philo->index)
		% philo->all->nb_phil]);
	pthread_mutex_lock(&philo->all->check);
	if (philo->all->dead == DEAD || (philo->all->nb_eat <= philo->count
			&& philo->all->nb_eat > 0))
	{
		pthread_mutex_unlock(&philo->all->check);
		pthread_mutex_unlock(&philo->all->fork[(philo->index)
			% philo->all->nb_phil]);
		pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->check);
	return (0);
} */
