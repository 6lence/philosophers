/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:57:25 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/14 18:33:30 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_wrong_arguments(void)
{
	printf("Try arguments like:\n");
	printf("    ./philo number_of_philosophers | time_to_die | time_to_eat ");
	printf("| time_to_sleep | number_of_times_each_philosopher_must_eat ");
	printf("(last argument is optional)\n");
	printf("Of course, every time in milliseconds !\n");
	return (1);
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

void	ft_initiate(t_both *b)
{
	int	i;

	b->philo = ft_calloc(sizeof(t_philo), b->l.nb_philo)
	pthread_mutex_init(b->l.die, NULL);
	i = 0;
	while (i < b->l.nb_philo)
	{
		b->philo[i].info = &b->l;
		b->philo.pos = i;
		pthread_mutex_init(b->philo[i]->left, NULL);
		pthread_mutex_init(b->philo[i]->right, NULL);
		pthread_mutex_init(b->philo[i]->meal, NULL);
		b->philo[i]->last_meat = get_time();
		pthread_mutex_init(b->l.fork[i++], NULL);
	}
	i = 0;
	while (i < b->l.nb_philo)
	{
		if (i == 0)
			b->philo[i]->left = &b->l.fork[b->l.nb_philo - 1];
		else
			b->philo[i]->left = &b->l.fork[i - 1];
		b->philo[i]->right = &b->l.fork[i++];
	}
	b->l.time_start = get_time();
}

void	ft_end(t_data *l)
{
	int	i;

	i = 0;
	while (i < b->l.nb_philo)
	{
		pthread_mutex_destroy(b->philo[i]->left);
		pthread_mutex_destroy(b->philo[i]->right);
		pthread_mutex_destroy(b->philo[i]->meal);
		pthread_mutex_destroy(b->l.fork[i++]);
	}
	pthread_mutex_destroy(b->l.die);
	free(b->philo);
}

int	main(int ac, char **av)
{
	t_both	b;
	int		i;

	if (ac < 5 || ac > 6)
		return (ft_wrong_arguments());
	if (ft_separate_arguments(ac, av, &b.l))
		return (1);
	ft_initiate(&b);
	pthread_create(&b.timer_start, NULL, &ft_timer, b);
	i = 0;
	while (i < b.l.nb_philo)
		pthread_create(&b.philo[i]->id, NULL, &ft_routine, b);
	ft_end(&b);
	return (0);
}