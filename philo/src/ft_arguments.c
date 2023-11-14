/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arguments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:05:45 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/14 22:57:24 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_time	ft_atoi(char *str)
{
	t_time	res;
	int		i;

	res = 0;
	i = 0;
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

int	ft_verify_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_separate_arguments(int ac, char **av, t_data l)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_verify_number(av[i]))
			return (printf("Arguments with only numbers !\n"));
		i++;
	}
	l.nb_philo = ft_atoi(av[1]);
	l.t_to_die = ft_atoi(av[2]);
	l.t_to_eat = ft_atoi(av[3]);
	l.t_to_sleep = ft_atoi(av[4]);
	l.nb_meal_max = -1;
	if (ac == 6)
		l.nb_meal_max = ft_atoi(av[5]);
	return (0);
}
