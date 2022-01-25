/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:09:12 by gmary             #+#    #+#             */
/*   Updated: 2022/01/25 15:52:18 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
/*
number_of_philosophers 
time_to_die =>ms since last meal or begin
time_to_eat =>ms hold 2 fork
time_to_sleep =>ms sleep
[number_of_times_each_philosopher_must_eat] => (simulation stop)

philo must be:
- timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died

A displayed state message should not be mixed up with another message

A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.
*/

void	print()

int	main(int ac, char **av)
{
	int check;
	pthread_t th;
	
	check = pthread_create(&th, NULL, &print, 4);
	if (check != 0)
	{
		write(2, "Error\n", 6);
	}
	pthread_exit(check);
}

