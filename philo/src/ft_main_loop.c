/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:25:15 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/15 11:57:24 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	nostop(t_philo *philo)
{
	pthread_mutex_lock(&philo->glb->die);
	pthread_mutex_lock(&philo->meal);
	if (!philo->glb->not_dead && (philo->glb->nb_meal_max == -1
			|| philo->eat < philo->glb->nb_meal_max))
		return (pthread_mutex_unlock(&philo->glb->die),
			pthread_mutex_unlock(&philo->meal),
			1);
	pthread_mutex_lock(&philo->glb->end);
	if (!philo->glb->not_dead && !(philo->glb->nb_meal_max == -1
			&& philo->eat < philo->glb->nb_meal_max))
		philo->glb->finished += 1;
	pthread_mutex_unlock(&philo->glb->end);
	return (pthread_mutex_unlock(&philo->glb->die),
		pthread_mutex_unlock(&philo->meal),
		0);
}

void	*ft_timer(void *ptr)
{
	t_both	*d;
	int		i;

	d = (t_both *)ptr;
	pthread_mutex_lock(&d->l.start);
	pthread_mutex_unlock(&d->l.start);
	while (!pthread_mutex_lock(&d->l.end)
		&& d->l.finished < d->l.nb_philo)
	{
		pthread_mutex_unlock(&d->l.end);
		i = -1;
		while (++i < d->l.nb_philo && !pthread_mutex_lock(&d->philo[i].last))
		{
			if (nostop(&d->philo[i]) && get_time()
				- d->philo[i].last_meal > d->l.t_to_die + 1)
				return (pthread_mutex_lock(&d->philo[i].m_state),
					d->philo[i].state = 0,
					pthread_mutex_unlock(&d->philo[i].m_state),
					ft_print(&d->philo[i]),
					pthread_mutex_unlock(&d->philo[i].last), (void *)0);
			pthread_mutex_unlock(&d->philo[i].last);
		}
	}
	pthread_mutex_unlock(&d->l.end);
	return ((void *)0);
}

void	ft_fork(t_philo *philo, pthread_mutex_t *a, pthread_mutex_t *b, int f)
{
	if (f && (!pthread_mutex_unlock(a) && (a != b && !pthread_mutex_unlock(b))))
		return ;
	pthread_mutex_lock(a);
	if (!nostop(philo) && !pthread_mutex_unlock(a))
		return ;
	pthread_mutex_lock(&philo->glb->write);
	printf("%lu philo %d has taken a fork\n",
		get_time() - philo->glb->time_start, philo->pos + 1);
	pthread_mutex_unlock(&philo->glb->write);
	if (a != b)
		pthread_mutex_lock(b);
	if ((a == b && !pthread_mutex_unlock(a)) || (!nostop(philo)
			&& !pthread_mutex_unlock(a) && !pthread_mutex_unlock(b)))
		return ;
	pthread_mutex_lock(&philo->glb->write);
	printf("%lu philo %d has taken a fork\n",
		get_time() - philo->glb->time_start, philo->pos + 1);
	pthread_mutex_unlock(&philo->glb->write);
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 1)
		ft_fork(philo, philo->left, philo->right, 0);
	else
		ft_fork(philo, philo->right, philo->left, 0);
	if (philo->left == philo->right || !nostop(philo))
		return ;
	pthread_mutex_lock(&philo->m_state);
	philo->state = EAT;
	pthread_mutex_unlock(&philo->m_state);
	if (!nostop(philo) && (!pthread_mutex_unlock(philo->left) && (philo->right
				!= philo->left && !pthread_mutex_unlock(philo->right))))
		return ;
	pthread_mutex_lock(&philo->last);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last);
	ft_print(philo);
	usleep(philo->glb->t_to_eat * 1000);
	if (philo->id % 2 == 1)
		ft_fork(philo, philo->left, philo->right, 1);
	else
		ft_fork(philo, philo->right, philo->left, 1);
	pthread_mutex_lock(&philo->meal);
	philo->eat++;
	pthread_mutex_unlock(&philo->meal);
}

void	*ft_start(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->glb->start);
	pthread_mutex_unlock(&philo->glb->start);
	while (nostop(philo))
	{
		ft_eat(philo);
		if (philo->left == philo->right || !nostop(philo))
			break ;
		pthread_mutex_lock(&philo->m_state);
		philo->state = SLEEP;
		pthread_mutex_unlock(&philo->m_state);
		ft_print(philo);
		usleep(philo->glb->t_to_sleep * 1000);
		if (!nostop(philo))
			break ;
		pthread_mutex_lock(&philo->m_state);
		philo->state = THINK;
		pthread_mutex_unlock(&philo->m_state);
		ft_print(philo);
	}
	return ((void *)0);
}
