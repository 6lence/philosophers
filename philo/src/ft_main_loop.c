/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:25:15 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/14 23:01:04 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_keep(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb->die);
	pthread_mutex_lock(&philo->meal);
	if (!philo->glb->die && (philo->glb->nb_meal == -1
			|| philo->meal < philo->glb->nb_meal_max))
		return (pthread_mutex_unlock(&philo->glb->die),
			pthread_mutex_unlock(&philo->meal), 1);
	pthread_mutex_lock(&philo->glb->end);
}

void	ft_eat(t_philo *philo)
{
	if (philo->pos % 2 == 0)
		ft_fork(philo, philo->left, philo->right, 0)
}

void	ft_start(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	while (ft_keep(philo))
	{
		ft_eat(philo);
		if (philo->left == philo->right || !ft_keep(philo))
			beak ;
		pthrear_mutex_lock(&philo->m_state);
		philo->state = SLEEP;
		pthread_mutex_unlock(&philo->m_state);
		print(philo, philo->state);
		usleep(philo->glb->t_to_sleep * 1000);
		if (!keep(philo))
			break ;
		pthread_mutex_lock(&philo->m_state);
		philo->state = THINK;
		pthread_mutex_unlock(&philo->m_state);
		print(philo, philo->m_state);
	}
	return (NULL);
}
