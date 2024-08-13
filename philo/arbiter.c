/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 05:00:50 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/13 05:36:20 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

bool	check_death(t_philo *philos)
{
	t_data	*data;

	data = philos->context;
	pthread_mutex_lock(&philos->context->death_mutex);
	if (philos->context->death_flag != -2
		&& philos->context->death_flag != -1)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %lld died\n",
			my_gettime() - data->start_time, data->death_flag);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&philos->context->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philos->context->death_mutex);
	return (false);
}

bool	check_meals_(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->context->meal_mutex);
	if (philo->eat_count == -1)
	{
		pthread_mutex_unlock(&philo->context->meal_mutex);
		return (false);
	}
	i = 0;
	while (i < philo->context->philo_count)
	{
		if (philo->context->philos[i].eat_count != -1
			&& philo->context->philos[i].eat_count > 0)
		{
			pthread_mutex_unlock(&philo->context->meal_mutex);
			return (false);
		}
		i++;
	}
	philo->context->done_eating = true;
	pthread_mutex_lock(&philo->context->death_mutex);
	philo->context->death_flag = -2;
	pthread_mutex_unlock(&philo->context->death_mutex);
	pthread_mutex_unlock(&philo->context->meal_mutex);
	return (true);
}
