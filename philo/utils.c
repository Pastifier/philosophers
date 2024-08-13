/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:51:39 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/13 05:47:22 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

t_ll	my_gettime(void)
{
	struct timeval	timeofday;

	if (gettimeofday(&timeofday, NULL) == -1)
		return (write_error(GETTIMEOFDAY_FAILED), -1);
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
		usleep(200);
		curr = my_gettime();
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
	if (philo->time_to_die < my_gettime() - philo->last_eat)
	{
		philo->context->death_flag = philo->id;
		pthread_mutex_unlock(&philo->context->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->context->death_mutex);
	return (false);
}
