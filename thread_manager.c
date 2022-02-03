/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:55:35 by gmary             #+#    #+#             */
/*   Updated: 2022/02/03 13:59:39 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



/*
	ici jai index - 1 et index (et pas index et index + 1 % nb_phil
	tout simplement car l'index commence a 1
*/
int	ft_drop_fk(t_philo *philo)
{
	if (philo->all->nb_phil == 1)
	{
		pthread_mutex_unlock(&philo->all->fork[0]);
		print(philo, 4);
		return (0) ;
	}
	if (philo->all->dead == DEAD)
		return (1);
	pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
	print(philo, 4);
	pthread_mutex_unlock(&philo->all->fork[(philo->index) % philo->all->nb_phil]);
	print(philo, 4);
	if (philo->all->dead == DEAD)
		return (1);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_meal);
	if (philo->all->dead == DEAD)
	{
		pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
		pthread_mutex_unlock(&philo->all->fork[(philo->index) % philo->all->nb_phil]);
		return (1);
	}
	if (philo->all->nb_phil == 1)
	{
		pthread_mutex_unlock(&philo->l_meal);
		return (0);
	}
	if (philo->all->nb_eat <= philo->count && philo->all->nb_eat > 0)
	{
		pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
		pthread_mutex_unlock(&philo->all->fork[(philo->index) % philo->all->nb_phil]);
		return (1);
	}
	//inclure un check dead ici ??
	//philo->t_lmeal = ft_time();
	//philo->t_lmeal = ft_time();
	philo->count += 1;
	print(philo, 3);
	philo->t_lmeal = ft_time();
	ft_sleep_t(philo->all->t_eat);
	//usleep(philo->all->t_eat * 1000);
	pthread_mutex_unlock(&philo->l_meal);
	return (0);
}

int	ft_take_fk(t_philo *philo)
{
	//if (philo->all->dead == DEAD)
	if (philo->all->dead == DEAD || philo->all->nb_eat <= philo->count)
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
		if (philo->all->dead == DEAD || philo->all->nb_eat <= philo->count)
		{
			pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
			return (1);
		}
		print(philo, 1);
		pthread_mutex_lock(&philo->all->fork[(philo->index) % philo->all->nb_phil]);
		if (philo->all->dead == DEAD || philo->all->nb_eat <= philo->count)
		{
			pthread_mutex_unlock(&philo->all->fork[philo->index - 1]);
			pthread_mutex_unlock(&philo->all->fork[(philo->index) % philo->all->nb_phil]);
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

	//usleep(philo->all->t_sleep * 1000);
	return (0);
}

//le pgm continue de tourner lorsque || philo->all->nb_eat <= philo->count est en condition

void	*routine_phil(void *content)
{
	t_philo	*philo;
	//unsigned int i = 0;

	philo = (t_philo *)content;
	if (philo->index % 2 == 0)
		usleep(100);
		//usleep(200);
		//usleep(1000);
	//fprintf(stderr, "after\n");
	while (philo->all->dead == ALIVE)
	{
		//fprintf(stderr, "i =%d\n", i);
		//if (philo->all->dead == DEAD || philo->all->nb_eat <= philo->count)
		//	break ;
		if (ft_take_fk(philo))
			break ;
		//fprintf(stderr, "2 i =%d\n", i);
		//if (philo->all->dead == DEAD)
		//	break ;
		//unlock fork dans eat ou cas ou ou on aurait deja manger suffisament
		if (ft_eat(philo))
			break ;
		//if (philo->all->dead == DEAD)
		//	break ;
		if (ft_drop_fk(philo))
			break ;
		if(philo->all->nb_eat <= philo->count)
		{
			pthread_mutex_lock(&philo->all->print);
			fprintf(stderr, "miam regalade %d\n", philo->index);
			pthread_mutex_unlock(&philo->all->print);
			break ;
		}
		if (philo->all->dead == DEAD)
			break ;
		//cree une condi en plus pour si ce n'est pas specifie le nb de repas
		if (ft_sleep(philo))
			break ;
		if (philo->all->dead == DEAD)
			break ;
	}
	//fprintf(stderr, "i =%d\n", i);
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
		pthread_detach(all->philo[i].thread);
		//if (pthread_create(&philo[i].thread, NULL, &ft_check_death, (void *)&philo[i]))
		//	return(2);
		i++;
	}
	while (all->dead == ALIVE)
	{
		//ft_sleep_t(4);
		ft_sleep_t(2);
		//usleep(400);
		//pthread_mutex_lock(&all->check);
		if ((all->nb_eat > 0) && ft_check_meal(all->philo))
		{
			ft_all_dead(all->philo);
			break ;
		}
		//pthread_mutex_lock(&all->check);
		if(ft_check_death(all->philo))
		{
			fprintf(stderr, "yAYYYYYY");
			ft_all_dead(all->philo);
			break ;
		}
		//pthread_mutex_unlock(&all->check);
		//fprintf(stderr, "i =%d\n", i);
	}
	//i = 0;
	//fprintf(stderr, "before join\n");
	//while (i < all->nb_phil)
	//{
	//	if (pthread_join(all->philo[i].thread, NULL) != 0)
	//		ft_print_error(7);
	//	fprintf(stderr, "before\n");
	//	i++;
	//}
	return (0);
}
