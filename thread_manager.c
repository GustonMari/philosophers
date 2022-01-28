/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:55:35 by gmary             #+#    #+#             */
/*   Updated: 2022/01/28 17:40:06 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_death(t_philo philo)
{
	while(philo.dead == 0)
	{
		pthread_mutex_lock(philo.l_meal);
		if (philo.t_start - ft_time() >philo->info.t_die)
		{
			printf("philo died");
			pthread_mutex_unlock(philo.l_meal);
			philo.dead == 1;
			//peut etre plus exit quon devrait utiliser ??
			return (0);
		}
		pthread_mutex_unlock(philo.l_meal);
	}
	return (0);
}

int	ft_dispatch(t_philo philo)
{
	//pthread_t	th;

	while (i < philo.info->nb_phil)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_check_death, (void *)&philo[i]))
			return(2);
		i++;
	}
	i = 0;
	while (i < philo.info->nb_phil)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}