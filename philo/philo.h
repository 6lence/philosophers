/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:33:09 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/14 17:44:12 by mescobar         ###   ########.fr       */
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

typedef long int	t_time;

typedef struct	s_philo
{
	int						pos;
	pthread_t				id;
	pthread_mutex_t			left;
	pthread_mutex_t			right;
	pthread_mutex_t			meal;
	t_time					last_meal;
	t_data					*glb;
}							t_philo;

typedef struct s_data
{
	pthread_mutex_t		*fork;
	pthread_mutex_t		*die;
	pthread_mutex_t		*nb_meal;
	pthread_mutex_t		*write;
	pthread_t			timer;
	t_time				nb_philo;
	t_time				t_to_die;
	t_time				t_to_eat;
	t_time				t_to_sleep;
	t_time				nb_meal_max;
	int					*not_dead;
}						t_data;

typedef struct	s_both
{
	struct s_philo	*philo;
	struct s_data	l;
	t_time			time_start;
}					t_both;

/* ft_args_utils */
int		ft_separate_arguments(int ac, char **av, t_data *l);
int		ft_verify_number(char *str);
t_time	ft_atoi(char *str);

/*	ft_main_loop  */
void	ft_look_fork(t_data *l);
void	ft_time(t_data *l);
void	ft_loop(t_data l);
void	*ft_routine(void *l);
void	ft_create_threads(t_data *l);

/*	ft_print  */
t_time	ft_checktime(t_time	time);
void	ft_print(char *str, t_data l);

/*	ft_utils  */
void	ft_eating(t_data *l);
void	ft_is_dead(t_data *l);
void	ft_sleep(t_data *l);

#endif