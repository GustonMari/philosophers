/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:55:35 by gmary             #+#    #+#             */
/*   Updated: 2022/01/31 15:36:32 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_death(t_philo *philo)
{
	while(philo->dead == 0)
	{
		pthread_mutex_lock(&philo->l_meal);
//		if (philo.start - ft_time() > philo.info->t_die)
		if (philo->t_lmeal - ft_time() > philo->info->t_die)
		{
			print(philo, 2);
			//printf("philo died");
			pthread_mutex_unlock(&philo->l_meal);
			philo->dead = 1;
			//peut etre plus exit quon devrait utiliser ??
			return (0);
		}
		pthread_mutex_unlock(&philo->l_meal);
	}
	return (0);
}

void	ft_drop_fk(t_philo *philo)
{
	pthread_mutex_unlock(&philo->all->fork[philo->index]);
	print(philo, 1);
	pthread_mutex_unlock(&philo->all->fork[(philo->index + 1) % philo->info->nb_phil]);
	print(philo, 1);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_meal);
	philo->t_lmeal = ft_time();
	//inclure un check dead ici ??
	philo->count += 1;
	print(philo, 3);
	usleep(philo->info->t_eat * 1000);
	pthread_mutex_unlock(&philo->l_meal);
}

void	ft_take_fk(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->fork[philo->index]);
	print(philo, 1);
	pthread_mutex_lock(&philo->all->fork[(philo->index + 1) % philo->info->nb_phil]);
	print(philo, 1);
}

void	*routine_(t_philo *philo)
{
	//bizare la double imbrication na pas lair de fonctionee
	while (philo->all->dead == 0)
	{
		//ft_take_fk(philo);
		//ft_eat(philo);
		//cree une condi en plus pour si ce n'est pas specifie
		if(philo->info->nb_eat <= philo->count)
			break ;
		//ft_drop_fk();
		//ft_sleep();
	}
	return (NULL);
}

//IL FAUT CREE UNE STRUCT STATE AVEC DDS MES PHILOS ET SI LON EST VIVANT OU PAS 
// POUR AVOIR UN VARIABLE DEAD COMMUN A TOUS MES PHILOS

int	ft_dispatch(t_global *all)
{
	//pthread_t		th;
	unsigned int	i;

	i = 0;
	while (i < all->nb_phil)
	{
		//if (pthread_create(&philo[i].thread, NULL, &ft_check_death, (void *)&philo[i]))
		//	return(2);
		i++;
	}
	i = 0;
	while (i < all->nb_phil)
	{
		//pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}