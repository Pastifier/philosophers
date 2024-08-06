/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:40:53 by ebinjama          #+#    #+#             */
/*   Updated: 2024/07/29 10:31:51y ebinjama         ###   ########.fr       */
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

	pthread_mutex_lock(&philo->context->time_mutex);
	start = my_gettime();
	pthread_mutex_unlock(&philo->context->time_mutex);
	curr = start;
	while (curr - start < time)
	{
		usleep(100);
		pthread_mutex_lock(&philo->context->time_mutex);
		curr = my_gettime();
		pthread_mutex_unlock(&philo->context->time_mutex);
		if (check_death(philo))
			return (-1);
	}
	return (curr);
}

void	print_philo_status(t_philo *philo, const char *msg)
{
	t_ll	timestamp;

	pthread_mutex_lock(&philo->context->time_mutex);
	timestamp = my_gettime() - philo->context->start_time;
	pthread_mutex_unlock(&philo->context->time_mutex);
	if (timestamp == -1)
		return ;
	pthread_mutex_lock(&philo->context->print_mutex);
	printf("%lld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->context->print_mutex);
}

bool	check_death(t_philo *philo)
{
	t_ll	curr_time;

	pthread_mutex_lock(&philo->context->time_mutex);
	curr_time = my_gettime();
	pthread_mutex_unlock(&philo->context->time_mutex);
	pthread_mutex_lock(&philo->context->death_mutex);
	if (philo->context->death_flag != -1)
	{
		pthread_mutex_unlock(&philo->context->death_mutex);
		return (true);
	}
	if (curr_time == -1)
	{
		pthread_mutex_unlock(&philo->context->death_mutex);
		return (false);
	}
	if (curr_time - philo->last_eat >= philo->time_to_die)
	{
		philo->context->death_flag = philo->id;
		pthread_mutex_unlock(&philo->context->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->context->death_mutex);
	return (false);
}
