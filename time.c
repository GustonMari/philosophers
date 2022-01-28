/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:43:08 by gmary             #+#    #+#             */
/*   Updated: 2022/01/28 17:56:25 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_chrono(void)
{
	struct timeval start;
	struct timeval end;
	gettimeofday(&start, NULL);
	usleep(15000);
	gettimeofday(&end, NULL);
	return ((end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec) / 1000));
}

unsigned int	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}
