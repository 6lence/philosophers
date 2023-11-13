/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:33:09 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/14 00:41:39 by mescobar         ###   ########.fr       */
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

typedef unsigned long long int	t_time;

typedef struct s_data
{
	t_time				philo;
	t_time				nb_philo;
	t_time				t_to_die;
	t_time				t_to_eat;
	t_time				t_to_sleep;
	t_time				nb_ph_eat;
	t_time				time;
	t_time				time_left;
	int					not_dead;
	int					left;
	int					right;
	pthread_t			*pid;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		lock;
}				t_data;

/* ft_args_utils */
int		ft_separate_arguments(int ac, char **av, t_data *l);
int		ft_verify_number(char *str);
t_time	ft_atoi(char *str);

/*	ft_main_loop  */
void	ft_look_fork(t_data *l);
void	ft_time(t_data *l);
void	ft_loop(t_data *l);
void	*ft_routine(void *l);
void	ft_create_threads(t_data *l);

/*	ft_print  */
t_time	ft_checktime(t_time	time);
void	ft_print(char *str, t_data *l);

/*	ft_utils  */
void	ft_eating(t_data *l);
int		ft_is_dead(t_data *l);
void	ft_sleep(t_data *l);

#endif