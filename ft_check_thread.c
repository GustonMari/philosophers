/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:58:13 by gmary             #+#    #+#             */
/*   Updated: 2022/02/03 15:16:48 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//int	ft_check_death(void *args)
int	ft_is_dead(t_philo *philo)
{
	//t_philo *philo;

	//philo = (t_philo *)args;
	//usleep(700);
	if (philo->all->dead == DEAD)
		return (1);
	
	//fprintf(stderr, "------------------ %u %u\n", (ft_time() - philo->t_lmeal), philo->all->t_die);
	//pthread_mutex_lock(&philo->l_meal);
	//pthread_mutex_lock(&philo->check);
	if (philo->all->dead == ALIVE)
	{
		if (ft_time() - philo->t_lmeal >= philo->all->t_die)
		{
			//fprintf(stderr, "%u %u\n", (ft_time() - philo->t_lmeal), philo->all->t_die);
			philo->all->dead = DEAD;
			usleep(800);
			print(philo, 2);
			//pthread_mutex_unlock(&philo->check);
			//pthread_mutex_unlock(&philo->l_meal);
			//philo->all->dead = DEAD;
			//peut etre plus exit quon devrait utiliser ??
			return (1);
		}
	}
	//pthread_mutex_unlock(&philo->check);
	//pthread_mutex_unlock(&philo->l_meal);
	return (0);
}

int	ft_check_death(t_philo *philo)
{
	unsigned int	i = 0;

	ft_sleep_t(7);
	//usleep(700);
	while (i < philo->all->nb_phil)
	{
		if (ft_is_dead(&philo[i]))
			return (1);
		//if (philo[i].all->dead == DEAD)
		//	return (1);
		i++;
	}
	return (0);
}

void	ft_all_dead(t_philo *philo)
{
	unsigned int	i = 0;
	//pthread_mutex_unlock(&philo->check);
	while (i < philo->all->nb_phil)
	{
		philo->all->dead = DEAD;
		philo[i].all->dead = DEAD;
		i++;
	}
	//pthread_mutex_unlock(&philo->check);
}

int	ft_check_meal(t_philo *philo)
{
	unsigned int i = 0;
	unsigned int eat = 0;

	while (i < philo->all->nb_phil)
	{
		if (philo[i].count >= philo->all->nb_eat)
		{
			eat++;
			//fprintf(stderr, "eat %d\n", eat);
		}
		if (eat == philo->all->nb_phil)
		{
			pthread_mutex_lock(&philo->all->print);
			write(1, "everyone ate!\n", 14);
			fprintf(stderr, "IN-----------------------\n");
			pthread_mutex_unlock(&philo->all->print);
			return (1);
		}
		i++;
	}
	return (0);
}
