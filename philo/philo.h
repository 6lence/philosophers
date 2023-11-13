/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:33:09 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/13 02:29:40 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	size_t				philo;
	size_t				nb_philo;
	size_t				t_to_die;
	size_t				t_to_eat;
	size_t				t_to_sleep;
	size_t				nb_ph_eat;
	size_t				time;
	size_t				time_left;
	int					not_dead;
	int					left;
	int					right;
	pthread_t			*pid;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		lock;
}				t_data;

/* ft_args_utils */
int		ft_separate_arguments(int ac, char **av, t_data *l);
size_t	ft_atoi(char *str);

/*	ft_main_loop  */
void	ft_create_threads(t_data *l);

/*	ft_print  */
void	ft_print(char *str, t_data *l);

#endif