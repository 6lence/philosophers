/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:32:48 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/14 00:41:40 by mescobar         ###   ########.fr       */
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
	struct timeval	now;
	t_time			i;

	gettimeofday(&now, NULL);
	l->time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	l->time += 1000;
	l->pid = malloc(sizeof(pthread_t) * l->nb_philo);
	l->mutex = malloc(sizeof(pthread_mutex_t) * l->nb_philo);
	pthread_mutex_init(&l->lock, NULL);
	i = 0;
	while (i < l->nb_philo)
		pthread_mutex_init(&l->mutex[i++], NULL);
	l->not_dead = 1;
}

void	ft_end(t_data *l)
{
	t_time	i;

	i = 0;
	pthread_mutex_destroy(&l->lock);
	while (i < l->nb_philo)
		pthread_mutex_destroy(&l->mutex[i++]);
	free(l->pid);
	free(l->mutex);
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
	ft_end(&l);
	return (0);
}
