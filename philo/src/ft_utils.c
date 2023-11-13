/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 02:09:11 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/14 00:42:59 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_eating(t_data *l)
{
	struct timeval	now;
	t_time			time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	ft_print("is eating", l);
	while (1)
	{
		usleep(100);
		ft_is_dead(l);
		pthread_mutex_lock(&l->lock);
		if (ft_checktime(time) >= l->t_to_eat)
		{
			pthread_mutex_unlock(&l->lock);
			break ;
		}
		pthread_mutex_unlock(&l->lock);
	}
	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	pthread_mutex_lock(&l->lock);
	l->time_left = time + l->t_to_die;
	l->nb_ph_eat--;
	pthread_mutex_unlock(&l->lock);
}

void	ft_sleep(t_data *l)
{
	struct timeval	now;
	t_time			time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	ft_print("is sleeping", l);
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&l->lock);
		if (ft_checktime(time) >= l->t_to_sleep)
		{
			pthread_mutex_unlock(&l->lock);
			break ;
		}
		pthread_mutex_unlock(&l->lock);
	}
	ft_print("is thinking", l);
}

int	ft_is_dead(t_data *l)
{
	struct timeval	now;
	t_time			time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	pthread_mutex_lock(&l->lock);
	if (l->not_dead)
	{
		if (time - l->time_left > 0)
		{
			printf("%lld %llu died\n", time - l->time_left, l->philo);
			return (0);
		}
	}
	pthread_mutex_unlock(&l->lock);
	return (1);
}
