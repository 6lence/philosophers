/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:16:50 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/12 22:47:13 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	m = 0;
pthread_mutex_t mutex;

void	*ft_routine(void *l)
{
	t_data t;

	t = *(t_data*)l;
	pthread_mutex_lock(&mutex);
	printf("%ld\n", t.a);
	pthread_mutex_unlock(&mutex);
	return ((void *)0);
}

void	ft_create_threads(t_data *l)
{
	size_t	i;

	i = 0;
	l->a = 19;
	pthread_mutex_init(&mutex, NULL);
	while (i < l->nb_philo)
		pthread_create(&l->pid[i++], NULL, ft_routine, l);
	i = 0;
	while (i < l->nb_philo)
		pthread_join(l->pid[i++], NULL);
	pthread_mutex_destroy(&mutex);
	printf("%ld | %ld\n", l->a, l->nb_philo);
}
