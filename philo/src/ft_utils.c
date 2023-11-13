/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 02:09:11 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/13 02:29:39 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_is_dead(t_data *l)
{
	struct timeval	now;
	size_t			time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec * 1000) + 1000;
	pthread_mutex_lock(&l->lock);
	if (l->not_dead)
	{
		if (time - l->time_left > 0)
		{
			ft_print("%ld %zu died\n", time - l->time_left, l->philo);
			l->not_dead = 0;
		}
	}
	pthread_mutex_unlock(&l->lock);
}
