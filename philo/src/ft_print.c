/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:29:02 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/14 00:43:24 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_time	ft_checktime(t_time	time)
{
	struct timeval	now;
	t_time			now2;

	gettimeofday(&now, NULL);
	now2 = (now.tv_sec * 1000) + (now.tv_usec / 1000); 
	return (now2 - time);
}

void	ft_print(char *str, t_data *l)
{
	struct timeval	now;
	t_time			time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	pthread_mutex_lock(&l->lock);
	if (l->not_dead)
		printf("%lld %llu %s\n", time - l->time, l->philo, str);
	pthread_mutex_unlock(&l->lock);
}
