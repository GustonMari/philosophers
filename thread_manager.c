/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:55:35 by gmary             #+#    #+#             */
/*   Updated: 2022/01/28 18:16:26 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_death(t_philo philo)
{
	while(philo.dead == 0)
	{
		pthread_mutex_lock(&philo.l_meal);
		if (philo.start - ft_time() > philo.info->t_die)
		{
			printf("philo died");
			pthread_mutex_unlock(&philo.l_meal);
			philo.dead = 1;
			//peut etre plus exit quon devrait utiliser ??
			return (0);
		}
		pthread_mutex_unlock(&philo.l_meal);
	}
	return (0);
}

//IL FAUT CREE UNE STRUCT STATE AVEC DDS MES PHILOS ET SI LON EST VIVANT OU PAS 
// POUR AVOIR UN VARIABLE DEAD COMMUN A TOUS MES PHILOS

int	ft_dispatch(t_global all)
{
	//pthread_t		th;
	unsigned int	i;

	i = 0;
	while (i < all.philo->info->nb_phil)
	{
		//if (pthread_create(&philo[i].thread, NULL, &ft_check_death, (void *)&philo[i]))
		//	return(2);
		i++;
	}
	i = 0;
	while (i < all.philo->info->nb_phil)
	{
		//pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}