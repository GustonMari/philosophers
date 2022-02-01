/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:55:35 by gmary             #+#    #+#             */
/*   Updated: 2022/02/01 15:20:48 by gmary            ###   ########.fr       */
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
//		if (philo.start - ft_time() > philo.info->t_die)
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

/*
	ici jai index - 1 et index (et pas index et index + 1 % nb_phil
	tout simplement car l'index commence a 1
*/
void	ft_drop_fk(t_philo *philo)
{
	pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
	print(philo, 4);
	pthread_mutex_unlock(&philo->all->fork[(philo->index) % philo->all->nb_phil]);
	print(philo, 4);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_meal);
	philo->t_lmeal = ft_time();
	//inclure un check dead ici ??
	philo->count += 1;
	print(philo, 3);
	usleep(philo->all->t_eat * 1000);
	pthread_mutex_unlock(&philo->l_meal);
}

void	ft_take_fk(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->fork[philo->index - 1]);
	print(philo, 1);
	pthread_mutex_lock(&philo->all->fork[(philo->index) % philo->all->nb_phil]);
	print(philo, 1);
}

int	ft_sleep(t_philo *philo)
{
	if (philo->all->dead == DEAD)
		return (1);
	usleep(philo->all->t_sleep * 1000);
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
//le pgm continue de tourner lorsque || philo->all->nb_eat <= philo->count est en condition

void	*routine_phil(void *content)
{
	t_philo	*philo;
	int i = 0;

	philo = (t_philo *)content;
	if (philo->index % 2 == 0)
		usleep(1000);
	//fprintf(stderr, "after\n");
	while (philo->all->dead == ALIVE)
	{
		//fprintf(stderr, "i =%d\n", i);
		ft_take_fk(philo);
		//fprintf(stderr, "2 i =%d\n", i);
		if (philo->all->dead == DEAD)
			break ;
		ft_eat(philo);
		ft_drop_fk(philo);
		if(philo->all->dead == DEAD)
		{
			pthread_mutex_lock(&philo->all->print);
			fprintf(stderr, "dead poto\n");
			pthread_mutex_unlock(&philo->all->print);
			break ;
		}
		if(philo->all->nb_eat <= philo->count)
		{
			pthread_mutex_lock(&philo->all->print);
			fprintf(stderr, "miam regalade %d\n", philo->index);
			pthread_mutex_unlock(&philo->all->print);
			break ;
		}
		//cree une condi en plus pour si ce n'est pas specifie le nb de repas
		ft_is_dead(philo);
		if(ft_check_death(philo))
			break ;
		if (ft_sleep(philo))
			break ;
		if (philo->all->dead == DEAD)
			break ;
		i++;
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
		if (pthread_create(&all->philo[i].thread, NULL, &routine_phil, (void *)&all->philo[i]) != 0)
			ft_print_error(5);
		//pthread_detach(all->philo[i].thread);
		//if (pthread_create(&philo[i].thread, NULL, &ft_check_death, (void *)&philo[i]))
		//	return(2);

		i++;
	}
	i = 0;
	while (i < all->nb_phil)
	{
		if (pthread_join(all->philo[i].thread, NULL) != 0)
			ft_print_error(7);
		fprintf(stderr, "before\n");
		i++;
	}
	return (0);
}