/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:44:31 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/13 04:56:05 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	mutex_massacre(t_data *data, int mutex_count, u_int8_t bit_flag)
{
	int	i;

	i = 0;
	if ((bit_flag >> 1) & 1)
	{
		while (i < mutex_count)
		{
			pthread_mutex_destroy(&data->forks[i].mutex);
			i++;
		}
	}
	if (bit_flag & 1)
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		pthread_mutex_destroy(&data->meal_mutex);
	}
}

void	destroy(t_data *data, t_philo *philos)
{
	mutex_massacre(data, data->philo_count, ALL_MUTEXES);
	free(data->forks);
	free(philos);
}
