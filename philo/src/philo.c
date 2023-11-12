/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:32:48 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/12 23:23:53 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_wrong_arguments(void)
{
	printf("Try arguments like:\n");
	printf("    ./philo number_of_philosophers | time_to_die | time_to_eat ");
	printf("| time_to_sleep | number_of_times_each_philosopher_must_eat ");
	printf("(last argument is optional)\n");
	printf("Of course, every time in milliseconds !\n");
	return (1);
}

void	ft_initiate(t_data *l)
{
	l->pid = malloc(sizeof(pthread_t) * l->nb_philo);
}

int	main(int ac, char **av)
{
	t_data	l;

	if (ac < 5 || ac > 6)
		return (ft_wrong_arguments());
	if (ft_separate_arguments(ac, av, &l))
		return (1);
	ft_initiate(&l);
	ft_create_threads(&l);
	return (0);
}
