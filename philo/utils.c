/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:51:39 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/13 03:43:44 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

t_ll	my_gettime(void)
{
	struct timeval	timeofday;

	if (gettimeofday(&timeofday, NULL) == -1)
		return (/*log=GETTIMEOFDAYFAILED*/-1);
	return ((timeofday.tv_sec * 1000) + (timeofday.tv_usec / 1000));
}

void	write_error(const char *msg)
{
	size_t	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, msg, len);
	write(2, "\n", 1);
}

ssize_t	my_usleep(size_t time, t_philo *philo)
{
	size_t	start;
	size_t	curr;

	start = my_gettime();
	curr = start;
	(void)philo;
	while (curr - start < time)
	{
		usleep(100);
		curr = my_gettime();
		// Could cause some performance issues due to mutexes locking and unlocking.
		if (check_death_status(philo))
			return (-1);
	}
	return (curr);
}

void	print_philo_status(t_philo *philo, const char *msg)
{
	t_ll	timestamp;

	timestamp = my_gettime() - philo->context->start_time;
	pthread_mutex_lock(&philo->context->print_mutex);
	pthread_mutex_lock(&philo->context->death_mutex);
	if (philo->context->death_flag == -1)
		printf("%lld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->context->death_mutex);
	pthread_mutex_unlock(&philo->context->print_mutex);
}

bool	check_death_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->context->death_mutex);
	if (philo->time_to_die <= my_gettime() - philo->last_eat)
	{
		//printf("%lld %d died\n",
		//	my_gettime() - philo->context->start_time, philo->id);
		philo->context->death_flag = philo->id;
		pthread_mutex_unlock(&philo->context->death_mutex);
		return (true);
	}
	//if (philo->context->death_flag != -1)
	//{
	//	pthread_mutex_unlock(&philo->context->death_mutex);
	//	return (true);
	//}
	pthread_mutex_unlock(&philo->context->death_mutex);
	return (false);
}

bool	check_meals_per_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->context->meal_mutex);
	if (philo->eat_count != -1 && philo->eat_count == 0)
	{
		philo->context->feast_count++;
		pthread_mutex_unlock(&philo->context->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->context->meal_mutex);
	return (false);
}
