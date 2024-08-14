/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 05:00:50 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/14 14:02:13 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

bool	start_sim(t_data *data)
{
	if (!init_threads(data->philos))
		return (false);
	while (true)
	{
		usleep(1);
		if (check_death(data->philos) || check_meals(data->philos))
			break ;
	}
	join_threads(data->philos, data);
	return (true);
}

void	join_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

bool	check_death(t_philo *philos)
{
	int	i;
	int	philo_count;

	i = 0;
	philo_count = philos->context->philo_count;
	while (i < philo_count)
	{
		pthread_mutex_lock(&philos[i].context->meal_mutex);
		if ((my_gettime() - philos[i].last_eat) >= philos[i].time_to_die
			&& !philos[i].is_eating)
		{
			print_philo_status(&philos[i], "died");
			pthread_mutex_lock(&philos[i].context->death_mutex);
			philos[i].context->death_flag = true;
			pthread_mutex_unlock(&philos[i].context->death_mutex);
			pthread_mutex_unlock(&philos[i].context->meal_mutex);
			return (true);
		}
		pthread_mutex_unlock(&philos[i].context->meal_mutex);
		i++;
	}
	return (false);
}

bool	check_meals(t_philo *philos)
{
	int	i;
	int	philo_count;
	int	satisfied;

	if (philos->context->meal_amount == -1)
		return (false);
	i = 0;
	satisfied = 0;
	philo_count = philos->context->philo_count;
	while (i < philo_count)
	{
		pthread_mutex_lock(&philos[i].context->meal_mutex);
		if (philos[i].eat_count >= philos->context->meal_amount)
			satisfied++;
		pthread_mutex_unlock(&philos[i].context->meal_mutex);
		i++;
	}
	if (satisfied == philo_count)
	{
		pthread_mutex_lock(&philos->context->death_mutex);
		philos->context->death_flag = true;
		pthread_mutex_unlock(&philos->context->death_mutex);
		return (true);
	}
	return (false);
}
