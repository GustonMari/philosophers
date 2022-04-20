/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:04:45 by gmary             #+#    #+#             */
/*   Updated: 2022/04/20 09:24:46 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_drop_fk(t_philo *philo)
{
	if (philo->all->nb_phil == 1)
	{
		pthread_mutex_unlock(&philo->all->fork[0]);
		return (0);
	}
	pthread_mutex_unlock(&philo->all->fork[(philo->index)
		% philo->all->nb_phil]);
	pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
	return (0);
}

int	is_dead_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->check);
	if (philo->all->dead == DEAD)
	{
		pthread_mutex_unlock(&philo->all->check);
		pthread_mutex_unlock(&philo->all->fork[(philo->index)
			% philo->all->nb_phil]);
		pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
		return (DEAD);
	}
	pthread_mutex_unlock(&philo->all->check);
	return (ALIVE);
}

int	ft_eat(t_philo *philo)
{
	if (is_dead_eat(philo) == DEAD)
		return (1);
	if (philo->all->nb_phil == 1)
	{
		return (0);
	}
	if (philo->all->nb_eat <= philo->count && philo->all->nb_eat > 0)
	{
		pthread_mutex_unlock(&philo->all->fork[(philo->index)
			% philo->all->nb_phil]);
		pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
		return (1);
	}
	pthread_mutex_lock(&philo->all->check);
	philo->count += 1;
	print(philo, 3);
	philo->t_lmeal = ft_time();
	pthread_mutex_unlock(&philo->all->check);
	ft_sleep_t_bis(philo->all->t_eat, philo);
	return (0);
}

int	ft_take_fk(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->check);
	if (philo->all->dead == DEAD || (philo->all->nb_eat <= philo->count
			&& philo->all->nb_eat > 0))
		return (1);
	pthread_mutex_unlock(&philo->all->check);
	if (philo->all->nb_phil == 1)
	{
		pthread_mutex_lock(&philo->all->fork[0]);
		print(philo, 1);
		return (0);
	}
	if (philo->all->nb_phil > 1)
	{
		if (ft_fk_left(philo) == 1)
			return (1);
		print(philo, 1);
		if (ft_fk_right(philo) == 1)
			return (1);
		print(philo, 1);
	}
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->check);
	if (philo->all->dead == DEAD)
		return (1);
	pthread_mutex_unlock(&philo->all->check);
	print(philo, 5);
	ft_sleep_t_bis(philo->all->t_sleep, philo);
	pthread_mutex_lock(&philo->all->check);
	if (philo->all->dead == DEAD)
	{
		pthread_mutex_unlock(&philo->all->check);
		return (1);
	}
	pthread_mutex_unlock(&philo->all->check);
	print(philo, 6);
	return (0);
}

/* int	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->check);
	if (philo->all->dead == DEAD)
		return (1);
	pthread_mutex_unlock(&philo->all->check);
	print(philo, 5);
	ft_sleep_t(philo->all->t_sleep);
	print(philo, 6);
	//ft_sleep_t((philo->all->t_eat - philo->all->t_sleep));
	return (0);
} */
