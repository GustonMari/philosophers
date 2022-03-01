/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:58:13 by gmary             #+#    #+#             */
/*   Updated: 2022/03/01 10:20:54 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_is_dead(t_philo *philo)
{
	if (philo->all->dead == DEAD)
	{
		pthread_mutex_unlock(&philo->all->check);
		return (1);
	}
	if (philo->all->dead == ALIVE)
	{
		if (ft_time() - philo->t_lmeal >= philo->all->t_die)
		{
			philo->all->dead = DEAD;
			ft_sleep_t(4);
			print(philo, 2);
			pthread_mutex_unlock(&philo->all->check);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->all->check);
	return (0);
}

int	ft_check_death(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	ft_sleep_t(8);
	while (i < philo->all->nb_phil)
	{
		pthread_mutex_lock(&philo->all->check);
		if (ft_is_dead(&philo[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_all_dead(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < philo->all->nb_phil)
	{
		pthread_mutex_lock(&philo->all->check);
		philo->all->dead = DEAD;
		philo[i].all->dead = DEAD;
		i++;
		pthread_mutex_unlock(&philo->all->check);
	}
	return (0);
}

int	ft_check_meal(t_philo *philo)
{
	unsigned int	i;
	unsigned int	eat;

	i = 0;
	eat = 0;
	while (i < philo->all->nb_phil)
	{
		pthread_mutex_lock(&philo->all->check);
		if (philo[i].count >= philo->all->nb_eat && (philo->all->nb_eat > 0))
		{
			eat++;
		}
		pthread_mutex_unlock(&philo->all->check);
		if (eat == philo->all->nb_phil)
		{
			printf("everyone ate!");
			return (1);
		}
		i++;
	}
	return (0);
}
