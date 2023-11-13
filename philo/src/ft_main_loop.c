/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:16:50 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/14 00:42:09 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_look_fork(t_data *l)
{
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
		pthread_mutex_unlock(&l->lock);
		usleep(300);
	}
}

void	ft_loop(t_data *l)
{
	while (ft_is_dead(l))
	{
		pthread_mutex_lock(&l->mutex[l->right]);
		ft_print("Has taken a fork", l);
		usleep(50);
		pthread_mutex_lock(&l->mutex[l->left]);
		ft_print("Has taken a fork", l);
		ft_eating(l);
		pthread_mutex_unlock(&l->mutex[l->left]);
		pthread_mutex_unlock(&l->mutex[l->right]);
		ft_sleep(l);
		pthread_mutex_lock(&l->lock);
		if (!l->nb_ph_eat)
		{
			pthread_mutex_unlock(&l->lock);
			break ;
		}
		pthread_mutex_unlock(&l->lock);
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
	t->time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	t->time_left = t->time + t->t_to_die;
	if (t->philo % 2 != 0)
		usleep(1000);
	pthread_mutex_unlock(&t->lock);
	ft_loop(l);
	return (NULL);
}

void	ft_create_threads(t_data *l)
{
	t_time	i;

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
	printf("%lld\n", l->philo);
}
