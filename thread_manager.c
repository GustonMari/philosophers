/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:55:35 by gmary             #+#    #+#             */
/*   Updated: 2022/02/01 10:41:54 by gmary            ###   ########.fr       */
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
	if (philo->t_lmeal - philo->start >= philo->all->t_die)
		philo->all->dead = DEAD;
}

void	ft_take_fk(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->fork[philo->index]);
	print(philo, 1);
	pthread_mutex_lock(&philo->all->fork[(philo->index + 1) % philo->info->nb_phil]);
	print(philo, 1);
}

void	*routine_phil(void *content)
{
	t_philo	*philo;

	philo = content;
	if (philo->index % 2 == 0)
		usleep(1000);
	while (philo->all->dead == ALIVE)
	{
		ft_take_fk(philo);
		if (philo->all->dead == DEAD)
			break ;
		//ft_eat(philo);
		//cree une condi en plus pour si ce n'est pas specifie le nb de repas
		if(philo->info->nb_eat <= philo->count || philo->all->dead == DEAD)
			break ;
		//ft_drop_fk(philo);
		if (philo->all->dead == DEAD)
			break ;
		//ft_sleep();
		if (philo->all->dead == DEAD)
			break ;
	}
	return (NULL);
}

int	ft_dispatch(t_global *all)
{
	//pthread_t		th;
	unsigned int	i;

	i = 0;
	while (i < all->nb_phil)
	{
		//ft_take_fk(&all->philo[i]);
		if (pthread_create(&all->philo[i].thread, NULL, routine_phil, (void *)&all->philo[i]))
			ft_print_error(5);
		
		//if (pthread_create(&philo[i].thread, NULL, &ft_check_death, (void *)&philo[i]))
		//	return(2);

		i++;
	}
	i = 0;
	while (i < all->nb_phil)
	{
		pthread_join(all->philo[i].thread, NULL);
		i++;
	}
	return (0);
}