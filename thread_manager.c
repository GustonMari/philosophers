/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:55:35 by gmary             #+#    #+#             */
/*   Updated: 2022/03/01 10:17:22 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine_phil(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	if (philo->index % 2 == 0)
		ft_sleep_t(1);
	while (1)
	{
		pthread_mutex_lock(&philo->all->check);
		if (philo->all->dead == ALIVE)
		{
			pthread_mutex_unlock(&philo->all->check);
			if (ft_take_fk(philo))
				break ;
			if (ft_eat(philo))
				break ;
			if (ft_drop_fk(philo))
				break ;
			if ((philo->all->nb_eat <= philo->count && philo->all->nb_eat > 0))
				break ;
			pthread_mutex_lock(&philo->all->check);
			if (philo->all->dead == DEAD)
			{
				pthread_mutex_unlock(&philo->all->check);
				break ;
			}
			pthread_mutex_unlock(&philo->all->check);
			if (ft_sleep(philo))
				break ;
			pthread_mutex_lock(&philo->all->check);
			if (philo->all->dead == DEAD)
			{
				pthread_mutex_unlock(&philo->all->check);
				break ;
			}
			pthread_mutex_unlock(&philo->all->check);
		}
		else
			break ;
	}
	return (NULL);
}

int	ft_dispatch(t_global *all)
{
	unsigned int	i;

	i = 0;
	while (i < all->nb_phil)
	{
		if (pthread_create(&all->philo[i].thread, NULL,
				&routine_phil, (void *)&all->philo[i]) != 0)
			return (ft_print_error(5));
		i++;
	}
	while (all->dead == ALIVE)
	{
		ft_sleep_t(2);
		if ((all->nb_eat > 0) && ft_check_meal(all->philo))
			ft_all_dead(all->philo);
		if (ft_check_death(all->philo))
			ft_all_dead(all->philo);
	}
	i = 0;
	while (i < all->nb_phil)
	{
		pthread_join(all->philo[i].thread,NULL);
		i++;
	}
	return (0);
}
