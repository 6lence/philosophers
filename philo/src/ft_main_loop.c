/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:16:50 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/13 02:29:41 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_look_fork(t_data *l)
{
	if (l->philo % 2 == 1)
		usleep(1);
	pthread_mutex_lock(&l->lock);
	if (l->philo % 2 == 0)
	{
		l->left = l->philo + 1;
		l->right = l->philo;
		if (l->philo == l->nb_philo)
			l->right = 1;
	}
	else
	{
		l->left = l->philo;
		l->right = l->philo + 1;
		if (l->philo == l->nb_philo)
			l->left = 1;
	}
	pthread_mutex_unlock(&l->lock);
}

void	ft_time(t_data *l)
{
	while (1)
	{
		pthread_mutex_lock(&l->lock);
		if (ft_checktime(l->time) >= 1000)
		{
			pthread_mutex_unlock(&l->lock);
			break ;
		}
		else
			pthread_mutex_unlock(&l->lock);
		usleep(300);
	}
}

void	ft_loop(t_data *l)
{
	while (ft_is_death(l))
	{
		pthread_mutex_lock(l->pid[l->right]);
		ft_print("Has taken a fork", l);
		pthread_mutex_lock(l->pid[l->left]);
		ft_printf("Has taken a fork", l);
		ft_eating(l);
	}
}

void	*ft_routine(void *l)
{
	struct timeval	now;
	t_data			*t;

	t = (t_data *)l;
	ft_look_fork(t);
	ft_time(t);
	pthread_mutex_lock(&t->lock);
	gettimeofday(&now, NULL);
	t->time_left = (now.tv_sec * 1000) + (now.tv_usec * 1000) + 1000;
	t->time_left += l->t_to_die;
	pthread_mutex_unlock(&t->lock);
	ft_loop(l);
	return (NULL);
}

void	ft_create_threads(t_data *l)
{
	size_t	i;

	i = 0;
	l->philo = 0;
	while (i < l->nb_philo)
	{
		pthread_create(&l->pid[i], NULL, ft_routine, l);
		pthread_mutex_lock(&l->lock);
		i++;
		l->philo++;
		pthread_mutex_unlock(&l->lock);
	}
	i = 0;
	while (i < l->nb_philo)
		pthread_join(l->pid[i++], NULL);
	printf("%ld\n", l->philo);
}
