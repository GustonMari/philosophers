/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:09:12 by gmary             #+#    #+#             */
/*   Updated: 2022/01/25 17:22:55 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

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
////////////////////////////////////////////////////////////////////////
/*
exit on y mets null car on part du principe que create a marcher
son second paramètre, un pointeur, 
permet de récupérer la valeur retournée par la fonction dans laquelle s'exécute le thread

*/
void	*print(void	*nb)
{
	//(void)nb;
	printf("%d\n", *(int *)nb);
	pthread_exit(NULL);
}

int	main()
{
	int check = 6;
	pthread_t th;
	void	*nb;
	int	four= 4;
	nb = &four;
	
	check = pthread_create(&th, NULL, print, nb);
	if (check < 0)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	check = pthread_join(th, NULL);
	if (check < 0)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	return (0);
}

