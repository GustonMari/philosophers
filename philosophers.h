/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:40:49 by gmary             #+#    #+#             */
/*   Updated: 2022/02/09 18:08:05 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

# define EAT 2
# define SLEEP 3
# define DEAD 1
# define ALIVE 0

/*
			STRUCT
*/

typedef struct s_info
{
	unsigned int	t_eat;
	unsigned int	t_die;
	unsigned int	t_sleep;
	unsigned int	nb_phil;
	unsigned int	nb_eat;
}				t_info;

typedef struct s_philo
{
	int				var;
	int				index;
	double			eaten;
	pthread_t		thread;
	t_info			*info;
	pthread_mutex_t	l_meal;
	unsigned int	start;
	unsigned int	t_lmeal;
	struct timeval	begin;
	int				dead;
	unsigned int	count;
	struct s_global	*all;
}				t_philo;

typedef struct s_global
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
			TIME FUNCTION
*/

unsigned int	ft_time(void);
void			ft_sleep_t(size_t ms);

/*
			UTILS
*/

int				ft_atoi(const char *str);
void			print(t_philo *philo, int msg);
int				ft_isdigit(int c);

/*
			THREAD FUNCTION
*/
int				ft_dispatch(t_global *all);
int				ft_is_dead(t_philo *philo);
int				ft_check_death(t_philo *philo);
//void			ft_all_dead(t_philo *philo);
int				ft_all_dead(t_philo *philo);
int				ft_check_meal(t_philo *philo);
int				ft_sleep(t_philo *philo);
int				ft_take_fk(t_philo *philo);
int				ft_eat(t_philo *philo);
int				ft_drop_fk(t_philo *philo);

/*
			ERROR & CLEAN
*/

int				ft_print_error(int msg);
void			ft_clean_all(t_global **all);
int				unlock_all(t_global *all);
int				destroy_fork(pthread_mutex_t *fork, t_global *all);

#endif