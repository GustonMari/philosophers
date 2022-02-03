/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:55:35 by gmary             #+#    #+#             */
/*   Updated: 2022/02/03 17:06:29 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine_phil(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	if (philo->index % 2 == 0)
		usleep(100);
	while (philo->all->dead == ALIVE)
	{
		if (ft_take_fk(philo))
			break ;
		if (ft_eat(philo))
			break ;
		if (ft_drop_fk(philo))
			break ;
		if (philo->all->nb_eat <= philo->count)
			break ;
		if (philo->all->dead == DEAD)
			break ;
		if (ft_sleep(philo))
			break ;
		if (philo->all->dead == DEAD)
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
			ft_print_error(5);
		pthread_detach(all->philo[i].thread);
		i++;
	}
	while (all->dead == ALIVE)
	{
		ft_sleep_t(2);
		if ((all->nb_eat > 0) && ft_check_meal(all->philo))
			return (ft_all_dead(all->philo));
		if (ft_check_death(all->philo))
			return (ft_all_dead(all->philo));
	}
	return (0);
}
