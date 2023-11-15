/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:57:25 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/15 11:47:00 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
t_time	ft_atoll(char *nptr)
{
	int			i;
	int			sign;
	t_time	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - 48;
		i++;
	}
	return ((int)res * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	res;
	size_t	i;

	res = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (res / size != nmemb || res / nmemb != size)
		return (NULL);
	ptr = malloc(res);
	i = 0;
	if (ptr)
	{
		while (i < res)
		{
			*(unsigned char *)(ptr + i) = 0;
			i++;
		}
	}
	return (ptr);
}

void	init_all(t_both *b, char **argv, int i)
{
	b->l.t_to_die = ft_atoll(argv[2]);
	b->l.t_to_eat = ft_atoll(argv[3]);
	b->l.t_to_sleep = ft_atoll(argv[4]);
	pthread_mutex_init(&b->l.die, NULL);
	pthread_mutex_init(&b->l.start, NULL);
	b->philo = ft_calloc(b->l.nb_philo, sizeof(t_philo));
	while (++i < b->l.nb_philo)
	{
		b->philo[i].glb = &b->l;
		b->philo[i].pos = i;
		pthread_mutex_init(&b->philo[i].m_state, NULL);
		pthread_mutex_init(&b->philo[i].meal, NULL);
		pthread_mutex_init(&b->philo[i].last, NULL);
		pthread_mutex_init(&b->l.forks[i], NULL);
	}
	i = -1;
	while (++i < b->l.nb_philo)
	{
		if (i == 0)
			b->philo[i].left = &b->l.forks[b->l.nb_philo - 1];
		else
			b->philo[i].left = &b->l.forks[i - 1];
		b->philo[i].right = &b->l.forks[i];
	}
	b->l.time_start = get_time();
}

void	free_all(t_both *b)
{
	int	i;

	i = -1;
	pthread_mutex_unlock(&b->l.start);
	while (++i < b->l.nb_philo)
		pthread_join(b->philo[i].id, NULL);
	pthread_join(b->timer, NULL);
	i = -1;
	while (++i < b->l.nb_philo)
	{
		pthread_mutex_destroy(&b->philo[i].glb->forks[i]);
		pthread_mutex_destroy(&b->philo[i].m_state);
		pthread_mutex_destroy(&b->philo[i].meal);
		pthread_mutex_destroy(&b->philo[i].last);
	}
	pthread_mutex_destroy(&b->l.write);
	pthread_mutex_destroy(&b->l.start);
	pthread_mutex_destroy(&b->l.end);
	pthread_mutex_destroy(&b->l.die);
	free(b->l.forks);
	free(b->philo);
}

int	main(int argc, char **argv)
{
	t_both	b;
	int		i;

	if (argc < 5 || argc > 6 || argv[1][0] == '-' || argv[2][0] == '-'
		|| argv[3][0] == '-' || argv[4][0] == '-')
		return (printf("Invalid args\n"), -1);
	b.l.not_dead = 0;
	b.l.finished = 0;
	b.l.nb_meal_max = -1;
	b.l.nb_philo = (int) ft_atoll(argv[1]);
	b.l.forks = ft_calloc(b.l.nb_philo, sizeof(pthread_mutex_t));
	if (argc == 6)
		b.l.nb_meal_max = (int) ft_atoll(argv[5]);
	i = -1;
	pthread_mutex_init(&b.l.write, NULL);
	pthread_mutex_init(&b.l.end, NULL);
	init_all(&b, argv, i);
	while (++i < b.l.nb_philo)
		b.philo[i].last_meal = get_time();
	pthread_mutex_lock(&b.l.start);
	pthread_create(&b.timer, NULL, &ft_timer, &b);
	i = -1;
	while (++i < b.l.nb_philo)
		pthread_create(&b.philo[i].id, NULL, &ft_start, &b.philo[i]);
	return (free_all(&b), 0);
}