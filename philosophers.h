/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:40:49 by gmary             #+#    #+#             */
/*   Updated: 2022/02/02 18:03:02 by gmary            ###   ########.fr       */
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
# define DEAD 1
# define ALIVE 0


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
}				t_info;

typedef struct	s_philo
{
	int				var;
	int				index;
	double			eaten;
	pthread_t 		thread;
	t_info			*info;
	//pthread_mutex_t	*fork;
	pthread_mutex_t	check;
	pthread_mutex_t	l_meal;
	unsigned int	start;
	unsigned int	t_lmeal;
	struct timeval	begin;
	int				dead;
	unsigned int	count;
	struct s_global	*all;
}				t_philo;

//surement tej le mutex check en dans global

typedef struct	s_global
{
	int				dead;
	unsigned int	t_eat;
	unsigned int	t_die;
	unsigned int	t_sleep;
	unsigned int	nb_phil;
	unsigned int	nb_eat;
	unsigned int	f_left;
	unsigned int	f_right;
	unsigned int	start;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	check;
	t_philo			*philo;
}				t_global;

/*
			UTILS
*/

int	ft_atoi(const char *str);
void	print(t_philo *philo, int msg);

/*
			TIME FUNCTION
*/
unsigned int	ft_time(void);
void			ft_sleep_t(size_t ms);


/*
			THREAD FUNCTION
*/
int		ft_dispatch(t_global *all);
int		ft_is_dead(t_philo *philo);
int		ft_check_death(t_philo *philo);
void	ft_all_dead(t_philo *philo);
int		ft_check_meal(t_philo *philo);

/*
			ERROR & CLEAN
*/
void	ft_print_error(int	msg);


#endif