/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mescobar <mescobar42@student.42perpigna    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:29:02 by mescobar          #+#    #+#             */
/*   Updated: 2023/11/13 02:29:42 by mescobar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_checktime(size_t	time)
{
	struct timeval	now;
	int				now2;

	gettimeofday(&now, NULL);
	now2 = (now.tv_sec * 1000) + (now.tv_usec * 1000) + 1000; 
	return (time - now2);
}

void	ft_printf(char *str, t_data *l);