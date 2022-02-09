/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:04:45 by gmary             #+#    #+#             */
/*   Updated: 2022/02/09 18:28:32 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*
int	ft_drop_fk(t_philo *philo)
{
	if (philo->all->nb_phil == 1)
	{
		pthread_mutex_unlock(&philo->all->fork[0]);
		//print(philo, 4);
		return (0);
	}
	pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
	//print(philo, 4);
	pthread_mutex_unlock(&philo->all->fork[(philo->index)
		% philo->all->nb_phil]);
	//print(philo, 4);
	if (philo->all->dead == DEAD)
		return (1);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (philo->all->dead == DEAD)
	{
		pthread_mutex_unlock(&philo->all->fork[(philo->index)
			% philo->all->nb_phil]);
		pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
		//pthread_mutex_unlock(&philo->l_meal);
		return (1);
	}
	if (philo->all->nb_phil == 1)
	{
		//pthread_mutex_unlock(&philo->l_meal);
		return (0);
	}
	if (philo->all->nb_eat <= philo->count && philo->all->nb_eat > 0)
	{
		pthread_mutex_unlock(&philo->all->fork[(philo->index)
			% philo->all->nb_phil]);
		pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
		//pthread_mutex_unlock(&philo->l_meal);
		return (1);
	}
	pthread_mutex_lock(&philo->all->check);
	//pthread_mutex_lock(&philo->l_meal);
	philo->count += 1;
	print(philo, 3);
	philo->t_lmeal = ft_time();
	ft_sleep_t(philo->all->t_eat);
	//pthread_mutex_unlock(&philo->l_meal);
	pthread_mutex_unlock(&philo->all->check);
	return (0);
}

int	ft_take_fk(t_philo *philo)
{
	//fprintf(stderr, "DEAD%d\n", philo->all->dead);
	//fprintf(stderr, "nb_eat %d\n", philo->all->nb_eat);
	//fprintf(stderr, "count %d\n", philo->count);
	if (philo->all->dead == DEAD || (philo->all->nb_eat <= philo->count && philo->all->nb_eat > 0))
		return (1);
	if (philo->all->nb_phil == 1)
	{
		pthread_mutex_lock(&philo->all->fork[0]);
		print(philo, 1);
		return (0);
	}
	if (philo->all->nb_phil > 1)
	{
		//pthread_mutex_lock(&philo->all->fork[philo->index]);
		pthread_mutex_lock(&philo->all->fork[(philo->index)
			% philo->all->nb_phil]);
		if (philo->all->dead == DEAD || (philo->all->nb_eat <= philo->count && philo->all->nb_eat > 0))
		{
			pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
			return (1);
		}
		print(philo, 1);
		pthread_mutex_lock(&philo->all->fork[(philo->index - 1)]);
		if (philo->all->dead == DEAD || (philo->all->nb_eat <= philo->count && philo->all->nb_eat > 0))
		{
			pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
			pthread_mutex_unlock(&philo->all->fork[(philo->index)
				% philo->all->nb_phil]);
			return (1);
		}
		print(philo, 1);
	}
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (philo->all->dead == DEAD)
		return (1);
	print(philo, 5);
	ft_sleep_t(philo->all->t_sleep);
	return (0);
}
*/
int	ft_drop_fk(t_philo *philo)
{
	if (philo->all->nb_phil == 1)
	{
		pthread_mutex_unlock(&philo->all->fork[0]);
		//print(philo, 4);
		return (0);
	}
	//print(philo, 4);
	pthread_mutex_unlock(&philo->all->fork[(philo->index)
		% philo->all->nb_phil]);
	pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
	//print(philo, 4);
	//if (philo->all->dead == DEAD)
	//	return (1);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (philo->all->dead == DEAD)
	{
		pthread_mutex_unlock(&philo->all->fork[(philo->index)
			% philo->all->nb_phil]);
		pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
		//pthread_mutex_unlock(&philo->l_meal);
		return (1);
	}
	if (philo->all->nb_phil == 1)
	{
		//pthread_mutex_unlock(&philo->l_meal);
		return (0);
	}
	if (philo->all->nb_eat <= philo->count && philo->all->nb_eat > 0)
	{
		pthread_mutex_unlock(&philo->all->fork[(philo->index)
			% philo->all->nb_phil]);
		pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
		//pthread_mutex_unlock(&philo->l_meal);
		return (1);
	}
	
	pthread_mutex_lock(&philo->all->check);
	//pthread_mutex_lock(&philo->l_meal);
	philo->count += 1;
	print(philo, 3);
	philo->t_lmeal = ft_time();
	pthread_mutex_unlock(&philo->all->check);
	//pthread_mutex_unlock(&philo->l_meal);
	ft_sleep_t(philo->all->t_eat);
	return (0);
}

int	ft_take_fk(t_philo *philo)
{
	//fprintf(stderr, "DEAD%d\n", philo->all->dead);
	//fprintf(stderr, "nb_eat %d\n", philo->all->nb_eat);
	//fprintf(stderr, "count %d\n", philo->count);
	if (philo->all->dead == DEAD || (philo->all->nb_eat <= philo->count && philo->all->nb_eat > 0))
		return (1);
	if (philo->all->nb_phil == 1)
	{
		pthread_mutex_lock(&philo->all->fork[0]);
		print(philo, 1);
		return (0);
	}
	if (philo->all->nb_phil > 1)
	{
		pthread_mutex_lock(&philo->all->fork[philo->index - 1]);
		if (philo->all->dead == DEAD || (philo->all->nb_eat <= philo->count && philo->all->nb_eat > 0))
		{
			pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
			return (1);
		}
		print(philo, 1);
		pthread_mutex_lock(&philo->all->fork[(philo->index)
			% philo->all->nb_phil]);
		if (philo->all->dead == DEAD || (philo->all->nb_eat <= philo->count && philo->all->nb_eat > 0))
		{
			pthread_mutex_unlock(&philo->all->fork[(philo->index)
				% philo->all->nb_phil]);
			pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
			return (1);
		}
		print(philo, 1);
	}
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (philo->all->dead == DEAD)
		return (1);
	print(philo, 5);
	ft_sleep_t(philo->all->t_sleep);
	return (0);
}