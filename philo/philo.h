/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:33:09 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/15 11:39:21 by mescobar         ###   ########.fr       */
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

# define EAT 1
# define SLEEP 2
# define THINK 3

typedef struct s_philo
{
	int						pos;
	pthread_t				id;
	t_time					last_meal;
	int						state;
	int						eat;
	pthread_mutex_t			*left;
	pthread_mutex_t			*right;
	pthread_mutex_t			meal;
	pthread_mutex_t			last;
	pthread_mutex_t			m_state;
	struct s_data			*glb;
}							t_philo;

typedef struct s_data
{
	t_time				nb_philo;
	t_time				nb_meal_max;
	int					*not_dead;
	int					finished;
	t_time				t_to_die;
	t_time				t_to_eat;
	t_time				t_to_sleep;
	t_time				time_start;
	pthread_mutex_t		end; 
	pthread_mutex_t		start;
	pthread_mutex_t		write;
	pthread_mutex_t		die;
	pthread_mutex_t		*forks;
}						t_data;

typedef struct	s_both
{
	struct s_philo	*philo;
	struct s_data	l;
	pthread_t		timer;
}					t_both;

/* ft_args_utils */
t_time	get_time(void);
void	ft_print(t_philo *philo);
int		ft_separate_arguments(int ac, char **av, t_data *l);
int		ft_verify_number(char *str);
t_time	ft_atoi(char *str);

/*	ft_main_loop  */
void	*ft_timer(void *var);
void	*ft_start(void *var);
int		ft_keep(t_philo *philo);

#endif