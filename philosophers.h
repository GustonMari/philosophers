/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:40:49 by gmary             #+#    #+#             */
/*   Updated: 2022/01/28 17:42:01 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define EAT 2
# define SLEEP 3
# define DIE 4


/*
			STRUCT
*/
typedef struct	s_info
{
	unsigned int	t_eat;
	unsigned int	t_die;
	unsigned int	t_sleep;
	unsigned int	nb_phil;
	unsigned int	nb_eat;
	unsigned int	f_left;
	unsigned int	f_right;
}				t_info;

typedef struct	s_philo
{
	int				var;
	int				index;
	double			eaten;
	pthread_t 		thread;
	t_info			*info;
	pthread_mutex_t	*fork;
	pthread_mutex_t	l_meal;
	int				start;
	struct timeval	begin;
	int				dead;
}				t_philo;

/*
			UTILS
*/

int	ft_atoi(const char *str);

/*
			TIME FUNCTION
*/
int	ft_time(void);

#endif