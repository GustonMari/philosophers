/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:43:08 by gmary             #+#    #+#             */
/*   Updated: 2022/04/20 09:26:32 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	ft_sleep_t(size_t ms)
{
	unsigned int	curr;
	unsigned int	end;

	curr = ft_time();
	end = curr + ms;
	while (ft_time() < end)
		usleep(10);
}

void	ft_sleep_t_bis(size_t ms, t_philo *philo)
{
	unsigned int	curr;
	unsigned int	end;

	curr = ft_time();
	end = curr + ms;
	while (ft_time() < end)
	{
		if (philo->all->dead == DEAD)
			break ;
		usleep(10);
	}
}
