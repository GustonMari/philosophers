/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:22:00 by gmary             #+#    #+#             */
/*   Updated: 2022/04/19 13:11:27 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long	nbr;

	nbr = n;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		nbr *= -1;
	}
	if (nbr >= 10)
		ft_putnbr((nbr / 10));
	ft_putchar(nbr % 10 + '0');
}

int	ft_print_error(int msg)
{
	if (msg == 1)
		write(2, "fork mutex failed to init\n", 26);
	if (msg == 2)
		write(2, "l_meal mutex failed to init\n", 28);
	if (msg == 3)
		write(2, "malloc failed to allocate\n", 26);
	if (msg == 4)
		write(2, "", 1);
	if (msg == 5)
		write(2, "mutex_create failed\n", 20);
	if (msg == 6)
		write(2, "print mutex failed to init\n", 27);
	if (msg == 7)
		write(2, "join failed\n", 12);
	if (msg == 8)
		write(2, "destroy mutex l_meal\n", 21);
	return (1);
}

void	print(t_philo *philo, int msg)
{
	pthread_mutex_lock(&philo->all->print);
	if (msg == 1)
		printf("%d %d has taken a fork\n",
			(ft_time() - (philo->start)), philo->index);
	if (msg == 2)
		printf("%d %d died\n",
			(ft_time() - (philo->start)), philo->index);
	if (msg == 3)
		printf("%d %d is eating\n",
			(ft_time() - (philo->start)), philo->index);
	if (msg == 4)
		printf("%d %d has drop a fork!\n",
			(ft_time() - (philo->start)), philo->index);
	if (msg == 5)
		printf("%d %d is sleeping\n",
			(ft_time() - (philo->start)), philo->index);
	if (msg == 6)
		printf("%d %d is thinking\n",
			(ft_time() - (philo->start)), philo->index);
	pthread_mutex_unlock(&philo->all->print);
}

/* void	print(t_philo *philo, int msg)
{
	//static int	stop_print = 0;

	pthread_mutex_lock(&philo->all->print);
	//if (stop_print == 1)
	//{
	//	pthread_mutex_unlock(&philo->all->print);
	//	return ;
	//}
	if (msg == 1)
		printf("%d %d has taken a fork!\n",
			(ft_time() - (philo->start)), philo->index);
	if (msg == 2)
		printf("%d %d is dead X_X!\n",
			(ft_time() - (philo->start)), philo->index);
	if (msg == 3)
		printf("%d %d is eating!\n",
			(ft_time() - (philo->start)), philo->index);
	if (msg == 4)
		printf("%d %d has drop a fork!\n",
			(ft_time() - (philo->start)), philo->index);
	if (msg == 5)
		printf("%d %d is sleeping!\n",
			(ft_time() - (philo->start)), philo->index);
	//if (msg == 2)
	//	stop_print = 1;
	pthread_mutex_unlock(&philo->all->print);
} */