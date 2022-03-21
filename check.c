/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmary <gmary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:48:12 by gmary             #+#    #+#             */
/*   Updated: 2022/03/21 09:48:22 by gmary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_2(char **av)
{
	if (!*av[1])
		return (0);
	if (!*av[2])
		return (0);
	if (!*av[3])
		return (0);
	if (!*av[4])
		return (0);
	return (1);
}

int	check(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (!check_2(av))
		return (0);
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
