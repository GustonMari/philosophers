/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:22:00 by gmary             #+#    #+#             */
/*   Updated: 2022/01/31 12:05:54 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putchar(char c)
{
	write(1, &c ,1);
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

void	print(t_philo *philo, int msg)
{
	ft_putnbr(ft_time() - philo->start);
	write(1, "Philosopher ", 12);
	ft_putnbr(philo->index);
	if (msg == 1)
		write(1, " has taken a fork!\n", 19);
	if (msg == 2)
		write(1, " is dead X_X\n", 13);
	if (msg == 3)
		write(1, " is eating!\n", 12);
	
}