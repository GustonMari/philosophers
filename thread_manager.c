/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:55:35 by gmary             #+#    #+#             */
/*   Updated: 2022/04/20 09:31:48 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_all_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->check);
	if (philo->all->dead == DEAD)
	{
		pthread_mutex_unlock(&philo->all->check);
		return (DEAD);
	}
	pthread_mutex_unlock(&philo->all->check);
	return (ALIVE);
}

int	ft_actions(t_philo *philo)
{
	if (ft_take_fk(philo))
		return (-1);
	if (ft_eat(philo))
		return (-1);
	if (ft_drop_fk(philo))
		return (-1);
	if ((philo->all->nb_eat <= philo->count && philo->all->nb_eat > 0))
		return (-1);
	if (is_all_dead(philo) == DEAD)
		return (-1);
	if (ft_sleep(philo))
		return (-1);
	if (is_all_dead(philo) == DEAD)
		return (-1);
	return (0);
}

void	*routine_phil(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	if (philo->all->nb_phil == 1)
	{
		print(philo, 1);
		ft_sleep_t(philo->all->t_die);
		//print(philo, 2);
		return (NULL);
	}
	if (philo->index % 2 == 0)
		ft_sleep_t(10);
	while (1)
	{
		pthread_mutex_lock(&philo->all->check);
		if (philo->all->dead == ALIVE)
		{
			pthread_mutex_unlock(&philo->all->check);
			if (ft_actions(philo) == -1)
				break ;
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
		ft_sleep_t(1);
		if ((all->nb_eat > 0) && ft_check_meal(all->philo))
			ft_all_dead(all->philo);
		if (ft_check_death(all->philo))
			ft_all_dead(all->philo);
	}
	i = 0;
	while (i < all->nb_phil)
	{
		pthread_join(all->philo[i].thread, NULL);
		i++;
	}
	return (0);
}
