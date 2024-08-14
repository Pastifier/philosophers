/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:19:12 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/14 12:40:24 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	join_threads(t_philo *philos, t_data *data);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);

bool	start_sim(t_data *data)
{
	if (!init_threads(data->philos))
		return (false);
	// update loop goes here:
	while (true)
	{
		usleep(1);
		if (check_death(data->philos) || check_meals(data->philos))
			break ;
	}
	join_threads(data->philos, data);
	return (true);
}

void	*routine(void *phcontext)
{
	t_philo	*philo;

	philo = (t_philo *)phcontext;
	if (philo->context->philo_count == 1)
	{
		print_philo_status(philo, MSG_FORK);
		my_usleep(philo->time_to_die, philo);
		return (NULL);
	}
	if (philo->id % 2)
		my_usleep(50, philo);
	// update loop goes here:
	// while (!check_death_status(philo))
	return (NULL);
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

void	philo_eat(t_philo *philo)
{
	(void)philo;
}

void	philo_sleep(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");
	my_usleep(philo->time_to_sleep, philo);
	print_philo_status(philo, "is thinking");
}

bool	check_death_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->context->death_mutex);
	if (philo->context->death_flag)
	{
		pthread_mutex_unlock(&philo->context->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->context->death_mutex);
	return (false);
}
