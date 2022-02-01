/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:58:13 by gmary             #+#    #+#             */
/*   Updated: 2022/02/01 18:06:19 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//int	ft_check_death(void *args)
int	ft_is_dead(t_philo *philo)
{
	//t_philo *philo;

	//philo = (t_philo *)args;
	if (philo->all->dead == DEAD)
		return (1);
	pthread_mutex_lock(&philo->l_meal);
	if (philo->all->dead == ALIVE)
	{
		if (ft_time() - philo->t_lmeal >= philo->all->t_die)
		{
			print(philo, 2);
			pthread_mutex_unlock(&philo->l_meal);
			philo->all->dead = DEAD;
			//peut etre plus exit quon devrait utiliser ??
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->l_meal);
	return (0);
}

int	ft_check_death(t_philo *philo)
{
	unsigned int	i = 0;

	while (i < philo->all->nb_phil)
	{
		if (philo[i].all->dead == DEAD)
			return (1);
		i++;
	}
	return (0);
}

void	ft_all_dead(t_philo *philo)
{
	unsigned int	i = 0;

	while (i < philo->all->nb_phil)
	{
		philo->all->dead = DEAD;
		i++;
	}
}

int	ft_check_meal(t_philo *philo)
{
	unsigned int i = 0;
	unsigned int eat = 0;

	while (i < philo->all->nb_phil)
	{
		if (philo[i].count >= philo->all->nb_eat)
			eat++;
		if (eat == philo->all->nb_eat)
			return (1);
		i++;
	}
	return (0);
}

