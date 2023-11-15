/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arguments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:05:45 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/15 11:56:21 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_time	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_print(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_state);
	pthread_mutex_lock(&philo->glb->write);
	if (philo->state == EAT)
		printf("%lu philo %d is eating.\n",
			get_time() - philo->glb->time_start, philo->pos + 1);
	else if (philo->state == SLEEP)
		printf("%lu philo %d is sleeping.\n",
			get_time() - philo->glb->time_start, philo->pos + 1);
	else if (philo->state == THINK)
		printf("%lu philo %d is thinking.\n",
			get_time() - philo->glb->time_start, philo->pos + 1);
	else if (philo->state == 0 && !philo->glb->not_dead)
	{
		pthread_mutex_lock(&philo->glb->die);
		philo->glb->not_dead += 1;
		pthread_mutex_unlock(&philo->glb->die);
		printf("%lu philo %d is dead.\n",
			get_time() - philo->glb->time_start, philo->pos + 1);
	}
	pthread_mutex_unlock(&philo->m_state);
	pthread_mutex_unlock(&philo->glb->write);
}
